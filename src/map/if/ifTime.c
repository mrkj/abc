/**CFile****************************************************************

  FileName    [ifTime.c]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [FPGA mapping based on priority cuts.]

  Synopsis    [Computation of delay paramters depending on the library.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - November 21, 2006.]

  Revision    [$Id: ifTime.c,v 1.00 2006/11/21 00:00:00 alanmi Exp $]

***********************************************************************/

#include "if.h"
#include "kit.h"

ABC_NAMESPACE_IMPL_START


////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

static void If_CutSortInputPins( If_Man_t * p, If_Cut_t * pCut, int * pPinPerm, float * pPinDelays );

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Inserts the entry while sorting them by delay.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
word If_AndVerifyArray( Vec_Wrd_t * vAnds, int nVars )
{
    Vec_Wrd_t * vTruths;
    If_And_t This;
    word Entry, Truth0, Truth1, TruthR;
    int i;
    static word Truth[8] = {
        0xAAAAAAAAAAAAAAAA,
        0xCCCCCCCCCCCCCCCC,
        0xF0F0F0F0F0F0F0F0,
        0xFF00FF00FF00FF00,
        0xFFFF0000FFFF0000,
        0xFFFFFFFF00000000,
        0x0000000000000000,
        0xFFFFFFFFFFFFFFFF
    };
    if ( Vec_WrdSize(vAnds) == 0 )
        return Truth[6];
    if ( Vec_WrdSize(vAnds) == 1 && Vec_WrdEntry(vAnds,0) == 0 )
        return Truth[7];
    vTruths = Vec_WrdAlloc( Vec_WrdSize(vAnds) );
    for ( i = 0; i < nVars; i++ )
        Vec_WrdPush( vTruths, Truth[i] );
    Vec_WrdForEachEntryStart( vAnds, Entry, i, nVars )
    {
        This   = If_WrdToAnd(Entry);
        Truth0 = Vec_WrdEntry( vTruths, This.iFan0 );
        Truth0 = This.fCompl0 ? ~Truth0 : Truth0;
        Truth1 = Vec_WrdEntry( vTruths, This.iFan1 );
        Truth1 = This.fCompl1 ? ~Truth1 : Truth1;
        TruthR = Truth0 & Truth1;
        Vec_WrdPush( vTruths, TruthR );
    }
    Vec_WrdFree( vTruths );
    TruthR = This.fCompl ? ~TruthR : TruthR;
    return TruthR;
}

