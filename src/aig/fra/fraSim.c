/**CFile****************************************************************

  FileName    [fraSim.c]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [New FRAIG package.]

  Synopsis    []

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 30, 2007.]

  Revision    [$Id: fraSim.c,v 1.00 2007/06/30 00:00:00 alanmi Exp $]

***********************************************************************/

#include "fra.h"

ABC_NAMESPACE_IMPL_START


////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Computes hash value of the node using its simulation info.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Fra_SmlNodeHash( Aig_Obj_t * pObj, int nTableSize )
{
    Fra_Man_t * p = (Fra_Man_t *)pObj->pData;
    static int s_FPrimes[128] = { 
        1009, 1049, 1093, 1151, 1201, 1249, 1297, 1361, 1427, 1459, 
        1499, 1559, 1607, 1657, 1709, 1759, 1823, 1877, 1933, 1997, 
        2039, 2089, 2141, 2213, 2269, 2311, 2371, 2411, 2467, 2543, 
        2609, 2663, 2699, 2741, 2797, 2851, 2909, 2969, 3037, 3089, 
        3169, 3221, 3299, 3331, 3389, 3461, 3517, 3557, 3613, 3671, 
        3719, 3779, 3847, 3907, 3943, 4013, 4073, 4129, 4201, 4243, 
        4289, 4363, 4441, 4493, 4549, 4621, 4663, 4729, 4793, 4871, 
        4933, 4973, 5021, 5087, 5153, 5227, 5281, 5351, 5417, 5471, 
        5519, 5573, 5651, 5693, 5749, 5821, 5861, 5923, 6011, 6073, 
        6131, 6199, 6257, 6301, 6353, 6397, 6481, 6563, 6619, 6689, 
        6737, 6803, 6863, 6917, 6977, 7027, 7109, 7187, 7237, 7309, 
        7393, 7477, 7523, 7561, 7607, 7681, 7727, 7817, 7877, 7933, 
        8011, 8039, 8059, 8081, 8093, 8111, 8123, 8147
    };
    unsigned * pSims;
    unsigned uHash;
    int i;
//    assert( p->pSml->nWordsTotal <= 128 );
    uHash = 0;
    pSims = Fra_ObjSim(p->pSml, pObj->Id);
    for ( i = p->pSml->nWordsPref; i < p->pSml->nWordsTotal; i++ )
        uHash ^= pSims[i] * s_FPrimes[i & 0x7F];
    return uHash % nTableSize;
}

/**Function*************************************************************

  Synopsis    [Returns 1 if simulation info is composed of all zeros.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Fra_SmlNodeIsConst( Aig_Obj_t * pObj )
{
    Fra_Man_t * p = (Fra_Man_t *)pObj->pData;
    unsigned * pSims;
    int i;
    pSims = Fra_ObjSim(p->pSml, pObj->Id);
    for ( i = p->pSml->nWordsPref; i < p->pSml->nWordsTotal; i++ )
        if ( pSims[i] )
            return 0;
    return 1;
}

/**Function*************************************************************

  Synopsis    [Returns 1 if simulation infos are equal.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Fra_SmlNodesAreEqual( Aig_Obj_t * pObj0, Aig_Obj_t * pObj1 )
{
    Fra_Man_t * p = (Fra_Man_t *)pObj0->pData;
    unsigned * pSims0, * pSims1;
    int i;
    pSims0 = Fra_ObjSim(p->pSml, pObj0->Id);
    pSims1 = Fra_ObjSim(p->pSml, pObj1->Id);
    for ( i = p->pSml->nWordsPref; i < p->pSml->nWordsTotal; i++ )
        if ( pSims0[i] != pSims1[i] )
            return 0;
    return 1;
}

/**Function*************************************************************

  Synopsis    [Counts the number of 1s in the XOR of simulation data.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Fra_SmlNodeNotEquWeight( Fra_Sml_t * p, int Left, int Right )
{
    unsigned * pSimL, * pSimR;
    int k, Counter = 0;
    pSimL = Fra_ObjSim( p, Left );
    pSimR = Fra_ObjSim( p, Right );
    for ( k = p->nWordsPref; k < p->nWordsTotal; k++ )
        Counter += Aig_WordCountOnes( pSimL[k] ^ pSimR[k] );
    return Counter;
}

/**Function*************************************************************

  Synopsis    [Returns 1 if simulation info is composed of all zeros.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Fra_SmlNodeIsZero( Fra_Sml_t * p, Aig_Obj_t * pObj )
{
    unsigned * pSims;
    int i;
    pSims = Fra_ObjSim(p, pObj->Id);
    for ( i = p->nWordsPref; i < p->nWordsTotal; i++ )
        if ( pSims[i] )
            return 0;
    return 1;
}

/**Function*************************************************************

  Synopsis    [Counts the number of one's in the patten of the output.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Fra_SmlNodeCountOnes( Fra_Sml_t * p, Aig_Obj_t * pObj )
{
    unsigned * pSims;
    int i, Counter = 0;
    pSims = Fra_ObjSim(p, pObj->Id);
    for ( i = 0; i < p->nWordsTotal; i++ )
        Counter += Aig_WordCountOnes( pSims[i] );
    return Counter;
}



/**Function*************************************************************

  Synopsis    [Generated const 0 pattern.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlSavePattern0( Fra_Man_t * p, int fInit )
{
    memset( p->pPatWords, 0, sizeof(unsigned) * p->nPatWords );
}

/**Function*************************************************************

  Synopsis    [[Generated const 1 pattern.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlSavePattern1( Fra_Man_t * p, int fInit )
{
    Aig_Obj_t * pObj;
    int i, k, nTruePis;
    memset( p->pPatWords, 0xff, sizeof(unsigned) * p->nPatWords );
    if ( !fInit )
        return;
    // clear the state bits to correspond to all-0 initial state
    nTruePis = Aig_ManPiNum(p->pManAig) - Aig_ManRegNum(p->pManAig);
    k = 0;
    Aig_ManForEachLoSeq( p->pManAig, pObj, i )
        Aig_InfoXorBit( p->pPatWords, nTruePis * p->nFramesAll + k++ );
}

/**Function*************************************************************

  Synopsis    [Copy pattern from the solver into the internal storage.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlSavePattern( Fra_Man_t * p )
{
    Aig_Obj_t * pObj;
    int i;
    memset( p->pPatWords, 0, sizeof(unsigned) * p->nPatWords );
    Aig_ManForEachPi( p->pManFraig, pObj, i )
        if ( p->pSat->model.ptr[Fra_ObjSatNum(pObj)] == l_True )
            Aig_InfoSetBit( p->pPatWords, i );

    if ( p->vCex )
    {
        Vec_IntClear( p->vCex );
        for ( i = 0; i < Aig_ManPiNum(p->pManAig) - Aig_ManRegNum(p->pManAig); i++ )
            Vec_IntPush( p->vCex, Aig_InfoHasBit( p->pPatWords, i ) );
        for ( i = Aig_ManPiNum(p->pManFraig) - Aig_ManRegNum(p->pManFraig); i < Aig_ManPiNum(p->pManFraig); i++ )
            Vec_IntPush( p->vCex, Aig_InfoHasBit( p->pPatWords, i ) );
    }

/*
    printf( "Pattern: " );
    Aig_ManForEachPi( p->pManFraig, pObj, i )
        printf( "%d", Aig_InfoHasBit( p->pPatWords, i ) );
    printf( "\n" );
*/
}



