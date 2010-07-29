/**CFile****************************************************************

  FileName    [sky.h]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Universal netlist with boxes.]

  Synopsis    [External declarations.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 20, 2005.]

  Revision    [$Id: sky.h,v 1.00 2005/06/20 00:00:00 alanmi Exp $]

***********************************************************************/

#ifndef __SKY_H__
#define __SKY_H__

////////////////////////////////////////////////////////////////////////
///                          INCLUDES                                ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                         PARAMETERS                               ///
////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////
///                         BASIC TYPES                              ///
////////////////////////////////////////////////////////////////////////

typedef struct Sky_Man_t_           Sky_Man_t;
typedef struct Sky_Mod_t_           Sky_Mod_t;

typedef struct Sky_PstPar_t_        Sky_PstPar_t;
struct Sky_PstPar_t_
{
    int        fReportAll;
    int        fReportBest;
    int        fReportInstances;
    int        fReportDangling;
    int        fReportFlops;
    int        fReportFanio;
    int        fReportMemory;
    int        fReportNpn;
    int        fReportMffc;
    int        fReportTiming;
    int        fReportPath;
    int        fSkipLut1;
    int        nCritPaths;
};

typedef struct Sky_RetPar_t_        Sky_RetPar_t;
struct Sky_RetPar_t_
{
    int        nIterMax;
    int        nTimeWin;
    int        fForward;
    int        fBackward;
    int        fVerbose;
    int        fVeryVerbose;
};

typedef struct Sky_RsnPar_t_        Sky_RsnPar_t;
struct Sky_RsnPar_t_
{
    // user parameters
    int        nPerPerturbed;  // percentage of touched objects 
    int        nPerIncrease;   // percentage of area increase
    int        nPerCritPath;   // percentage of nodes on the critical path
    int        nPerNodeCrit;   // determines criticallity of the node
    int        fUnplaceTouch;  // unplace all touched objects
    int        fSelectByCost;  // alternative algo to select cones
    int        fVerbose;       // verbose output
    int        fVeryVerbose;   // very verbose output
    // internal parameters
    int        nCritSlackTh;   // delay bound on critical slack
    int        nCritWeightTh;  // delay bound on critical node weight
    int        nPerturbMax;    // the max object to be perturbed
    int        nLevelMax;      // maximum level 
    int        nDelayMax;      // maximum delay 
    int        nUnitWireDelay; // affective unit delay expressed using wire delay 
    // computed parameters
    int        nPassThroughs;  // passing through
};

typedef struct Sky_RmePar_t_        Sky_RmePar_t;
struct Sky_RmePar_t_
{
    // user parameters
    int        nPerPerturbed;  // percentage of touched objects 
    int        nPerIncrease;   // percentage of area increase
    int        nPerTimeWnd;    // percentage of max delay to highlight the critical region
    int        nPerNotUseful;  // percentage of max delay to not use the result
    int        nNodesMax;      // the max number of nodes retimed without improvement
    int        fUnplaceTouch;  // unplace all touched objects
    int        fForward;       // perform only forward retiming
    int        fInsertFirst;   // insert new node at the head of the queue
    int        fRandWDelays;   // generate random wire-delay info
    int        fVerbose;       // verbose output
    int        fVeryVerbose;   // very verbose output
    int        fVeryVerbose2;  // very verbose output
    // internal parameters
    int        nPerturbMax;    // the max object to be perturbed
    int        nLevelMax;      // maximum level 
    int        nDelayMax;      // maximum delay 
    int        nUnitWireDelay; // affective unit delay expressed using wire delay 
    int        nArrTimeTarget; // the target arrival time
};

typedef struct Sky_PerPar_t_  Sky_PerPar_t;
struct Sky_PerPar_t_
{
    // user parameters
    int        nLutSize;       // the LUT size from the set {4,5,6}
    int        nItersMax;      // maximum number of attempts
    int        fMapEval;       // evaluate current mapping
    int        fVerbose;       // verbose output
    int        fVeryVerbose;   // very verbose output
    // internal parameters
    int        PeriodMax;      // upper bound on the clock period
    int        Period;         // current clock period
};

typedef struct Sky_RsfPar_t_        Sky_RsfPar_t;
struct Sky_RsfPar_t_
{
    // user parameters
    int        nPerTimeWnd;    // max percentage of allowed timing improvement
    int        nPerAreaInc;    // max percentage of allowed area increase
    int        nPerNotUseful;  // percentage of max delay to not use the result
    int        nAddLutDelays;  // the number of LUT delay added for each level
    int        fUnplaceTouch;  // unplace all touched objects
    int        fVerbose;       // verbose output
    int        fVeryVerbose;   // very verbose output
    // internal parameters
    int        nDelayMax;      // maximum delay 
    int        nCritSlackTh;   // delay bound on critical slack
    int        nCritWeightTh;  // delay bound on critical node weight
    int        nCritSlackBest; // maximum delay improvement
    int        nCritInouts;    // critical inputs/outputs
};

