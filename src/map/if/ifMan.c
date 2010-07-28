/**CFile****************************************************************

  FileName    [ifMan.c]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [FPGA mapping based on priority cuts.]

  Synopsis    [Mapping manager.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - November 21, 2006.]

  Revision    [$Id: ifMan.c,v 1.00 2006/11/21 00:00:00 alanmi Exp $]

***********************************************************************/

#include "if.h"

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

static If_Obj_t * If_ManSetupObj( If_Man_t * p );
static If_Cut_t ** If_ManSetupCuts( If_Man_t * p );

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Starts the AIG manager.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
If_Man_t * If_ManStart( If_Par_t * pPars )
{
    If_Man_t * p;
    // start the manager
    p = ALLOC( If_Man_t, 1 );
    memset( p, 0, sizeof(If_Man_t) );
    p->pPars = pPars;
    p->fEpsilon = (float)0.001;
    // allocate arrays for nodes
    p->vCis    = Vec_PtrAlloc( 100 );
    p->vCos    = Vec_PtrAlloc( 100 );
    p->vObjs   = Vec_PtrAlloc( 100 );
    p->vMapped = Vec_PtrAlloc( 100 );
    p->vTemp   = Vec_PtrAlloc( 100 );
    // prepare the memory manager
    p->nTruthSize = p->pPars->fTruth? If_CutTruthWords( p->pPars->nLutSize ) : 0;
    p->nPermSize  = p->pPars->fUsePerm? If_CutPermWords( p->pPars->nLutSize ) : 0;
    p->nCutSize   = sizeof(If_Cut_t) + sizeof(int) * (p->pPars->nLutSize + p->nPermSize + p->nTruthSize);
    p->nEntrySize = sizeof(If_Obj_t) + p->pPars->nCutsMax * p->nCutSize;
    p->nEntryBase = sizeof(If_Obj_t) + p->pPars->nCutsMax * sizeof(If_Cut_t);
    p->pMem = Mem_FixedStart( p->nEntrySize );
    // report expected memory usage
    if ( p->pPars->fVerbose )
        printf( "Memory (bytes): Truth = %3d. Cut = %3d. Entry = %4d. Total = %.2f Mb / 1K AIG nodes\n", 
            4 * p->nTruthSize, p->nCutSize, p->nEntrySize, 1000.0 * p->nEntrySize / (1<<20) );
    // room for temporary truth tables
    p->puTemp[0] = p->pPars->fTruth? ALLOC( unsigned, 4 * p->nTruthSize ) : NULL;
    p->puTemp[1] = p->puTemp[0] + p->nTruthSize;
    p->puTemp[2] = p->puTemp[1] + p->nTruthSize;
    p->puTemp[3] = p->puTemp[2] + p->nTruthSize;
    // create the constant node
    p->pConst1 = If_ManSetupObj( p );
    p->pConst1->Type = IF_CONST1;
    p->pConst1->fPhase = 1;
    // create temporary cuts
    p->ppCuts = If_ManSetupCuts( p );
    return p;
}

