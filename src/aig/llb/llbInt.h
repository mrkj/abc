/**CFile****************************************************************

  FileName    [llbInt.h]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [BDD-based reachability.]

  Synopsis    [External declarations.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - May 8, 2010.]

  Revision    [$Id: llbInt.h,v 1.00 2010/05/08 00:00:00 alanmi Exp $]

***********************************************************************/
 
#ifndef __LLB_INT_H__
#define __LLB_INT_H__


////////////////////////////////////////////////////////////////////////
///                          INCLUDES                                ///
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "aig.h"
#include "saig.h"
#include "cuddInt.h"
#include "extra.h"
#include "llb.h"

////////////////////////////////////////////////////////////////////////
///                         PARAMETERS                               ///
////////////////////////////////////////////////////////////////////////



ABC_NAMESPACE_HEADER_START


////////////////////////////////////////////////////////////////////////
///                         BASIC TYPES                              ///
////////////////////////////////////////////////////////////////////////

typedef struct Llb_Man_t_ Llb_Man_t;
typedef struct Llb_Mtr_t_ Llb_Mtr_t;
typedef struct Llb_Grp_t_ Llb_Grp_t;

struct Llb_Man_t_
{
    Gia_ParLlb_t *  pPars;          // parameters
    Aig_Man_t *     pAigGlo;        // initial AIG manager (owned by the caller)
    Aig_Man_t *     pAig;           // derived AIG manager (created in this package)
    DdManager *     dd;             // BDD manager
    DdManager *     ddG;            // BDD manager
    Vec_Int_t *     vObj2Var;       // mapping AIG ObjId into BDD var index
    Vec_Int_t *     vVar2Obj;       // mapping BDD var index into AIG ObjId
    Vec_Ptr_t *     vGroups;        // group Id into group pointer
    Llb_Mtr_t *     pMatrix;        // dependency matrix
    // image computation
    Vec_Int_t *     vVarBegs;       // the first group where the var appears  
    Vec_Int_t *     vVarEnds;       // the last group where the var appears 
    // variable mapping
    Vec_Int_t *     vNs2Glo;        // next state variables into global variables
    Vec_Int_t *     vGlo2Cs;        // global variables into current state variables
    // flow computation
//    Vec_Int_t *     vMem;
//    Vec_Ptr_t *     vTops;
//    Vec_Ptr_t *     vBots;
//    Vec_Ptr_t *     vCuts;
};

struct Llb_Mtr_t_
{
    int             nPis;           // number of primary inputs
    int             nFfs;           // number of flip-flops
    int             nRows;          // number of rows
    int             nCols;          // number of columns
    int *           pColSums;       // sum of values in a column
    Llb_Grp_t **    pColGrps;       // group structure for each col
    int *           pRowSums;       // sum of values in a row
    char **         pMatrix;        // dependency matrix
    Llb_Man_t *     pMan;           // manager
    // partial product
    char *          pProdVars;      // variables in the partial product
    int *           pProdNums;      // var counts in the remaining partitions
};

struct Llb_Grp_t_
{
    int             Id;             // group ID
    Vec_Ptr_t *     vIns;           // input AIG objs
    Vec_Ptr_t *     vOuts;          // output AIG objs
    Vec_Ptr_t *     vNodes;         // internal AIG objs
    Llb_Man_t *     pMan;           // manager
    Llb_Grp_t *     pPrev;          // previous group
    Llb_Grp_t *     pNext;          // next group
};

////////////////////////////////////////////////////////////////////////
///                      MACRO DEFINITIONS                           ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                    FUNCTION DECLARATIONS                         ///
////////////////////////////////////////////////////////////////////////

/*=== llbCex.c =======================================================*/
extern Abc_Cex_t *     Llb_ManDeriveCex( Llb_Man_t * p, DdNode * bInter, int iOutFail, int iIter );
/*=== llbConstr.c ======================================================*/
extern Vec_Int_t *     Llb_ManDeriveConstraints( Aig_Man_t * p );
extern void            Llb_ManPrintEntries( Aig_Man_t * p, Vec_Int_t * vCands );
/*=== llbCore.c ======================================================*/
extern int             Llb_ManModelCheckAig( Aig_Man_t * pAigGlo, Gia_ParLlb_t * pPars, Vec_Int_t * vHints, DdManager ** pddGlo );
/*=== llbCluster.c ======================================================*/
extern void            Llb_ManCluster( Llb_Mtr_t * p );
/*=== llbFlow.c ======================================================*/
extern Llb_Man_t *     Llb_ManStartFlow( Aig_Man_t * pAigGlo, Aig_Man_t * pAig, Gia_ParLlb_t * pPars );
/*=== llbHint.c ======================================================*/
extern int             Llb_ManReachabilityWithHints( Llb_Man_t * p );
extern int             Llb_ManModelCheckAigWithHints( Aig_Man_t * pAigGlo, Gia_ParLlb_t * pPars );
/*=== llbMan.c =======================================================*/
extern void            Llb_ManPrepareVarMap( Llb_Man_t * p );
extern Llb_Man_t *     Llb_ManStart( Aig_Man_t * pAigGlo, Aig_Man_t * pAig, Gia_ParLlb_t *  pPars );
extern void            Llb_ManStop( Llb_Man_t * p );
/*=== llbMatrix.c ====================================================*/
extern void            Llb_MtrVerifyMatrix( Llb_Mtr_t * p );
extern Llb_Mtr_t *     Llb_MtrCreate( Llb_Man_t * p );
extern void            Llb_MtrFree( Llb_Mtr_t * p );
extern void            Llb_MtrPrint( Llb_Mtr_t * p, int fOrder );
extern void            Llb_MtrPrintMatrixStats( Llb_Mtr_t * p );
/*=== llbPart.c ======================================================*/
extern Llb_Grp_t *     Llb_ManGroupAlloc( Llb_Man_t * pMan );
extern void            Llb_ManGroupStop( Llb_Grp_t * p );
extern void            Llb_ManPrepareGroups( Llb_Man_t * pMan );
extern Llb_Grp_t *     Llb_ManGroupsCombine( Llb_Grp_t * p1, Llb_Grp_t * p2 );
extern Llb_Grp_t *     Llb_ManGroupCreateFromCuts( Llb_Man_t * pMan, Vec_Int_t * vCut1, Vec_Int_t * vCut2 );
extern void            Llb_ManPrepareVarLimits( Llb_Man_t * p );
/*=== llbPivot.c =====================================================*/
extern int             Llb_ManTracePaths( Aig_Man_t * p, Aig_Obj_t * pPivot );
extern Vec_Int_t *     Llb_ManMarkPivotNodes( Aig_Man_t * p, int fUseInternal );
/*=== llbReach.c =====================================================*/
extern int             Llb_ManReachability( Llb_Man_t * p, Vec_Int_t * vHints, DdManager ** pddGlo );
/*=== llbSched.c =====================================================*/
extern void            Llb_MtrSchedule( Llb_Mtr_t * p );



ABC_NAMESPACE_HEADER_END



#endif

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////

