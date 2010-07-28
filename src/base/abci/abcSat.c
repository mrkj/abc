/**CFile****************************************************************

  FileName    [abcSat.c]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Network and node package.]

  Synopsis    [Procedures to solve the miter using the internal SAT solver.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 20, 2005.]

  Revision    [$Id: abcSat.c,v 1.00 2005/06/20 00:00:00 alanmi Exp $]

***********************************************************************/

#include "abc.h"

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

extern Vec_Int_t * Abc_NtkGetCiSatVarNums( Abc_Ntk_t * pNtk );
static nMuxes;

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Attempts to solve the miter using an internal SAT solver.]

  Description [Returns -1 if timed out; 0 if SAT; 1 if UNSAT.]
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Abc_NtkMiterSat( Abc_Ntk_t * pNtk, sint64 nConfLimit, sint64 nInsLimit, int fJFront, int fVerbose, sint64 * pNumConfs, sint64 * pNumInspects )
{
    solver * pSat;
    lbool   status;
    int RetValue, clk;

    if ( pNumConfs )
        *pNumConfs = 0;
    if ( pNumInspects )
        *pNumInspects = 0;

    assert( Abc_NtkIsStrash(pNtk) );
    assert( Abc_NtkLatchNum(pNtk) == 0 );

//    if ( Abc_NtkPoNum(pNtk) > 1 )
//        fprintf( stdout, "Warning: The miter has %d outputs. SAT will try to prove all of them.\n", Abc_NtkPoNum(pNtk) );

    // load clauses into the solver
    clk = clock();
    pSat = Abc_NtkMiterSatCreate( pNtk, fJFront );
    if ( pSat == NULL )
        return 1;
//    printf( "Created SAT problem with %d variable and %d clauses. ", solver_nvars(pSat), solver_nclauses(pSat) );
//    PRT( "Time", clock() - clk );

    // simplify the problem
    clk = clock();
    status = solver_simplify(pSat);
//    printf( "Simplified the problem to %d variables and %d clauses. ", solver_nvars(pSat), solver_nclauses(pSat) );
//    PRT( "Time", clock() - clk );
    if ( status == 0 )
    {
        solver_delete( pSat );
//        printf( "The problem is UNSATISFIABLE after simplification.\n" );
        return 1;
    }

    // solve the miter
    clk = clock();
    if ( fVerbose )
        pSat->verbosity = 1;
    status = solver_solve( pSat, NULL, NULL, (sint64)nConfLimit, (sint64)nInsLimit );
    if ( status == l_Undef )
    {
//        printf( "The problem timed out.\n" );
        RetValue = -1;
    }
    else if ( status == l_True )
    {
//        printf( "The problem is SATISFIABLE.\n" );
        RetValue = 0;
    }
    else if ( status == l_False )
    {
//        printf( "The problem is UNSATISFIABLE.\n" );
        RetValue = 1;
    }
    else
        assert( 0 );
//    PRT( "SAT solver time", clock() - clk );
//    printf( "The number of conflicts = %d.\n", (int)pSat->solver_stats.conflicts );

    // if the problem is SAT, get the counterexample
    if ( status == l_True )
    {
//        Vec_Int_t * vCiIds = Abc_NtkGetCiIds( pNtk );
        Vec_Int_t * vCiIds = Abc_NtkGetCiSatVarNums( pNtk );
        pNtk->pModel = solver_get_model( pSat, vCiIds->pArray, vCiIds->nSize );
        Vec_IntFree( vCiIds );
    }
    // free the solver
    if ( fVerbose )
        Asat_SatPrintStats( stdout, pSat );

    if ( pNumConfs )
        *pNumConfs = (int)pSat->solver_stats.conflicts;
    if ( pNumInspects )
        *pNumInspects = (int)pSat->solver_stats.inspects;

    solver_delete( pSat );
    return RetValue;
}