/**Function*************************************************************

  Synopsis    [Creates the counter-example from the successful pattern.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlCheckOutputSavePattern( Fra_Man_t * p, Aig_Obj_t * pObjPo )
{ 
    Aig_Obj_t * pFanin, * pObjPi;
    unsigned * pSims;
    int i, k, BestPat, * pModel;
    // find the word of the pattern
    pFanin = Aig_ObjFanin0(pObjPo);
    pSims = Fra_ObjSim(p->pSml, pFanin->Id);
    for ( i = 0; i < p->pSml->nWordsTotal; i++ )
        if ( pSims[i] )
            break;
    assert( i < p->pSml->nWordsTotal );
    // find the bit of the pattern
    for ( k = 0; k < 32; k++ )
        if ( pSims[i] & (1 << k) )
            break;
    assert( k < 32 );
    // determine the best pattern
    BestPat = i * 32 + k;
    // fill in the counter-example data
    pModel = ABC_ALLOC( int, Aig_ManPiNum(p->pManFraig)+1 );
    Aig_ManForEachPi( p->pManAig, pObjPi, i )
    {
        pModel[i] = Aig_InfoHasBit(Fra_ObjSim(p->pSml, pObjPi->Id), BestPat);
//        printf( "%d", pModel[i] );
    }
    pModel[Aig_ManPiNum(p->pManAig)] = pObjPo->Id;
//    printf( "\n" );
    // set the model
    assert( p->pManFraig->pData == NULL );
    p->pManFraig->pData = pModel;
    return;
}

/**Function*************************************************************

  Synopsis    [Returns 1 if the one of the output is already non-constant 0.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Fra_SmlCheckOutput( Fra_Man_t * p )
{
    Aig_Obj_t * pObj;
    int i;
    // make sure the reference simulation pattern does not detect the bug
    pObj = Aig_ManPo( p->pManAig, 0 );
    assert( Aig_ObjFanin0(pObj)->fPhase == (unsigned)Aig_ObjFaninC0(pObj) ); 
    Aig_ManForEachPo( p->pManAig, pObj, i )
    {
        if ( !Fra_SmlNodeIsConst( Aig_ObjFanin0(pObj) ) )
        {
            // create the counter-example from this pattern
            Fra_SmlCheckOutputSavePattern( p, pObj );
            return 1;
        }
    }
    return 0;
}



/**Function*************************************************************

  Synopsis    [Assigns random patterns to the PI node.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlAssignRandom( Fra_Sml_t * p, Aig_Obj_t * pObj )
{
    unsigned * pSims;
    int i;
    assert( Aig_ObjIsPi(pObj) );
    pSims = Fra_ObjSim( p, pObj->Id );
    for ( i = 0; i < p->nWordsTotal; i++ )
        pSims[i] = Fra_ObjRandomSim();
}

/**Function*************************************************************

  Synopsis    [Assigns constant patterns to the PI node.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlAssignConst( Fra_Sml_t * p, Aig_Obj_t * pObj, int fConst1, int iFrame )
{
    unsigned * pSims;
    int i;
    assert( Aig_ObjIsPi(pObj) );
    pSims = Fra_ObjSim( p, pObj->Id ) + p->nWordsFrame * iFrame;
    for ( i = 0; i < p->nWordsFrame; i++ )
        pSims[i] = fConst1? ~(unsigned)0 : 0;
}

/**Function*************************************************************

  Synopsis    [Assings random simulation info for the PIs.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlInitialize( Fra_Sml_t * p, int fInit )
{
    Aig_Obj_t * pObj;
    int i;
    if ( fInit )
    {
        assert( Aig_ManRegNum(p->pAig) > 0 );
        assert( Aig_ManRegNum(p->pAig) < Aig_ManPiNum(p->pAig) );
        // assign random info for primary inputs
        Aig_ManForEachPiSeq( p->pAig, pObj, i )
            Fra_SmlAssignRandom( p, pObj );
        // assign the initial state for the latches
        Aig_ManForEachLoSeq( p->pAig, pObj, i )
            Fra_SmlAssignConst( p, pObj, 0, 0 );
    }
    else
    {
        Aig_ManForEachPi( p->pAig, pObj, i )
            Fra_SmlAssignRandom( p, pObj );
    }
}

/**Function*************************************************************

  Synopsis    [Assings distance-1 simulation info for the PIs.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlAssignDist1( Fra_Sml_t * p, unsigned * pPat )
{
    Aig_Obj_t * pObj;
    int f, i, k, Limit, nTruePis;
    assert( p->nFrames > 0 );
    if ( p->nFrames == 1 )
    {
        // copy the PI info 
        Aig_ManForEachPi( p->pAig, pObj, i )
            Fra_SmlAssignConst( p, pObj, Aig_InfoHasBit(pPat, i), 0 );
        // flip one bit
        Limit = ABC_MIN( Aig_ManPiNum(p->pAig), p->nWordsTotal * 32 - 1 );
        for ( i = 0; i < Limit; i++ )
            Aig_InfoXorBit( Fra_ObjSim( p, Aig_ManPi(p->pAig,i)->Id ), i+1 );
    }
    else
    {
        int fUseDist1 = 0;

        // copy the PI info for each frame
        nTruePis = Aig_ManPiNum(p->pAig) - Aig_ManRegNum(p->pAig);
        for ( f = 0; f < p->nFrames; f++ )
            Aig_ManForEachPiSeq( p->pAig, pObj, i )
                Fra_SmlAssignConst( p, pObj, Aig_InfoHasBit(pPat, nTruePis * f + i), f );
        // copy the latch info 
        k = 0;
        Aig_ManForEachLoSeq( p->pAig, pObj, i )
            Fra_SmlAssignConst( p, pObj, Aig_InfoHasBit(pPat, nTruePis * p->nFrames + k++), 0 );
//        assert( p->pManFraig == NULL || nTruePis * p->nFrames + k == Aig_ManPiNum(p->pManFraig) );

        // flip one bit of the last frame
        if ( fUseDist1 ) //&& p->nFrames == 2 )
        {
            Limit = ABC_MIN( nTruePis, p->nWordsFrame * 32 - 1 );
            for ( i = 0; i < Limit; i++ )
                Aig_InfoXorBit( Fra_ObjSim( p, Aig_ManPi(p->pAig, i)->Id ) + p->nWordsFrame*(p->nFrames-1), i+1 );
        }
    }
}


/**Function*************************************************************

  Synopsis    [Simulates one node.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlNodeSimulate( Fra_Sml_t * p, Aig_Obj_t * pObj, int iFrame )
{
    unsigned * pSims, * pSims0, * pSims1;
    int fCompl, fCompl0, fCompl1, i;
    assert( !Aig_IsComplement(pObj) );
    assert( Aig_ObjIsNode(pObj) );
    assert( iFrame == 0 || p->nWordsFrame < p->nWordsTotal );
    // get hold of the simulation information
    pSims  = Fra_ObjSim(p, pObj->Id) + p->nWordsFrame * iFrame;
    pSims0 = Fra_ObjSim(p, Aig_ObjFanin0(pObj)->Id) + p->nWordsFrame * iFrame;
    pSims1 = Fra_ObjSim(p, Aig_ObjFanin1(pObj)->Id) + p->nWordsFrame * iFrame;
    // get complemented attributes of the children using their random info
    fCompl  = pObj->fPhase;
    fCompl0 = Aig_ObjPhaseReal(Aig_ObjChild0(pObj));
    fCompl1 = Aig_ObjPhaseReal(Aig_ObjChild1(pObj));
    // simulate
    if ( fCompl0 && fCompl1 )
    {
        if ( fCompl )
            for ( i = 0; i < p->nWordsFrame; i++ )
                pSims[i] = (pSims0[i] | pSims1[i]);
        else
            for ( i = 0; i < p->nWordsFrame; i++ )
                pSims[i] = ~(pSims0[i] | pSims1[i]);
    }
    else if ( fCompl0 && !fCompl1 )
    {
        if ( fCompl )
            for ( i = 0; i < p->nWordsFrame; i++ )
                pSims[i] = (pSims0[i] | ~pSims1[i]);
        else
            for ( i = 0; i < p->nWordsFrame; i++ )
                pSims[i] = (~pSims0[i] & pSims1[i]);
    }
    else if ( !fCompl0 && fCompl1 )
    {
        if ( fCompl )
            for ( i = 0; i < p->nWordsFrame; i++ )
                pSims[i] = (~pSims0[i] | pSims1[i]);
        else
            for ( i = 0; i < p->nWordsFrame; i++ )
                pSims[i] = (pSims0[i] & ~pSims1[i]);
    }
    else // if ( !fCompl0 && !fCompl1 )
    {
        if ( fCompl )
            for ( i = 0; i < p->nWordsFrame; i++ )
                pSims[i] = ~(pSims0[i] & pSims1[i]);
        else
            for ( i = 0; i < p->nWordsFrame; i++ )
                pSims[i] = (pSims0[i] & pSims1[i]);
    }
}

/**Function*************************************************************

  Synopsis    [Simulates one node.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Fra_SmlNodesCompareInFrame( Fra_Sml_t * p, Aig_Obj_t * pObj0, Aig_Obj_t * pObj1, int iFrame0, int iFrame1 )
{
    unsigned * pSims0, * pSims1;
    int i;
    assert( !Aig_IsComplement(pObj0) );
    assert( !Aig_IsComplement(pObj1) );
    assert( iFrame0 == 0 || p->nWordsFrame < p->nWordsTotal );
    assert( iFrame1 == 0 || p->nWordsFrame < p->nWordsTotal );
    // get hold of the simulation information
    pSims0  = Fra_ObjSim(p, pObj0->Id) + p->nWordsFrame * iFrame0;
    pSims1  = Fra_ObjSim(p, pObj1->Id) + p->nWordsFrame * iFrame1;
    // compare
    for ( i = 0; i < p->nWordsFrame; i++ )
        if ( pSims0[i] != pSims1[i] )
            return 0;
    return 1;
}

/**Function*************************************************************

  Synopsis    [Simulates one node.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlNodeCopyFanin( Fra_Sml_t * p, Aig_Obj_t * pObj, int iFrame )
{
    unsigned * pSims, * pSims0;
    int fCompl, fCompl0, i;
    assert( !Aig_IsComplement(pObj) );
    assert( Aig_ObjIsPo(pObj) );
    assert( iFrame == 0 || p->nWordsFrame < p->nWordsTotal );
    // get hold of the simulation information
    pSims  = Fra_ObjSim(p, pObj->Id) + p->nWordsFrame * iFrame;
    pSims0 = Fra_ObjSim(p, Aig_ObjFanin0(pObj)->Id) + p->nWordsFrame * iFrame;
    // get complemented attributes of the children using their random info
    fCompl  = pObj->fPhase;
    fCompl0 = Aig_ObjPhaseReal(Aig_ObjChild0(pObj));
    // copy information as it is
    if ( fCompl0 )
        for ( i = 0; i < p->nWordsFrame; i++ )
            pSims[i] = ~pSims0[i];
    else
        for ( i = 0; i < p->nWordsFrame; i++ )
            pSims[i] = pSims0[i];
}

/**Function*************************************************************

  Synopsis    [Simulates one node.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlNodeTransferNext( Fra_Sml_t * p, Aig_Obj_t * pOut, Aig_Obj_t * pIn, int iFrame )
{
    unsigned * pSims0, * pSims1;
    int i;
    assert( !Aig_IsComplement(pOut) );
    assert( !Aig_IsComplement(pIn) );
    assert( Aig_ObjIsPo(pOut) );
    assert( Aig_ObjIsPi(pIn) );
    assert( iFrame == 0 || p->nWordsFrame < p->nWordsTotal );
    // get hold of the simulation information
    pSims0 = Fra_ObjSim(p, pOut->Id) + p->nWordsFrame * iFrame;
    pSims1 = Fra_ObjSim(p, pIn->Id) + p->nWordsFrame * (iFrame+1);
    // copy information as it is
    for ( i = 0; i < p->nWordsFrame; i++ )
        pSims1[i] = pSims0[i];
}


/**Function*************************************************************

  Synopsis    [Check if any of the POs becomes non-constant.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Fra_SmlCheckNonConstOutputs( Fra_Sml_t * p )
{
    Aig_Obj_t * pObj;
    int i;
    Aig_ManForEachPoSeq( p->pAig, pObj, i )
        if ( !Fra_SmlNodeIsZero(p, pObj) )
            return 1;
    return 0;
}

/**Function*************************************************************

  Synopsis    [Simulates AIG manager.]

  Description [Assumes that the PI simulation info is attached.]
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlSimulateOne( Fra_Sml_t * p )
{
    Aig_Obj_t * pObj, * pObjLi, * pObjLo;
    int f, i, clk;
clk = clock();
    for ( f = 0; f < p->nFrames; f++ )
    {
        // simulate the nodes
        Aig_ManForEachNode( p->pAig, pObj, i )
            Fra_SmlNodeSimulate( p, pObj, f );
        // copy simulation info into outputs
        Aig_ManForEachPoSeq( p->pAig, pObj, i )
            Fra_SmlNodeCopyFanin( p, pObj, f );
        // quit if this is the last timeframe
        if ( f == p->nFrames - 1 )
            break;
        // copy simulation info into outputs
        Aig_ManForEachLiSeq( p->pAig, pObj, i )
            Fra_SmlNodeCopyFanin( p, pObj, f );
        // copy simulation info into the inputs
        Aig_ManForEachLiLoSeq( p->pAig, pObjLi, pObjLo, i )
            Fra_SmlNodeTransferNext( p, pObjLi, pObjLo, f );
    }
p->timeSim += clock() - clk;
p->nSimRounds++;
}


/**Function*************************************************************

  Synopsis    [Resimulates fraiging manager after finding a counter-example.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlResimulate( Fra_Man_t * p )
{
    int nChanges, clk;
    Fra_SmlAssignDist1( p->pSml, p->pPatWords );
    Fra_SmlSimulateOne( p->pSml );
//    if ( p->pPars->fPatScores )
//        Fra_CleanPatScores( p );
    if ( p->pPars->fProve && Fra_SmlCheckOutput(p) )
        return;
clk = clock();
    nChanges = Fra_ClassesRefine( p->pCla );
    nChanges += Fra_ClassesRefine1( p->pCla, 1, NULL );
    if ( p->pCla->vImps )
        nChanges += Fra_ImpRefineUsingCex( p, p->pCla->vImps );
    if ( p->vOneHots )
        nChanges += Fra_OneHotRefineUsingCex( p, p->vOneHots );
p->timeRef += clock() - clk;
    if ( !p->pPars->nFramesK && nChanges < 1 )
        printf( "Error: A counter-example did not refine classes!\n" );
//    assert( nChanges >= 1 );
//printf( "Refined classes = %5d.   Changes = %4d.\n", Vec_PtrSize(p->vClasses), nChanges );
}

/**Function*************************************************************

  Synopsis    [Performs simulation of the manager.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlSimulate( Fra_Man_t * p, int fInit )
{
    int fVerbose = 0;
    int nChanges, nClasses, clk;
    assert( !fInit || Aig_ManRegNum(p->pManAig) );
    // start the classes
    Fra_SmlInitialize( p->pSml, fInit );
    Fra_SmlSimulateOne( p->pSml );
    if ( p->pPars->fProve && Fra_SmlCheckOutput(p) )
        return;
    Fra_ClassesPrepare( p->pCla, p->pPars->fLatchCorr, 0 );
//    Fra_ClassesPrint( p->pCla, 0 );
if ( fVerbose )
printf( "Starting classes = %5d.   Lits = %6d.\n", Vec_PtrSize(p->pCla->vClasses), Fra_ClassesCountLits(p->pCla) );

//return;

    // refine classes by walking 0/1 patterns
    Fra_SmlSavePattern0( p, fInit );
    Fra_SmlAssignDist1( p->pSml, p->pPatWords );
    Fra_SmlSimulateOne( p->pSml );
    if ( p->pPars->fProve && Fra_SmlCheckOutput(p) )
        return;
clk = clock();
    nChanges = Fra_ClassesRefine( p->pCla );
    nChanges += Fra_ClassesRefine1( p->pCla, 1, NULL );
p->timeRef += clock() - clk;
if ( fVerbose )
printf( "Refined classes  = %5d.   Changes = %4d.   Lits = %6d.\n", Vec_PtrSize(p->pCla->vClasses), nChanges, Fra_ClassesCountLits(p->pCla) );
    Fra_SmlSavePattern1( p, fInit );
    Fra_SmlAssignDist1( p->pSml, p->pPatWords );
    Fra_SmlSimulateOne( p->pSml );
    if ( p->pPars->fProve && Fra_SmlCheckOutput(p) )
        return;
clk = clock();
    nChanges = Fra_ClassesRefine( p->pCla );
    nChanges += Fra_ClassesRefine1( p->pCla, 1, NULL );
p->timeRef += clock() - clk;

if ( fVerbose )
printf( "Refined classes  = %5d.   Changes = %4d.   Lits = %6d.\n", Vec_PtrSize(p->pCla->vClasses), nChanges, Fra_ClassesCountLits(p->pCla) );
    // refine classes by random simulation
    do {
        Fra_SmlInitialize( p->pSml, fInit );
        Fra_SmlSimulateOne( p->pSml );
        nClasses = Vec_PtrSize(p->pCla->vClasses);
        if ( p->pPars->fProve && Fra_SmlCheckOutput(p) )
            return;
clk = clock();
        nChanges = Fra_ClassesRefine( p->pCla );
        nChanges += Fra_ClassesRefine1( p->pCla, 1, NULL );
p->timeRef += clock() - clk;
if ( fVerbose )
printf( "Refined classes  = %5d.   Changes = %4d.   Lits = %6d.\n", Vec_PtrSize(p->pCla->vClasses), nChanges, Fra_ClassesCountLits(p->pCla) );
    } while ( (double)nChanges / nClasses > p->pPars->dSimSatur );

//    if ( p->pPars->fVerbose )
//    printf( "Consts = %6d. Classes = %6d. Literals = %6d.\n", 
//        Vec_PtrSize(p->pCla->vClasses1), Vec_PtrSize(p->pCla->vClasses), Fra_ClassesCountLits(p->pCla) );
//    Fra_ClassesPrint( p->pCla, 0 );
}
 

/**Function*************************************************************

  Synopsis    [Allocates simulation manager.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Fra_Sml_t * Fra_SmlStart( Aig_Man_t * pAig, int nPref, int nFrames, int nWordsFrame )
{
    Fra_Sml_t * p;
    p = (Fra_Sml_t *)ABC_ALLOC( char, sizeof(Fra_Sml_t) + sizeof(unsigned) * Aig_ManObjNumMax(pAig) * (nPref + nFrames) * nWordsFrame );
    memset( p, 0, sizeof(Fra_Sml_t) + sizeof(unsigned) * (nPref + nFrames) * nWordsFrame );
    p->pAig        = pAig;
    p->nPref       = nPref;
    p->nFrames     = nPref + nFrames;
    p->nWordsFrame = nWordsFrame;
    p->nWordsTotal = (nPref + nFrames) * nWordsFrame;
    p->nWordsPref  = nPref * nWordsFrame;
    return p;
}

/**Function*************************************************************

  Synopsis    [Deallocates simulation manager.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlStop( Fra_Sml_t * p )
{
    ABC_FREE( p );
}


/**Function*************************************************************

  Synopsis    [Performs simulation of the uninitialized circuit.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Fra_Sml_t * Fra_SmlSimulateComb( Aig_Man_t * pAig, int nWords )
{
    Fra_Sml_t * p;
    p = Fra_SmlStart( pAig, 0, 1, nWords );
    Fra_SmlInitialize( p, 0 );
    Fra_SmlSimulateOne( p );
    return p;
}

/**Function*************************************************************

  Synopsis    [Performs simulation of the initialized circuit.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Fra_Sml_t * Fra_SmlSimulateSeq( Aig_Man_t * pAig, int nPref, int nFrames, int nWords, int fCheckMiter )
{
    Fra_Sml_t * p;
    p = Fra_SmlStart( pAig, nPref, nFrames, nWords );
    Fra_SmlInitialize( p, 1 );
    Fra_SmlSimulateOne( p );
    if ( fCheckMiter )
    p->fNonConstOut = Fra_SmlCheckNonConstOutputs( p );
    return p;
}

/**Function*************************************************************

  Synopsis    [Allocates a counter-example.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Cex_t * Fra_SmlAllocCounterExample( int nRegs, int nRealPis, int nFrames )
{
    Abc_Cex_t * pCex;
    int nWords = Aig_BitWordNum( nRegs + nRealPis * nFrames );
    pCex = (Abc_Cex_t *)ABC_ALLOC( char, sizeof(Abc_Cex_t) + sizeof(unsigned) * nWords );
    memset( pCex, 0, sizeof(Abc_Cex_t) + sizeof(unsigned) * nWords );
    pCex->nRegs  = nRegs;
    pCex->nPis   = nRealPis;
    pCex->nBits  = nRegs + nRealPis * nFrames;
    return pCex;
}

/**Function*************************************************************

  Synopsis    [Frees the counter-example.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Fra_SmlFreeCounterExample( Abc_Cex_t * pCex )
{
    ABC_FREE( pCex );
}

/**Function*************************************************************

  Synopsis    [Creates sequential counter-example from the simulation info.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Cex_t * Fra_SmlGetCounterExample( Fra_Sml_t * p )
{
    Abc_Cex_t * pCex;
    Aig_Obj_t * pObj;
    unsigned * pSims;
    int iPo, iFrame, iBit, i, k;

    // make sure the simulation manager has it
    assert( p->fNonConstOut );

    // find the first output that failed
    iPo = -1;
    iBit = -1;
    iFrame = -1;
    Aig_ManForEachPoSeq( p->pAig, pObj, iPo )
    {
        if ( Fra_SmlNodeIsZero(p, pObj) )
            continue;
        pSims = Fra_ObjSim( p, pObj->Id );
        for ( i = p->nWordsPref; i < p->nWordsTotal; i++ )
            if ( pSims[i] )
            {
                iFrame = i / p->nWordsFrame;
                iBit = 32 * (i % p->nWordsFrame) + Aig_WordFindFirstBit( pSims[i] );
                break;
            }
        break;
    }
    assert( iPo < Aig_ManPoNum(p->pAig)-Aig_ManRegNum(p->pAig) );
    assert( iFrame < p->nFrames );
    assert( iBit < 32 * p->nWordsFrame );

    // allocate the counter example
    pCex = Fra_SmlAllocCounterExample( Aig_ManRegNum(p->pAig), Aig_ManPiNum(p->pAig) - Aig_ManRegNum(p->pAig), iFrame + 1 );
    pCex->iPo    = iPo;
    pCex->iFrame = iFrame;

    // copy the bit data
    Aig_ManForEachLoSeq( p->pAig, pObj, k )
    {
        pSims = Fra_ObjSim( p, pObj->Id );
        if ( Aig_InfoHasBit( pSims, iBit ) )
            Aig_InfoSetBit( pCex->pData, k );
    }
    for ( i = 0; i <= iFrame; i++ )
    {
        Aig_ManForEachPiSeq( p->pAig, pObj, k )
        {
            pSims = Fra_ObjSim( p, pObj->Id );
            if ( Aig_InfoHasBit( pSims, 32 * p->nWordsFrame * i + iBit ) )
                Aig_InfoSetBit( pCex->pData, pCex->nRegs + pCex->nPis * i + k );
        }
    }
    // verify the counter example
    if ( !Fra_SmlRunCounterExample( p->pAig, pCex ) )
    {
        printf( "Fra_SmlGetCounterExample(): Counter-example is invalid.\n" );
        Fra_SmlFreeCounterExample( pCex );
        pCex = NULL;
    }
    return pCex;
}
 
/**Function*************************************************************

  Synopsis    [Generates seq counter-example from the combinational one.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Cex_t * Fra_SmlCopyCounterExample( Aig_Man_t * pAig, Aig_Man_t * pFrames, int * pModel )
{
    Abc_Cex_t * pCex;
    Aig_Obj_t * pObj;
    int i, nFrames, nTruePis, nTruePos, iPo, iFrame;
    // get the number of frames
    assert( Aig_ManRegNum(pAig) > 0 );
    assert( Aig_ManRegNum(pFrames) == 0 );
    nTruePis = Aig_ManPiNum(pAig)-Aig_ManRegNum(pAig);
    nTruePos = Aig_ManPoNum(pAig)-Aig_ManRegNum(pAig);
    nFrames = Aig_ManPiNum(pFrames) / nTruePis;
    assert( nTruePis * nFrames == Aig_ManPiNum(pFrames) );
    assert( nTruePos * nFrames == Aig_ManPoNum(pFrames) );
    // find the PO that failed
    iPo = -1;
    iFrame = -1;
    Aig_ManForEachPo( pFrames, pObj, i )
        if ( pObj->Id == pModel[Aig_ManPiNum(pFrames)] )
        {
            iPo = i % nTruePos;
            iFrame = i / nTruePos;
            break;
        }
    assert( iPo >= 0 );
    // allocate the counter example
    pCex = Fra_SmlAllocCounterExample( Aig_ManRegNum(pAig), nTruePis, iFrame + 1 );
    pCex->iPo    = iPo;
    pCex->iFrame = iFrame;

    // copy the bit data
    for ( i = 0; i < Aig_ManPiNum(pFrames); i++ )
    {
        if ( pModel[i] )
            Aig_InfoSetBit( pCex->pData, pCex->nRegs + i );
        if ( pCex->nRegs + i == pCex->nBits - 1 )
            break;
    }

    // verify the counter example
    if ( !Fra_SmlRunCounterExample( pAig, pCex ) )
    {
        printf( "Fra_SmlGetCounterExample(): Counter-example is invalid.\n" );
        Fra_SmlFreeCounterExample( pCex );
        pCex = NULL;
    }
    return pCex;

}

/**Function*************************************************************

  Synopsis    [Make the trivial counter-example for the trivially asserted output.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Cex_t * Fra_SmlTrivCounterExample( Aig_Man_t * pAig, int iFrameOut )
{
    Abc_Cex_t * pCex;
    int nTruePis, nTruePos, iPo, iFrame;
    assert( Aig_ManRegNum(pAig) > 0 );
    nTruePis = Aig_ManPiNum(pAig)-Aig_ManRegNum(pAig);
    nTruePos = Aig_ManPoNum(pAig)-Aig_ManRegNum(pAig);
    iPo = iFrameOut % nTruePos;
    iFrame = iFrameOut / nTruePos;
    // allocate the counter example
    pCex = Fra_SmlAllocCounterExample( Aig_ManRegNum(pAig), nTruePis, iFrame + 1 );
    pCex->iPo    = iPo;
    pCex->iFrame = iFrame;
    return pCex;
}

/**Function*************************************************************

  Synopsis    [Resimulates the counter-example.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Fra_SmlRunCounterExample( Aig_Man_t * pAig, Abc_Cex_t * p )
{
    Fra_Sml_t * pSml;
    Aig_Obj_t * pObj;
    int RetValue, i, k, iBit;
    assert( Aig_ManRegNum(pAig) > 0 );
    assert( Aig_ManRegNum(pAig) < Aig_ManPiNum(pAig) );
    // start a new sequential simulator
    pSml = Fra_SmlStart( pAig, 0, p->iFrame+1, 1 );
    // assign simulation info for the registers
    iBit = 0;
    Aig_ManForEachLoSeq( pAig, pObj, i )
        Fra_SmlAssignConst( pSml, pObj, Aig_InfoHasBit(p->pData, iBit++), 0 );
    // assign simulation info for the primary inputs
    for ( i = 0; i <= p->iFrame; i++ )
        Aig_ManForEachPiSeq( pAig, pObj, k )
            Fra_SmlAssignConst( pSml, pObj, Aig_InfoHasBit(p->pData, iBit++), i );
    assert( iBit == p->nBits );
    // run random simulation
    Fra_SmlSimulateOne( pSml );
    // check if the given output has failed
    RetValue = !Fra_SmlNodeIsZero( pSml, Aig_ManPo(pAig, p->iPo) );
    Fra_SmlStop( pSml );
    return RetValue;
}

/**Function*************************************************************

  Synopsis    [Make the trivial counter-example for the trivially asserted output.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Cex_t * Fra_SmlSimpleCounterExample( Aig_Man_t * pAig, int * pModel, int iFrame, int iPo )
{
    Abc_Cex_t * pCex;
    int iBit;
    pCex = Fra_SmlAllocCounterExample( Aig_ManRegNum(pAig), Aig_ManPiNum(pAig)-Aig_ManRegNum(pAig), iFrame + 1 );
    pCex->iPo    = iPo;
    pCex->iFrame = iFrame;
    for ( iBit = Aig_ManRegNum(pAig); iBit < pCex->nBits; iBit++ )
        if ( pModel[iBit-Aig_ManRegNum(pAig)] )
            Aig_InfoSetBit( pCex->pData, iBit );
/*
    if ( !Fra_SmlRunCounterExample( pAig, pCex ) )
    {
        printf( "Fra_SmlSimpleCounterExample(): Counter-example is invalid.\n" );
//        Fra_SmlFreeCounterExample( pCex );
//        pCex = NULL;
    }
*/
    return pCex;
}