////////////////////////////////////////////////////////////////////////
///                      MACRO DEFINITIONS                           ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                    FUNCTION DECLARATIONS                         ///
////////////////////////////////////////////////////////////////////////

/*=== sky.c ======================================================================*/
/*=== skyBest.c ==================================================================*/
extern ABC_DLL int             Sky_ManCompareWithBest( Sky_Man_t * p );
/*=== skyCheck.c =================================================================*/
/*=== skyCleanup.c ===============================================================*/
extern ABC_DLL Sky_Man_t *     Sky_ManCleanupSeq( Sky_Man_t * p, int fVerbose );
/*=== skyCore.c ==================================================================*/
extern ABC_DLL Sky_Man_t *     Sky_ManPerformBalance( Sky_Man_t * p, int fExor, int fUpdateLevel, int fVerbose );
extern ABC_DLL Sky_Man_t *     Sky_ManPerformDc2( Sky_Man_t * p, int fBalance, int fUpdateLevel, int fVerbose );
extern ABC_DLL Sky_Man_t *     Sky_ManPerformDch( Sky_Man_t * p, void * pPars );
extern ABC_DLL Sky_Man_t *     Sky_ManPerformBidec( Sky_Man_t * p, int fVerbose );
extern ABC_DLL Sky_Man_t *     Sky_ManPerformMapShrink( Sky_Man_t * p, int fKeepLevel, int fVerbose );
extern ABC_DLL float           Sky_ManTrace( Sky_Man_t * p, void * pLutLib, int fVerbose );
extern ABC_DLL Sky_Man_t *     Sky_ManSpeedup( Sky_Man_t * p, void * pLutLib, int Percentage, int Degree, int fVerbose, int fVeryVerbose );
/*=== skyDfs.c ===================================================================*/
/*=== skyDress.c =================================================================*/
extern ABC_DLL Sky_Man_t *     Sky_ManDress( Sky_Man_t * p0, Sky_Man_t * p1, int nBTLimit, int fPolarity, int fVerbose, int fVeryVerbose );
/*=== skyExtract.c ===============================================================*/
extern ABC_DLL Gia_Man_t *     Sky_ManExtract( Sky_Man_t * p );
extern ABC_DLL Gia_Man_t *     Sky_ManCollapseComb( Sky_Man_t * p );
extern ABC_DLL Gia_Man_t *     Sky_ManCollapseSeq( Sky_Man_t * p );
/*=== skyIf.c ====================================================================*/
extern ABC_DLL void            Sky_ManSetIfParsDefault( void * pPars );
extern ABC_DLL Sky_Man_t *     Sky_ManMappingIf( Sky_Man_t * p, void * pPars );
extern ABC_DLL Sky_Man_t *     Sky_ManMappingIfLogic( Sky_Man_t * p, void * pPars );
/*=== skyLog.c =================================================================*/
extern ABC_DLL void            Sky_ManLogDump( Sky_Man_t * p, char * pFileName );
/*=== skyLogic.c =================================================================*/
extern ABC_DLL Sky_Man_t *     Sky_ManLogic( Sky_Man_t * p, int fOldAlgo, int fTrueFanins, int nSlackMin );
extern ABC_DLL Sky_Man_t *     Sky_ManLogicAig( Sky_Man_t * p );
extern ABC_DLL Sky_Man_t *     Sky_ManUnmap( Sky_Man_t * p );
extern ABC_DLL Sky_Man_t *     Sky_ManShortNames( Sky_Man_t * p );
/*=== skyMan.c ===================================================================*/
extern ABC_DLL void            Sky_ManFree( Sky_Man_t * p );
extern ABC_DLL void            Sky_ManFreeP( void ** p );
extern ABC_DLL Sky_Man_t *     Sky_ManDup( Sky_Man_t * p, Sky_Mod_t*(*pFuncModDup)(Sky_Man_t*,Sky_Mod_t*,int) );
extern ABC_DLL Sky_Mod_t *     Sky_ManReadRoot( Sky_Man_t * p );
/*=== skyName.c ==================================================================*/
/*=== skyObj.c ===================================================================*/
/*=== skyPrint.c =================================================================*/
extern ABC_DLL void            Sky_ManPrintStats( Sky_Man_t * p, Sky_PstPar_t * pPars );
/*=== skyReadBlif.c ==============================================================*/
extern ABC_DLL Sky_Man_t *     Sky_ManReadBlif( Sky_Man_t * pOld, char * pFileName, int fReadPlace, int fReadDelay, int fCheck );
extern ABC_DLL Sky_Man_t *     Sky_ManPrepareOne( char * pFileName, int fSaveNodeNames );
/*=== skySeq.c ===================================================================*/
extern ABC_DLL Sky_Man_t *     Sky_ManSeqSynthesis( Sky_Man_t * p, void * pSynPars, int fIgnoreAsync );
extern ABC_DLL Sky_Man_t *     Sky_ManFraig( Sky_Man_t * p, void * pDchPars );
/*=== skyStats.c =================================================================*/
extern ABC_DLL char *          Sky_ManName( Sky_Man_t * p );
extern ABC_DLL char *          Sky_ManSpec( Sky_Man_t * p );
extern ABC_DLL void            Sky_ManSetName( Sky_Man_t * p, char * pName );
extern ABC_DLL void            Sky_ManSetSpec( Sky_Man_t * p, char * pSpec );
extern ABC_DLL int             Sky_ManHasCboices( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManIsStrashed( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManIsMapped( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManPiNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManPoNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManFfNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManBoxNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManSeqBoxNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManSeqWhiteBoxNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManSeqBlackBoxNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManCombBoxNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManCombWhiteBoxNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManCombBlackBoxNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManNodeNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManNode0Num( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManNode1Num( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManNode2pNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManAigLevelNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManMappedLevelNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManAndNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManObjNum( Sky_Man_t * p );
extern ABC_DLL int             Sky_ManEdgeNum( Sky_Man_t * p );
extern ABC_DLL float           Sky_ManDelay( Sky_Man_t * p, void * pLutLib );
/*=== skyStrash.c ================================================================*/
extern ABC_DLL Sky_Man_t *     Sky_ManStrash( Sky_Man_t * p );
/*=== skySweep.c =================================================================*/
extern ABC_DLL Sky_Man_t *     Sky_ManLogicSweep( Sky_Man_t * p, int fVerbose );
/*=== skySym.c =================================================================*/
extern ABC_DLL Sky_Man_t *     Sky_ManWireSwap( Sky_Man_t * p, int fVerbose );
/*=== skyUtil.c ==================================================================*/
/*=== skyVerify.c ================================================================*/
extern ABC_DLL int             Sky_ManPrepareVerification( Sky_Man_t * pMan, char ** argv, int argc, 
                               Sky_Man_t ** ppMan1, Sky_Man_t ** ppMan2, int * pfDelete1, int * pfDelete2 );
extern ABC_DLL int             Sky_ManVerifyCec( Sky_Man_t * p1, Sky_Man_t * p2, int fClp, int fDumpMiter, int fVerbose );
extern ABC_DLL int             Sky_ManVerifySec( Sky_Man_t * p1, Sky_Man_t * p2, void * pSecPars, int fDumpMiter, int fIgnoreAsync );
extern ABC_DLL int             Sky_ManVerifySim( Sky_Man_t * p1, Sky_Man_t * p2, Gia_ParSim_t * pSimPars, int fDumpMiter, int fIgnoreAsync );
/*=== skyWriteBlif.c =============================================================*/
extern ABC_DLL void            Sky_ManWriteBlif( Sky_Man_t * p, char * pFileName, int fReverse );

/*=== rtiCore.c ==================================================================*/
extern ABC_DLL int             Rti_ManPeriod( Sky_Man_t * p, int fUnitDelay, int nItersMax, int fReverse, int fOneDir, int fVerbose );
extern ABC_DLL Sky_Man_t *     Rti_ManRetime( Sky_Man_t * p, Sky_RetPar_t * pPars );
/*=== rtiCore.c ==================================================================*/
extern ABC_DLL Sky_Man_t *     Rti_ManElaborate( Sky_Man_t * p, int fReset, int fEnable, int fVerbose );
/*=== rtiCrit.c ==================================================================*/
extern ABC_DLL Sky_Man_t *     Rti_ManResynthesize( Sky_Man_t * p, int nPerTouched, int nPerIncrease, int fVerbose );

/*=== rtiMap.c ==================================================================*/
extern ABC_DLL void            Rti_ManSetDefaultParams( Sky_PerPar_t * p );
extern ABC_DLL Sky_Man_t *     Rti_ManSeqMapping( Sky_Man_t * p, Sky_PerPar_t * pPars );
/*=== rtiFlow.c ==================================================================*/
extern ABC_DLL void            Rsf_ManSetDefaultParams( Sky_RsfPar_t * p );
extern ABC_DLL Sky_Man_t *     Rsf_ManResynthesize( Sky_Man_t * p, Sky_RsfPar_t * pPars );
/*=== rtiFront.c ==================================================================*/
extern ABC_DLL void            Rsn_ManSetDefaultParams( Sky_RsnPar_t * p );
extern ABC_DLL Sky_Man_t *     Rsn_ManResynthesize( Sky_Man_t * p, Sky_RsnPar_t * pPars );
/*=== rtiWave.c ==================================================================*/
extern ABC_DLL void            Rme_ManSetDefaultParams( Sky_Man_t * pSky, Sky_RmePar_t * p );
extern ABC_DLL Sky_Man_t *     Rme_ManRetime( Sky_Man_t * p, Sky_RmePar_t * pPars );

#ifdef __cplusplus
}
#endif

#endif

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////