/**Function*************************************************************

  Synopsis    []

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void If_ManStop( If_Man_t * p )
{
    If_Cut_t * pTemp;
    int i;
    Vec_PtrFree( p->vCis );
    Vec_PtrFree( p->vCos );
    Vec_PtrFree( p->vObjs );
    Vec_PtrFree( p->vMapped );
    Vec_PtrFree( p->vTemp );
    if ( p->vLatchOrder ) Vec_PtrFree( p->vLatchOrder );
    if ( p->vLags ) Vec_IntFree( p->vLags );
    Mem_FixedStop( p->pMem, 0 );
    // free pars memory
    if ( p->pPars->pTimesArr )
        FREE( p->pPars->pTimesArr );
    if ( p->pPars->pTimesReq )
        FREE( p->pPars->pTimesReq );
    // free temporary cut memory
    pTemp = p->ppCuts[0];
    for ( i = 1; i < 1 + p->pPars->nCutsMax * p->pPars->nCutsMax; i++ )
        if ( pTemp > p->ppCuts[i] )
            pTemp = p->ppCuts[i];
    FREE( p->puTemp[0] );
    free( pTemp );
    free( p->ppCuts );
    free( p );
}

/**Function*************************************************************

  Synopsis    [Creates primary input.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
If_Obj_t * If_ManCreateCi( If_Man_t * p )
{
    If_Obj_t * pObj;
    pObj = If_ManSetupObj( p );
    pObj->Type = IF_CI;
    Vec_PtrPush( p->vCis, pObj );
    p->nObjs[IF_CI]++;
    return pObj;
}

/**Function*************************************************************

  Synopsis    [Creates primary output with the given driver.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
If_Obj_t * If_ManCreateCo( If_Man_t * p, If_Obj_t * pDriver, int fCompl0 )
{
    If_Obj_t * pObj;
    pObj = If_ManSetupObj( p );
    pObj->Type = IF_CO;
    pObj->fCompl0 = fCompl0;
    Vec_PtrPush( p->vCos, pObj );
    pObj->pFanin0 = pDriver; pDriver->nRefs++;
    p->nObjs[IF_CO]++;
    return pObj;
}

/**Function*************************************************************

  Synopsis    [Create the new node assuming it does not exist.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
If_Obj_t * If_ManCreateAnd( If_Man_t * p, If_Obj_t * pFan0, int fCompl0, If_Obj_t * pFan1, int fCompl1 )
{
    If_Obj_t * pObj;
    // get memory for the new object
    pObj = If_ManSetupObj( p );
    pObj->Type    = IF_AND;
    pObj->fCompl0 = fCompl0;
    pObj->fCompl1 = fCompl1;
    pObj->pFanin0 = pFan0; pFan0->nRefs++;
    pObj->pFanin1 = pFan1; pFan1->nRefs++;
    pObj->fPhase  = (fCompl0 ^ pFan0->fPhase) & (fCompl1 ^ pFan1->fPhase);
    pObj->Level   = 1 + IF_MAX( pFan0->Level, pFan1->Level );
    if ( p->nLevelMax < (int)pObj->Level )
        p->nLevelMax = (int)pObj->Level;
    p->nObjs[IF_AND]++;
    return pObj;
}

/**Function*************************************************************

  Synopsis    [Creates the choice node.]

  Description [Should be called after the equivalence class nodes are linked.]
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void If_ManCreateChoice( If_Man_t * p, If_Obj_t * pObj )
{
    If_Obj_t * pTemp;
    // mark the node as a representative if its class
    assert( pObj->fRepr == 0 );
    pObj->fRepr = 1;
    // update the level of this node (needed for correct required time computation)
    for ( pTemp = pObj->pEquiv; pTemp; pTemp = pTemp->pEquiv )
        pObj->Level = IF_MAX( pObj->Level, pTemp->Level );
    // mark the largest level
    if ( p->nLevelMax < (int)pObj->Level )
        p->nLevelMax = (int)pObj->Level;
}

/**Function*************************************************************

  Synopsis    [Prepares memory for the node with cuts.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
If_Obj_t * If_ManSetupObj( If_Man_t * p )
{
    If_Cut_t * pCut;
    If_Obj_t * pObj;
    int i, * pArrays, nTruthWords;
    // get memory for the object
    pObj = (If_Obj_t *)Mem_FixedEntryFetch( p->pMem );
    memset( pObj, 0, p->nEntryBase );
    // organize memory
    pArrays = (int *)((char *)pObj + p->nEntryBase);
    for ( i = 0; i < p->pPars->nCutsMax; i++ )
    {
        pCut = pObj->Cuts + i;
        pCut->nLimit  = p->pPars->nLutSize;
        pCut->pLeaves = pArrays + i * p->pPars->nLutSize;
        pCut->pPerm   = (char *)(p->pPars->fUsePerm? pArrays + p->pPars->nCutsMax * p->pPars->nLutSize + i * p->nPermSize : NULL);
        pCut->pTruth  = p->pPars->fTruth? pArrays + p->pPars->nCutsMax * (p->pPars->nLutSize + p->nPermSize) + i * p->nTruthSize : NULL;
    }
    // assign ID and save 
    pObj->Id = Vec_PtrSize(p->vObjs);
    Vec_PtrPush( p->vObjs, pObj );
    // assign elementary cut
    pCut = pObj->Cuts;
    pCut->nLeaves    = 1;
    pCut->pLeaves[0] = p->pPars->fLiftLeaves? (pObj->Id << 8) : pObj->Id;
    pCut->uSign      = If_ObjCutSign( pCut->pLeaves[0] );
    // set the number of cuts
    pObj->nCuts = 1;
    // set the required times
    pObj->Required = IF_FLOAT_LARGE;
    // set up elementary truth table of the unit cut
    if ( p->pPars->fTruth )
    {
        nTruthWords = Extra_TruthWordNum( pCut->nLimit );
        for ( i = 0; i < nTruthWords; i++ )
            If_CutTruth(pCut)[i] = 0xAAAAAAAA;
    }
    return pObj;
}

/**Function*************************************************************

  Synopsis    [Prepares memory for additional cuts of the manager.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
If_Cut_t ** If_ManSetupCuts( If_Man_t * p )
{
    If_Cut_t ** pCutStore;
    int * pArrays, nCutsTotal, i;
    // decide how many cuts to alloc
    nCutsTotal = 1 + p->pPars->nCutsMax * p->pPars->nCutsMax;
    // allocate and clean space for cuts
    pCutStore = (If_Cut_t **)ALLOC( If_Cut_t *, (nCutsTotal + 1) );
    memset( pCutStore, 0, sizeof(If_Cut_t *) * (nCutsTotal + 1) );
    pCutStore[0] = (If_Cut_t *)ALLOC( char, p->nCutSize * nCutsTotal );
    memset( pCutStore[0], 0, p->nCutSize * nCutsTotal );
    // assign cut paramters and space for the cut leaves
    assert( sizeof(int) == sizeof(unsigned) );
    pArrays = (int *)((char *)pCutStore[0] + sizeof(If_Cut_t) * nCutsTotal);
    for ( i = 0; i < nCutsTotal; i++ )
    {
        pCutStore[i] = (If_Cut_t *)((char *)pCutStore[0] + sizeof(If_Cut_t) * i);
        pCutStore[i]->nLimit  = p->pPars->nLutSize;
        pCutStore[i]->pLeaves = pArrays + i * p->pPars->nLutSize;
        pCutStore[i]->pPerm   = (char *)(p->pPars->fUsePerm? pArrays + nCutsTotal * p->pPars->nLutSize + i * p->nPermSize : NULL);
        pCutStore[i]->pTruth  = p->pPars->fTruth? pArrays + nCutsTotal * (p->pPars->nLutSize + p->nPermSize) + i * p->nTruthSize : NULL;
    }
    return pCutStore;
}


////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////