/**Function*************************************************************

  Synopsis    [Inserts the entry while sorting them by delay.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void If_AndInsertSorted( Vec_Wrd_t * vAnds, If_And_t And )
{
    If_And_t This, Prev;
    int i;
    Vec_WrdPush( vAnds, If_AndToWrd(And) );
    for ( i = Vec_WrdSize(vAnds) - 1; i > 0; i-- )
    {
        This = If_WrdToAnd( Vec_WrdEntry(vAnds, i) );
        Prev = If_WrdToAnd( Vec_WrdEntry(vAnds, i-1) );
        if ( This.Delay <= Prev.Delay )
            break;
        Vec_WrdWriteEntry( vAnds, i,   If_AndToWrd(Prev) );
        Vec_WrdWriteEntry( vAnds, i-1, If_AndToWrd(This) );
    }
}

/**Function*************************************************************

  Synopsis    [Decomposes the cube into a bunch of AND gates.]

  Description [Records the result of decomposition into vLits. Returns
  the last AND gate of the decomposition.]
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
If_And_t If_CutDelaySopCube( Vec_Wrd_t * vCube, Vec_Wrd_t * vAnds, int fOrGate )
{
    If_And_t This, Prev, Next;
    assert( Vec_WrdSize(vCube) > 0 );
    while ( Vec_WrdSize(vCube) > 1 )
    {
        // get last
        This = If_WrdToAnd( Vec_WrdPop(vCube) );
        Prev = If_WrdToAnd( Vec_WrdPop(vCube) );
        // create new
        If_AndClear( &Next );
        Next.iFan0   = Prev.Id;
        Next.fCompl0 = Prev.fCompl ^ fOrGate;
        Next.iFan1   = This.Id;
        Next.fCompl1 = This.fCompl ^ fOrGate;
        Next.Id      = Vec_WrdSize(vAnds);
        Next.fCompl  = fOrGate;
        Next.Delay   = 1 + ABC_MAX( This.Delay, Prev.Delay );
        // add new
        If_AndInsertSorted( vCube, Next );
        Vec_WrdPush( vAnds, If_AndToWrd(Next) );
    }
    return If_WrdToAnd( Vec_WrdPop(vCube) );
}



/**Function*************************************************************

  Synopsis    [Returns the well-balanced structure of AIG nodes.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Vec_Wrd_t * If_CutDelaySopAnds( If_Man_t * p, If_Cut_t * pCut, Vec_Int_t * vCover, int fCompl )
{
    Vec_Wrd_t * vAnds, * vAndGate, * vOrGate;
    If_Obj_t * pLeaf;
    If_And_t Leaf;
    int i, k, Entry, Literal;
    vAnds = Vec_WrdAlloc( 32 );
    if ( Vec_IntSize(vCover) == 0 ) // const 0
    {
        assert( fCompl == 0 );
        return vAnds; 
    }
    if ( Vec_IntSize(vCover) == 1 && Vec_IntEntry(vCover, 0) == 0 ) // const 1
    {
        assert( fCompl == 0 );
        Vec_WrdPush( vAnds, 0 );
        return vAnds;
    }
    If_CutForEachLeaf( p, pCut, pLeaf, k )
    {
        If_AndClear( &Leaf );
        Leaf.Id     = k;
        Leaf.Delay  = (int)If_ObjCutBest(pLeaf)->Delay; 
        Vec_WrdPush( vAnds, If_AndToWrd(Leaf) );
    }
    // iterate through the cubes
    vOrGate = Vec_WrdAlloc( 16 );
    vAndGate = Vec_WrdAlloc( 16 );
    Vec_IntForEachEntry( vCover, Entry, i )
    { 
        Vec_WrdClear( vAndGate );
        If_CutForEachLeaf( p, pCut, pLeaf, k )
        {
            Literal = 3 & (Entry >> (k << 1));
            if ( Literal == 1 ) // neg literal
            {
                If_AndClear( &Leaf );
                Leaf.fCompl = 1;
                Leaf.Id     = k;
                Leaf.Delay  = (int)If_ObjCutBest(pLeaf)->Delay; 
                If_AndInsertSorted( vAndGate, Leaf );
            }
            else if ( Literal == 2 ) // pos literal
            {
                If_AndClear( &Leaf );
                Leaf.Id     = k;
                Leaf.Delay  = (int)If_ObjCutBest(pLeaf)->Delay; 
                If_AndInsertSorted( vAndGate, Leaf );
            }
            else if ( Literal != 0 ) 
                assert( 0 );
        }
        Leaf = If_CutDelaySopCube( vAndGate, vAnds, 0 );
        If_AndInsertSorted( vOrGate, Leaf );
    }
    Leaf = If_CutDelaySopCube( vOrGate, vAnds, 1 );
    Vec_WrdFree( vAndGate );
    Vec_WrdFree( vOrGate );
    if ( Vec_WrdSize(vAnds) == (int)pCut->nLeaves )
    {
//        Extra_PrintBinary( stdout, If_CutTruth(pCut), 32 ); printf( "\n" );
        assert( Leaf.Id < pCut->nLeaves );
        Leaf.iFan0 = Leaf.iFan1 = Leaf.Id;
        Leaf.Id    = Vec_WrdSize(vAnds);
        Vec_WrdPush( vAnds, If_AndToWrd(Leaf) );
    }
    if ( fCompl )
    {
        Leaf = If_WrdToAnd( Vec_WrdPop(vAnds) );
        Leaf.fCompl ^= 1;
        Vec_WrdPush( vAnds, If_AndToWrd(Leaf) );
    }
    return vAnds;
}

/**Function*************************************************************

  Synopsis    [Computes balanced AND decomposition.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Vec_Wrd_t * If_CutDelaySopArray( If_Man_t * p, If_Cut_t * pCut )
{
    Vec_Int_t * vCover;
    Vec_Wrd_t * vAnds;
    int RetValue;
    vCover = Vec_IntAlloc(0);
    RetValue = Kit_TruthIsop( If_CutTruth(pCut), If_CutLeaveNum(pCut), vCover, 1 );
    if ( RetValue == -1 )
    {
        Vec_IntFree( vCover );
        return NULL;
    }
    assert( RetValue == 0 || RetValue == 1 );
    vAnds = If_CutDelaySopAnds( p, pCut, vCover, RetValue ^ pCut->fCompl );
/*
    if ( pCut->nLeaves <= 5 )
    {
        if ( *If_CutTruth(pCut) != (unsigned)If_AndVerifyArray(vAnds, pCut->nLeaves) )
        {
            unsigned Truth0 = *If_CutTruth(pCut);
            unsigned Truth1 = (unsigned)If_AndVerifyArray(vAnds, pCut->nLeaves);

            printf( "\n" );
            Extra_PrintBinary( stdout, &Truth0, 32 ); printf( "\n" );
            Extra_PrintBinary( stdout, &Truth1, 32 ); printf( "\n" );

            printf( "Verification failed for %d vars.\n", pCut->nLeaves );
        }
//        else
//            printf( "Verification passed for %d vars.\n", pCut->nLeaves );
    }
    else if ( pCut->nLeaves == 6 )
    {
        if ( *((word *)If_CutTruth(pCut)) != If_AndVerifyArray(vAnds, pCut->nLeaves) )
            printf( "Verification failed for %d vars.\n", pCut->nLeaves );
//        else
//            printf( "Verification passed for %d vars.\n", pCut->nLeaves );
    }
*/
    Vec_IntFree( vCover );
    return vAnds;
}