/**Function*************************************************************

  Synopsis    [Returns the array of CI IDs.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Vec_Int_t * Abc_NtkGetCiSatVarNums( Abc_Ntk_t * pNtk )
{
    Vec_Int_t * vCiIds;
    Abc_Obj_t * pObj;
    int i;
    vCiIds = Vec_IntAlloc( Abc_NtkCiNum(pNtk) );
    Abc_NtkForEachCi( pNtk, pObj, i )
        Vec_IntPush( vCiIds, (int)pObj->pCopy );
    return vCiIds;
}


 
/**Function*************************************************************

  Synopsis    [Adds trivial clause.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Abc_NtkClauseTriv( solver * pSat, Abc_Obj_t * pNode, Vec_Int_t * vVars )
{
//printf( "Adding triv %d.         %d\n", Abc_ObjRegular(pNode)->Id, (int)pSat->solver_stats.clauses );
    vVars->nSize = 0;
    Vec_IntPush( vVars, toLitCond( (int)Abc_ObjRegular(pNode)->pCopy, Abc_ObjIsComplement(pNode) ) );
//    Vec_IntPush( vVars, toLitCond( (int)Abc_ObjRegular(pNode)->Id, Abc_ObjIsComplement(pNode) ) );
    return solver_addclause( pSat, vVars->pArray, vVars->pArray + vVars->nSize );
}
 
/**Function*************************************************************

  Synopsis    [Adds trivial clause.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Abc_NtkClauseTop( solver * pSat, Vec_Ptr_t * vNodes, Vec_Int_t * vVars )
{
    Abc_Obj_t * pNode;
    int i;
//printf( "Adding triv %d.         %d\n", Abc_ObjRegular(pNode)->Id, (int)pSat->solver_stats.clauses );
    vVars->nSize = 0;
    Vec_PtrForEachEntry( vNodes, pNode, i )
        Vec_IntPush( vVars, toLitCond( (int)Abc_ObjRegular(pNode)->pCopy, Abc_ObjIsComplement(pNode) ) );
//    Vec_IntPush( vVars, toLitCond( (int)Abc_ObjRegular(pNode)->Id, Abc_ObjIsComplement(pNode) ) );
    return solver_addclause( pSat, vVars->pArray, vVars->pArray + vVars->nSize );
}
 
/**Function*************************************************************

  Synopsis    [Adds trivial clause.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Abc_NtkClauseAnd( solver * pSat, Abc_Obj_t * pNode, Vec_Ptr_t * vSuper, Vec_Int_t * vVars )
{
    int fComp1, Var, Var1, i;
//printf( "Adding AND %d.  (%d)    %d\n", pNode->Id, vSuper->nSize+1, (int)pSat->solver_stats.clauses );

    assert( !Abc_ObjIsComplement( pNode ) );
    assert( Abc_ObjIsNode( pNode ) );

//    nVars = solver_nvars(pSat);
    Var = (int)pNode->pCopy;
//    Var = pNode->Id;

//    assert( Var  < nVars ); 
    for ( i = 0; i < vSuper->nSize; i++ )
    {
        // get the predecessor nodes
        // get the complemented attributes of the nodes
        fComp1 = Abc_ObjIsComplement(vSuper->pArray[i]);
        // determine the variable numbers
        Var1 = (int)Abc_ObjRegular(vSuper->pArray[i])->pCopy;
//        Var1 = (int)Abc_ObjRegular(vSuper->pArray[i])->Id;

        // check that the variables are in the SAT manager
//        assert( Var1 < nVars );

        // suppose the AND-gate is A * B = C
        // add !A => !C   or   A + !C
    //  fprintf( pFile, "%d %d 0%c", Var1, -Var, 10 );
        vVars->nSize = 0;
        Vec_IntPush( vVars, toLitCond(Var1, fComp1) );
        Vec_IntPush( vVars, toLitCond(Var,  1     ) );
        if ( !solver_addclause( pSat, vVars->pArray, vVars->pArray + vVars->nSize ) )
            return 0;
    }

    // add A & B => C   or   !A + !B + C
//  fprintf( pFile, "%d %d %d 0%c", -Var1, -Var2, Var, 10 );
    vVars->nSize = 0;
    for ( i = 0; i < vSuper->nSize; i++ )
    {
        // get the predecessor nodes
        // get the complemented attributes of the nodes
        fComp1 = Abc_ObjIsComplement(vSuper->pArray[i]);
        // determine the variable numbers
        Var1 = (int)Abc_ObjRegular(vSuper->pArray[i])->pCopy;
//        Var1 = (int)Abc_ObjRegular(vSuper->pArray[i])->Id;
        // add this variable to the array
        Vec_IntPush( vVars, toLitCond(Var1, !fComp1) );
    }
    Vec_IntPush( vVars, toLitCond(Var, 0) );
    return solver_addclause( pSat, vVars->pArray, vVars->pArray + vVars->nSize );
}
 
/**Function*************************************************************

  Synopsis    [Adds trivial clause.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Abc_NtkClauseMux( solver * pSat, Abc_Obj_t * pNode, Abc_Obj_t * pNodeC, Abc_Obj_t * pNodeT, Abc_Obj_t * pNodeE, Vec_Int_t * vVars )
{
    int VarF, VarI, VarT, VarE, fCompT, fCompE;
//printf( "Adding mux %d.         %d\n", pNode->Id, (int)pSat->solver_stats.clauses );

    assert( !Abc_ObjIsComplement( pNode ) );
    assert( Abc_NodeIsMuxType( pNode ) );
    // get the variable numbers
    VarF = (int)pNode->pCopy;
    VarI = (int)pNodeC->pCopy;
    VarT = (int)Abc_ObjRegular(pNodeT)->pCopy;
    VarE = (int)Abc_ObjRegular(pNodeE)->pCopy;
//    VarF = (int)pNode->Id;
//    VarI = (int)pNodeC->Id;
//    VarT = (int)Abc_ObjRegular(pNodeT)->Id;
//    VarE = (int)Abc_ObjRegular(pNodeE)->Id;

    // get the complementation flags
    fCompT = Abc_ObjIsComplement(pNodeT);
    fCompE = Abc_ObjIsComplement(pNodeE);

    // f = ITE(i, t, e)
    // i' + t' + f
    // i' + t  + f'
    // i  + e' + f
    // i  + e  + f'
    // create four clauses
    vVars->nSize = 0;
    Vec_IntPush( vVars, toLitCond(VarI,  1) );
    Vec_IntPush( vVars, toLitCond(VarT,  1^fCompT) );
    Vec_IntPush( vVars, toLitCond(VarF,  0) );
    if ( !solver_addclause( pSat, vVars->pArray, vVars->pArray + vVars->nSize ) )
        return 0;
    vVars->nSize = 0;
    Vec_IntPush( vVars, toLitCond(VarI,  1) );
    Vec_IntPush( vVars, toLitCond(VarT,  0^fCompT) );
    Vec_IntPush( vVars, toLitCond(VarF,  1) );
    if ( !solver_addclause( pSat, vVars->pArray, vVars->pArray + vVars->nSize ) )
        return 0;
    vVars->nSize = 0;
    Vec_IntPush( vVars, toLitCond(VarI,  0) );
    Vec_IntPush( vVars, toLitCond(VarE,  1^fCompE) );
    Vec_IntPush( vVars, toLitCond(VarF,  0) );
    if ( !solver_addclause( pSat, vVars->pArray, vVars->pArray + vVars->nSize ) )
        return 0;
    vVars->nSize = 0;
    Vec_IntPush( vVars, toLitCond(VarI,  0) );
    Vec_IntPush( vVars, toLitCond(VarE,  0^fCompE) );
    Vec_IntPush( vVars, toLitCond(VarF,  1) );
    if ( !solver_addclause( pSat, vVars->pArray, vVars->pArray + vVars->nSize ) )
        return 0;
 
    if ( VarT == VarE )
    {
//        assert( fCompT == !fCompE );
        return 1;
    }

    // two additional clauses
    // t' & e' -> f'       t  + e   + f'
    // t  & e  -> f        t' + e'  + f 
    vVars->nSize = 0;
    Vec_IntPush( vVars, toLitCond(VarT,  0^fCompT) );
    Vec_IntPush( vVars, toLitCond(VarE,  0^fCompE) );
    Vec_IntPush( vVars, toLitCond(VarF,  1) );
    if ( !solver_addclause( pSat, vVars->pArray, vVars->pArray + vVars->nSize ) )
        return 0;
    vVars->nSize = 0;
    Vec_IntPush( vVars, toLitCond(VarT,  1^fCompT) );
    Vec_IntPush( vVars, toLitCond(VarE,  1^fCompE) );
    Vec_IntPush( vVars, toLitCond(VarF,  0) );
    return solver_addclause( pSat, vVars->pArray, vVars->pArray + vVars->nSize );
}

/**Function*************************************************************

  Synopsis    [Returns the array of nodes to be combined into one multi-input AND-gate.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Abc_NtkCollectSupergate_rec( Abc_Obj_t * pNode, Vec_Ptr_t * vSuper, int fFirst, int fStopAtMux )
{
    int RetValue1, RetValue2, i;
    // check if the node is visited
    if ( Abc_ObjRegular(pNode)->fMarkB )
    {
        // check if the node occurs in the same polarity
        for ( i = 0; i < vSuper->nSize; i++ )
            if ( vSuper->pArray[i] == pNode )
                return 1;
        // check if the node is present in the opposite polarity
        for ( i = 0; i < vSuper->nSize; i++ )
            if ( vSuper->pArray[i] == Abc_ObjNot(pNode) )
                return -1;
        assert( 0 );
        return 0;
    }
    // if the new node is complemented or a PI, another gate begins
    if ( !fFirst )
    if ( Abc_ObjIsComplement(pNode) || !Abc_ObjIsNode(pNode) || Abc_ObjFanoutNum(pNode) > 1 || fStopAtMux && Abc_NodeIsMuxType(pNode) )
    {
        Vec_PtrPush( vSuper, pNode );
        Abc_ObjRegular(pNode)->fMarkB = 1;
        return 0;
    }
    assert( !Abc_ObjIsComplement(pNode) );
    assert( Abc_ObjIsNode(pNode) );
    // go through the branches
    RetValue1 = Abc_NtkCollectSupergate_rec( Abc_ObjChild0(pNode), vSuper, 0, fStopAtMux );
    RetValue2 = Abc_NtkCollectSupergate_rec( Abc_ObjChild1(pNode), vSuper, 0, fStopAtMux );
    if ( RetValue1 == -1 || RetValue2 == -1 )
        return -1;
    // return 1 if at least one branch has a duplicate
    return RetValue1 || RetValue2;
}

/**Function*************************************************************

  Synopsis    [Returns the array of nodes to be combined into one multi-input AND-gate.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Abc_NtkCollectSupergate( Abc_Obj_t * pNode, int fStopAtMux, Vec_Ptr_t * vNodes )
{
    int RetValue, i;
    assert( !Abc_ObjIsComplement(pNode) );
    // collect the nodes in the implication supergate
    Vec_PtrClear( vNodes );
    RetValue = Abc_NtkCollectSupergate_rec( pNode, vNodes, 1, fStopAtMux );
    assert( vNodes->nSize > 1 );
    // unmark the visited nodes
    for ( i = 0; i < vNodes->nSize; i++ )
        Abc_ObjRegular((Abc_Obj_t *)vNodes->pArray[i])->fMarkB = 0;
    // if we found the node and its complement in the same implication supergate, 
    // return empty set of nodes (meaning that we should use constant-0 node)
    if ( RetValue == -1 )
        vNodes->nSize = 0;
}


/**Function*************************************************************

  Synopsis    [Computes the factor of the node.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Abc_NtkNodeFactor( Abc_Obj_t * pObj, int nLevelMax )
{
//  nLevelMax = ((nLevelMax)/2)*3;
    assert( (int)pObj->Level <= nLevelMax );
//    return (int)(100000000.0 * pow(0.999, nLevelMax - pObj->Level));
    return (int)(100000000.0 * (1 + 0.01 * pObj->Level));
//    return (int)(100000000.0 / ((nLevelMax)/2)*3 - pObj->Level);
}

/**Function*************************************************************

  Synopsis    [Sets up the SAT solver.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Abc_NtkMiterSatCreateInt( solver * pSat, Abc_Ntk_t * pNtk, int fJFront )
{
    Abc_Obj_t * pNode, * pFanin, * pNodeC, * pNodeT, * pNodeE;
    Vec_Ptr_t * vNodes, * vSuper;
    Vec_Flt_t * vFactors;
    Vec_Int_t * vVars, * vFanio;
    Vec_Vec_t * vCircuit;
    int i, k, fUseMuxes = 1;
    int clk1 = clock(), clk;
    int fOrderCiVarsFirst = 0;
    int nLevelsMax = Abc_AigLevel(pNtk);
    int RetValue = 0;

    assert( Abc_NtkIsStrash(pNtk) );

    // clean the CI node pointers
    Abc_NtkForEachCi( pNtk, pNode, i )
        pNode->pCopy = NULL;

    // start the data structures
    vNodes  = Vec_PtrAlloc( 1000 );   // the nodes corresponding to vars in the solver
    vSuper  = Vec_PtrAlloc( 100 );    // the nodes belonging to the given implication supergate
    vVars   = Vec_IntAlloc( 100 );    // the temporary array for variables in the clause
    if ( fJFront )
        vCircuit = Vec_VecAlloc( 1000 );
//        vCircuit = Vec_VecStart( 184 );

    // add the clause for the constant node
    pNode = Abc_AigConst1(pNtk);
    pNode->fMarkA = 1;
    pNode->pCopy = (Abc_Obj_t *)vNodes->nSize;
    Vec_PtrPush( vNodes, pNode );
    Abc_NtkClauseTriv( pSat, pNode, vVars );
/*
    // add the PI variables first
    Abc_NtkForEachCi( pNtk, pNode, i )
    {
        pNode->fMarkA = 1;
        pNode->pCopy = (Abc_Obj_t *)vNodes->nSize;
        Vec_PtrPush( vNodes, pNode );
    }
*/
    // collect the nodes that need clauses and top-level assignments
    Vec_PtrClear( vSuper );
    Abc_NtkForEachCo( pNtk, pNode, i )
    {
        // get the fanin
        pFanin = Abc_ObjFanin0(pNode);
        // create the node's variable
        if ( pFanin->fMarkA == 0 )
        {
            pFanin->fMarkA = 1;
            pFanin->pCopy = (Abc_Obj_t *)vNodes->nSize;
            Vec_PtrPush( vNodes, pFanin );
        }
        // add the trivial clause
        Vec_PtrPush( vSuper, Abc_ObjChild0(pNode) );
    }
    if ( !Abc_NtkClauseTop( pSat, vSuper, vVars ) )
        goto Quits;


    // add the clauses
    Vec_PtrForEachEntry( vNodes, pNode, i )
    {
        assert( !Abc_ObjIsComplement(pNode) );
        if ( !Abc_AigNodeIsAnd(pNode) )
            continue;
//printf( "%d ", pNode->Id );

        // add the clauses
        if ( fUseMuxes && Abc_NodeIsMuxType(pNode) )
        {
            nMuxes++;

            pNodeC = Abc_NodeRecognizeMux( pNode, &pNodeT, &pNodeE );
            Vec_PtrClear( vSuper );
            Vec_PtrPush( vSuper, pNodeC );
            Vec_PtrPush( vSuper, pNodeT );
            Vec_PtrPush( vSuper, pNodeE );
            // add the fanin nodes to explore
            Vec_PtrForEachEntry( vSuper, pFanin, k )
            {
                pFanin = Abc_ObjRegular(pFanin);
                if ( pFanin->fMarkA == 0 )
                {
                    pFanin->fMarkA = 1;
                    pFanin->pCopy = (Abc_Obj_t *)vNodes->nSize;
                    Vec_PtrPush( vNodes, pFanin );
                }
            }
            // add the clauses
            if ( !Abc_NtkClauseMux( pSat, pNode, pNodeC, pNodeT, pNodeE, vVars ) )
                goto Quits;
        }
        else
        {
            // get the supergate
            Abc_NtkCollectSupergate( pNode, fUseMuxes, vSuper );
            // add the fanin nodes to explore
            Vec_PtrForEachEntry( vSuper, pFanin, k )
            {
                pFanin = Abc_ObjRegular(pFanin);
                if ( pFanin->fMarkA == 0 )
                {
                    pFanin->fMarkA = 1;
                    pFanin->pCopy = (Abc_Obj_t *)vNodes->nSize;
                    Vec_PtrPush( vNodes, pFanin );
                }
            }
            // add the clauses
            if ( vSuper->nSize == 0 )
            {
                if ( !Abc_NtkClauseTriv( pSat, Abc_ObjNot(pNode), vVars ) )
//                if ( !Abc_NtkClauseTriv( pSat, pNode, vVars ) )
                    goto Quits;
            }
            else
            {
                if ( !Abc_NtkClauseAnd( pSat, pNode, vSuper, vVars ) )
                    goto Quits;
            }
        }
        // add the variables to the J-frontier
        if ( !fJFront )
            continue;
        // make sure that the fanin entries go first
        assert( pNode->pCopy );
        Vec_VecExpand( vCircuit, (int)pNode->pCopy );
        vFanio = Vec_VecEntry( vCircuit, (int)pNode->pCopy );
        Vec_PtrForEachEntryReverse( vSuper, pFanin, k )
//        Vec_PtrForEachEntry( vSuper, pFanin, k )
        {
            pFanin = Abc_ObjRegular( pFanin );
            assert( pFanin->pCopy && pFanin->pCopy != pNode->pCopy );
            Vec_IntPushFirst( vFanio, (int)pFanin->pCopy );
            Vec_VecPush( vCircuit, (int)pFanin->pCopy, pNode->pCopy );
        }
    }

    // set preferred variables
    if ( fOrderCiVarsFirst )
    {
        int * pPrefVars = ALLOC( int, Abc_NtkCiNum(pNtk) );
        int nVars = 0;
        Abc_NtkForEachCi( pNtk, pNode, i )
        {
            if ( pNode->fMarkA == 0 )
                continue;
            pPrefVars[nVars++] = (int)pNode->pCopy;
        }
        nVars = ABC_MIN( nVars, 10 );
        Asat_SolverSetPrefVars( pSat, pPrefVars, nVars );
    }

    // create the variable order
    if ( fJFront )
    {
    clk = clock();
        Asat_JManStart( pSat, vCircuit );
        Vec_VecFree( vCircuit );
    PRT( "Setup", clock() - clk );
//        Asat_JManStop( pSat );
//    PRT( "Total", clock() - clk1 );
    }

    Abc_NtkStartReverseLevels( pNtk );
    vFactors = Vec_FltStart( solver_nvars(pSat) );
    Abc_NtkForEachNode( pNtk, pNode, i )
        if ( pNode->fMarkA )
            Vec_FltWriteEntry( vFactors, (int)pNode->pCopy, (float)pow(0.97, Abc_NodeReadReverseLevel(pNode)) );
    Abc_NtkForEachCi( pNtk, pNode, i )
        if ( pNode->fMarkA )
            Vec_FltWriteEntry( vFactors, (int)pNode->pCopy, (float)pow(0.97, nLevelsMax+1) );
    // set the PI levels
