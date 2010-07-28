/**CFile****************************************************************

  FileName    [cgtInt.h]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Clock gating package.]

  Synopsis    [Internal declarations.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 20, 2005.]

  Revision    [$Id: cgtInt.h,v 1.00 2005/06/20 00:00:00 alanmi Exp $]

***********************************************************************/
 
#ifndef __CGT_INT_H__
#define __CGT_INT_H__

////////////////////////////////////////////////////////////////////////
///                          INCLUDES                                ///
////////////////////////////////////////////////////////////////////////

#include "saig.h"
#include "satSolver.h"
#include "cnf.h"
#include "cgt.h"

////////////////////////////////////////////////////////////////////////
///                         PARAMETERS                               ///
////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////
///                         BASIC TYPES                              ///
////////////////////////////////////////////////////////////////////////

typedef struct Cgt_Man_t_ Cgt_Man_t;
struct Cgt_Man_t_
{
    // user's data
    Cgt_Par_t *  pPars;          // user's parameters
    Aig_Man_t *  pAig;           // user's AIG manager
    // user's constraints
    Aig_Man_t *  pCare;          // constraint cones
    Vec_Vec_t *  vSuppsInv;      // inverse support of the constraints
    // result of clock-gating
    Vec_Vec_t *  vGatesAll;      // the computed clock-gates
    Vec_Ptr_t *  vGates;         // the selected clock-gates
    // internal data
    Aig_Man_t *  pFrame;         // clock gate AIG manager
    Vec_Ptr_t *  vFanout;        // temporary storage for fanouts
    Vec_Ptr_t *  vVisited;       // temporary storage for visited nodes
    // SAT solving
    Aig_Man_t *  pPart;          // partition
    Cnf_Dat_t *  pCnf;           // CNF of the partition
    sat_solver * pSat;           // SAT solver 
    Vec_Ptr_t *  vPatts;         // simulation patterns
    int          nPatts;         // the number of patterns accumulated
    int          nPattWords;     // the number of pattern words
    // statistics
    int          nRecycles;      // recycles 
    int          nCalls;         // total calls
    int          nCallsSat;      // satisfiable calls
    int          nCallsUnsat;    // unsatisfiable calls  
    int          nCallsUndec;    // undecided calls
    int          nCallsFiltered; // filtered out calls
    int          timeAig;        // constructing AIG
    int          timePrepare;    // partitioning and SAT solving
    int          timeSat;        // total runtime
    int          timeSatSat;     // satisfiable runtime 
    int          timeSatUnsat;   // unsatisfiable runtime 
    int          timeSatUndec;   // undecided runtime
    int          timeDecision;   // making decision about what gates to use
    int          timeOther;      // other runtime
    int          timeTotal;      // total runtime
};

////////////////////////////////////////////////////////////////////////
///                      MACRO DEFINITIONS                           ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                    FUNCTION DECLARATIONS                         ///
////////////////////////////////////////////////////////////////////////

/*=== cgtAig.c ==========================================================*/
extern void             Cgt_ManDetectCandidates( Aig_Man_t * pAig, Aig_Obj_t * pObj, int nLevelMax, Vec_Ptr_t * vCands );
extern Aig_Man_t *      Cgt_ManDeriveAigForGating( Cgt_Man_t * p );
extern Aig_Man_t *      Cgt_ManDupPartition( Aig_Man_t * pAig, int nVarsMin, int nFlopsMin, int iStart, Aig_Man_t * pCare, Vec_Vec_t * vSuppsInv, int * pnOutputs );
extern Aig_Man_t *      Cgt_ManDeriveGatedAig( Aig_Man_t * pAig, Vec_Vec_t * vGates, int fReduce, int * pnUsedNodes );
/*=== cgtDecide.c ==========================================================*/
extern Vec_Vec_t *      Cgt_ManDecideSimple( Aig_Man_t * pAig, Vec_Vec_t * vGatesAll, int nOdcMax, int fVerbose );
extern Vec_Vec_t *      Cgt_ManDecideArea( Aig_Man_t * pAig, Vec_Vec_t * vGatesAll, int nOdcMax, int fVerbose );
/*=== cgtMan.c ==========================================================*/
extern Cgt_Man_t *      Cgt_ManCreate( Aig_Man_t * pAig, Aig_Man_t * pCare, Cgt_Par_t * pPars );
extern void             Cgt_ManClean( Cgt_Man_t * p );
extern void             Cgt_ManStop( Cgt_Man_t * p );
/*=== cgtSat.c ==========================================================*/
extern int              Cgt_CheckImplication( Cgt_Man_t * p, Aig_Obj_t * pGate, Aig_Obj_t * pFlop );

#ifdef __cplusplus
}
#endif

#endif

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////