/**Function*************************************************************

  Synopsis    [Derives the maximum depth from the leaf to the root.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int If_CutDelayLeafDepth_rec( Vec_Wrd_t * vAnds, If_And_t And, int iLeaf )
{
    int Depth0, Depth1, Depth;
    if ( (int)And.Id == iLeaf )
        return 0;
    if ( And.iFan0 == And.iFan1 )
        return -100;
    Depth0 = If_CutDelayLeafDepth_rec( vAnds, If_WrdToAnd(Vec_WrdEntry(vAnds, And.iFan0)), iLeaf );
    Depth1 = If_CutDelayLeafDepth_rec( vAnds, If_WrdToAnd(Vec_WrdEntry(vAnds, And.iFan1)), iLeaf );
    Depth  = ABC_MAX( Depth0, Depth1 );
    Depth  = (Depth == -100) ? -100 : Depth + 1;
    return Depth;
}

/**Function*************************************************************

  Synopsis    [Derives the maximum depth from the leaf to the root.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int If_CutDelayLeafDepth( Vec_Wrd_t * vAnds, int iLeaf )
{
    If_And_t Leaf;
    if ( Vec_WrdSize(vAnds) == 0 ) // const 0
        return -100;
    if ( Vec_WrdSize(vAnds) == 1 && Vec_WrdEntry(vAnds, 0) == 0 ) // const 1
        return -100;
    Leaf = If_WrdToAnd(Vec_WrdEntryLast(vAnds));
    if ( Leaf.iFan0 == Leaf.iFan1 )
    {
        if ( (int)Leaf.iFan0 == iLeaf )
            return 0;
        return -100;
    }
    return If_CutDelayLeafDepth_rec( vAnds, Leaf, iLeaf );
}


/**Function*************************************************************

  Synopsis    [Computes the SOP delay using balanced AND decomposition.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int If_CutDelaySopCost( If_Man_t * p, If_Cut_t * pCut )
{
    If_And_t Leaf;
    Vec_Wrd_t * vAnds;
    int i;//, Delay;
    // mark cut as a user cut
    pCut->fUser = 1;
    vAnds = If_CutDelaySopArray( p, pCut );
    if ( vAnds == NULL )
    {
        assert( 0 );
        return ABC_INFINITY;
    }
    // get the cost
    If_AndClear( &Leaf );
    if ( Vec_WrdSize(vAnds) )
        Leaf = If_WrdToAnd( Vec_WrdEntryLast(vAnds) );
    if ( pCut->nLeaves > 2 && Vec_WrdSize(vAnds) > (int)pCut->nLeaves )
        pCut->Cost = Vec_WrdSize(vAnds) - pCut->nLeaves;
    else
        pCut->Cost = 1;
    // get the permutation
    for ( i = 0; i < (int)pCut->nLeaves; i++ )
        pCut->pPerm[i] = If_CutDelayLeafDepth( vAnds, i );
    Vec_WrdFree( vAnds );
    // verify the delay
//    Delay = If_CutDelay( p, pCut );
//    assert( (int)Leaf.Delay == Delay );
    return Leaf.Delay;
}






/**Function*************************************************************

  Synopsis    [Computes delay.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
float If_CutDelay( If_Man_t * p, If_Cut_t * pCut )
{
    static int pPinPerm[IF_MAX_LUTSIZE];
    static float pPinDelays[IF_MAX_LUTSIZE];
    If_Obj_t * pLeaf;
    float Delay, DelayCur;
    float * pLutDelays;
    int i, Shift;
    assert( p->pPars->fSeqMap || pCut->nLeaves > 1 );
    Delay = -IF_FLOAT_LARGE;
    if ( p->pPars->pLutLib )
    {
        assert( !p->pPars->fLiftLeaves );
        pLutDelays = p->pPars->pLutLib->pLutDelays[pCut->nLeaves];
        if ( p->pPars->pLutLib->fVarPinDelays )
        {
            // compute the delay using sorted pins
            If_CutSortInputPins( p, pCut, pPinPerm, pPinDelays );
            for ( i = 0; i < (int)pCut->nLeaves; i++ )
            {
                DelayCur = pPinDelays[pPinPerm[i]] + pLutDelays[i];
                Delay = IF_MAX( Delay, DelayCur );
            }
        }
        else
        {
            If_CutForEachLeaf( p, pCut, pLeaf, i )
            {
                DelayCur = If_ObjCutBest(pLeaf)->Delay + pLutDelays[0];
                Delay = IF_MAX( Delay, DelayCur );
            }
        }
    }
    else
    {
        if ( pCut->fUser )
        {
            assert( !p->pPars->fLiftLeaves );
            If_CutForEachLeaf( p, pCut, pLeaf, i )
            {
                DelayCur = If_ObjCutBest(pLeaf)->Delay + (float)(pCut->pPerm ? pCut->pPerm[i] : 1.0);
                Delay = IF_MAX( Delay, DelayCur );
            }
        }
        else
        {
            if ( p->pPars->fLiftLeaves )
            {
                If_CutForEachLeafSeq( p, pCut, pLeaf, Shift, i )
                {
                    DelayCur = If_ObjCutBest(pLeaf)->Delay - Shift * p->Period;
                    Delay = IF_MAX( Delay, DelayCur );
                }
            }
            else
            {
                If_CutForEachLeaf( p, pCut, pLeaf, i )
                {
                    DelayCur = If_ObjCutBest(pLeaf)->Delay;
                    Delay = IF_MAX( Delay, DelayCur );
                }
            }
            Delay += 1.0;
        }
    }
    return Delay;
}

/**Function*************************************************************

  Synopsis    []

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void If_CutPropagateRequired( If_Man_t * p, If_Cut_t * pCut, float ObjRequired )
{
    static int pPinPerm[IF_MAX_LUTSIZE];
    static float pPinDelays[IF_MAX_LUTSIZE];
    If_Obj_t * pLeaf;
    float * pLutDelays;
    float Required;
    int i;
    assert( !p->pPars->fLiftLeaves );
    // compute the pins
    if ( p->pPars->pLutLib )
    {
        pLutDelays = p->pPars->pLutLib->pLutDelays[pCut->nLeaves];
        if ( p->pPars->pLutLib->fVarPinDelays )
        {
            // compute the delay using sorted pins
            If_CutSortInputPins( p, pCut, pPinPerm, pPinDelays );
            for ( i = 0; i < (int)pCut->nLeaves; i++ )
            {
                Required = ObjRequired - pLutDelays[i];
                pLeaf = If_ManObj( p, pCut->pLeaves[pPinPerm[i]] );
                pLeaf->Required = IF_MIN( pLeaf->Required, Required );
            }
        }
        else
        {
            Required = ObjRequired - pLutDelays[0];
            If_CutForEachLeaf( p, pCut, pLeaf, i )
                pLeaf->Required = IF_MIN( pLeaf->Required, Required );
        }
    }
    else
    {
        if ( pCut->fUser )
        {
            If_CutForEachLeaf( p, pCut, pLeaf, i )
            {
                Required = ObjRequired - (float)(pCut->pPerm ? pCut->pPerm[i] : 1.0);
                pLeaf->Required = IF_MIN( pLeaf->Required, Required );
            }
        }
        else
        {
            Required = ObjRequired - (float)1.0;
            If_CutForEachLeaf( p, pCut, pLeaf, i )
                pLeaf->Required = IF_MIN( pLeaf->Required, Required );
        }
    }
}

/**Function*************************************************************

  Synopsis    [Sorts the pins in the decreasing order of delays.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void If_CutSortInputPins( If_Man_t * p, If_Cut_t * pCut, int * pPinPerm, float * pPinDelays )
{
    If_Obj_t * pLeaf;
    int i, j, best_i, temp;
    // start the trivial permutation and collect pin delays
    If_CutForEachLeaf( p, pCut, pLeaf, i )
    {
        pPinPerm[i] = i;
        pPinDelays[i] = If_ObjCutBest(pLeaf)->Delay;
    }
    // selection sort the pins in the decreasible order of delays
    // this order will match the increasing order of LUT input pins
    for ( i = 0; i < (int)pCut->nLeaves-1; i++ )
    {
        best_i = i;
        for ( j = i+1; j < (int)pCut->nLeaves; j++ )
            if ( pPinDelays[pPinPerm[j]] > pPinDelays[pPinPerm[best_i]] )
                best_i = j;
        if ( best_i == i )
            continue;
        temp = pPinPerm[i]; 
        pPinPerm[i] = pPinPerm[best_i]; 
        pPinPerm[best_i] = temp;
    }
/*
    // verify
    assert( pPinPerm[0] < (int)pCut->nLeaves );
    for ( i = 1; i < (int)pCut->nLeaves; i++ )
    {
        assert( pPinPerm[i] < (int)pCut->nLeaves );
        assert( pPinDelays[pPinPerm[i-1]] >= pPinDelays[pPinPerm[i]] );
    }
*/
}

/**Function*************************************************************

  Synopsis    [Sorts the pins in the decreasing order of delays.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void If_CutRotatePins( If_Man_t * p, If_Cut_t * pCut )
{
    If_Obj_t * pLeaf;
    float PinDelays[32];
//    int PinPerm[32];
    int i;
//    assert( p->pPars->pLutLib && p->pPars->pLutLib->fVarPinDelays && p->pPars->fTruth ); 
    If_CutForEachLeaf( p, pCut, pLeaf, i )
        PinDelays[i] = If_ObjCutBest(pLeaf)->Delay;
    If_CutTruthPermute( p->puTemp[0], If_CutTruth(pCut), If_CutLeaveNum(pCut), PinDelays, If_CutLeaves(pCut) );
//    If_CutSortInputPins( p, pCut, PinPerm, PinDelays );
}

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////


ABC_NAMESPACE_IMPL_END