//    Abc_NtkForEachObj( pNtk, pNode, i )
//        if ( pNode->fMarkA )
//            printf( "(%d) %.3f   ", Abc_NodeReadReverseLevel(pNode), Vec_FltEntry(vFactors, (int)pNode->pCopy) );
//    printf( "\n" );
    Asat_SolverSetFactors( pSat, Vec_FltReleaseArray(vFactors) );
    Vec_FltFree( vFactors );

/*
    // create factors
    vLevels = Vec_IntStart( Vec_PtrSize(vNodes) );   // the reverse levels of the nodes
    Abc_NtkForEachObj( pNtk, pNode, i )
        if ( pNode->fMarkA )
            Vec_IntWriteEntry( vLevels, (int)pNode->pCopy, Abc_NtkNodeFactor(pNode, nLevelsMax) );
    assert( Vec_PtrSize(vNodes) == Vec_IntSize(vLevels) );
    Asat_SolverSetFactors( pSat, Vec_IntReleaseArray(vLevels) );
    Vec_IntFree( vLevels );
*/
    RetValue = 1;
Quits :
    // delete
    Vec_IntFree( vVars );
    Vec_PtrFree( vNodes );
    Vec_PtrFree( vSuper );
    return RetValue;
}

/**Function*************************************************************

  Synopsis    [Sets up the SAT solver.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
solver * Abc_NtkMiterSatCreate( Abc_Ntk_t * pNtk, int fJFront )
{
    solver * pSat;
    Abc_Obj_t * pNode;
    int RetValue, i, clk = clock();

    nMuxes = 0;

    pSat = solver_new();
    RetValue = Abc_NtkMiterSatCreateInt( pSat, pNtk, fJFront );
    Abc_NtkForEachObj( pNtk, pNode, i )
        pNode->fMarkA = 0;
//    Asat_SolverWriteDimacs( pSat, "temp_sat.cnf", NULL, NULL, 1 );
    if ( RetValue == 0 )
    {
        solver_delete(pSat);
        return NULL;
    }
//    printf( "Ands = %6d.  Muxes = %6d (%5.2f %%).  ", Abc_NtkNodeNum(pNtk), nMuxes, 300.0*nMuxes/Abc_NtkNodeNum(pNtk) );
//    PRT( "Creating solver", clock() - clk );
    return pSat;
}


////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////