/**Function*************************************************************

  Synopsis    [Resimulates the counter-example.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Fra_SmlWriteCounterExample( FILE * pFile, Aig_Man_t * pAig, Abc_Cex_t * p )
{
    Fra_Sml_t * pSml;
    Aig_Obj_t * pObj;
    int RetValue, i, k, iBit;
    unsigned * pSims;
    assert( Aig_ManRegNum(pAig) > 0 );
    assert( Aig_ManRegNum(pAig) < Aig_ManPiNum(pAig) );
    // start a new sequential simulator
    pSml = Fra_SmlStart( pAig, 0, p->iFrame+1, 1 );
    // assign simulation info for the registers
    iBit = 0;
    Aig_ManForEachLoSeq( pAig, pObj, i )
//        Fra_SmlAssignConst( pSml, pObj, Aig_InfoHasBit(p->pData, iBit++), 0 );
        Fra_SmlAssignConst( pSml, pObj, 0, 0 );
    // assign simulation info for the primary inputs
    iBit = p->nRegs;
    for ( i = 0; i <= p->iFrame; i++ )
        Aig_ManForEachPiSeq( pAig, pObj, k )
            Fra_SmlAssignConst( pSml, pObj, Aig_InfoHasBit(p->pData, iBit++), i );
    assert( iBit == p->nBits );
    // run random simulation
    Fra_SmlSimulateOne( pSml );
    // check if the given output has failed
    RetValue = !Fra_SmlNodeIsZero( pSml, Aig_ManPo(pAig, p->iPo) );

    // write the output file
    for ( i = 0; i <= p->iFrame; i++ )
    {
/*
        Aig_ManForEachLoSeq( pAig, pObj, k )
        {
            pSims = Fra_ObjSim(pSml, pObj->Id);
            fprintf( pFile, "%d", (int)(pSims[i] != 0) );
        }
        fprintf( pFile, " " );
*/
        Aig_ManForEachPiSeq( pAig, pObj, k )
        {
            pSims = Fra_ObjSim(pSml, pObj->Id);
            fprintf( pFile, "%d", (int)(pSims[i] != 0) );
        }
/*
        fprintf( pFile, " " );
        Aig_ManForEachPoSeq( pAig, pObj, k )
        {
            pSims = Fra_ObjSim(pSml, pObj->Id);
            fprintf( pFile, "%d", (int)(pSims[i] != 0) );
        }
        fprintf( pFile, " " );
        Aig_ManForEachLiSeq( pAig, pObj, k )
        {
            pSims = Fra_ObjSim(pSml, pObj->Id);
            fprintf( pFile, "%d", (int)(pSims[i] != 0) );
        }
*/
        fprintf( pFile, "\n" );
    }

    Fra_SmlStop( pSml );
    return RetValue;
}


////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////


ABC_NAMESPACE_IMPL_END

