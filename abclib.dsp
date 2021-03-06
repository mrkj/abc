# Microsoft Developer Studio Project File - Name="abclib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=abclib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "abclib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "abclib.mak" CFG="abclib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "abclib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "abclib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "abclib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseLib"
# PROP BASE Intermediate_Dir "ReleaseLib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseLib"
# PROP Intermediate_Dir "ReleaseLib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "src/aig/_rti" /I "src/aig/_bat" /I "src/base/abc" /I "src/base/abci" /I "src/base/cmd" /I "src/base/io" /I "src/base/main" /I "src/base/ver" /I "src/bdd/cudd" /I "src/bdd/dsd" /I "src/bdd/epd" /I "src/bdd/mtr" /I "src/bdd/parse" /I "src/bdd/reo" /I "src/bdd/cas" /I "src/map/cov" /I "src/map/fpga" /I "src/map/mapper" /I "src/map/mio" /I "src/map/super" /I "src/map/if" /I "src/map/pcm" /I "src/map/ply" /I "src/misc/extra" /I "src/misc/mvc" /I "src/misc/st" /I "src/misc/util" /I "src/misc/espresso" /I "src/misc/nm" /I "src/misc/vec" /I "src/misc/hash" /I "src/misc/bzlib" /I "src/misc/zlib" /I "src/opt/cut" /I "src/opt/dec" /I "src/opt/fxu" /I "src/opt/rwr" /I "src/opt/sim" /I "src/opt/ret" /I "src/opt/res" /I "src/opt/lpk" /I "src/sat/bsat" /I "src/sat/csat" /I "src/sat/msat" /I "src/sat/fraig" /I "src/sat/nsat" /I "src/sat/psat" /I "src/aig/ivy" /I "src/aig/hop" /I "src/aig/rwt" /I "src/aig/deco" /I "src/aig/mem" /I "src/aig/dar" /I "src/aig/fra" /I "src/aig/cnf" /I "src/aig/csw" /I "src/aig/ioa" /I "src/aig/aig" /I "src/aig/kit" /I "src/aig/bdc" /I "src/aig/bar" /I "src/aig/ntl" /I "src/aig/nwk" /I "src/aig/tim" /I "src/opt/mfs" /I "src/aig/mfx" /I "src/aig/saig" /I "src/aig/bbr" /I "src/aig/int" /I "src/aig/dch" /I "src/aig/ssw" /I "src/sat/lsat" /I "src/aig/cec" /I "src/aig/cgt" /I "src/aig/sec" /I "src/map/amap" /I "src/aig/fsim" /I "src/aig/gia" /I "src/aig/bbl" /I "src/aig/sky" /I "src/aig/_sky" /I "src/aig/llb" /I "src/aig/_nal" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D ABC_DLL=ABC_DLLEXPORT /D "_CRT_SECURE_NO_DEPRECATE" /FR /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\abcr.lib"

!ELSEIF  "$(CFG)" == "abclib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugLib"
# PROP BASE Intermediate_Dir "DebugLib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugLib"
# PROP Intermediate_Dir "DebugLib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "src/aig/_rti" /I "src/aig/_bat" /I "src/base/abc" /I "src/base/abci" /I "src/base/cmd" /I "src/base/io" /I "src/base/main" /I "src/base/ver" /I "src/bdd/cudd" /I "src/bdd/dsd" /I "src/bdd/epd" /I "src/bdd/mtr" /I "src/bdd/parse" /I "src/bdd/reo" /I "src/bdd/cas" /I "src/map/cov" /I "src/map/fpga" /I "src/map/mapper" /I "src/map/mio" /I "src/map/super" /I "src/map/if" /I "src/map/pcm" /I "src/map/ply" /I "src/misc/extra" /I "src/misc/mvc" /I "src/misc/st" /I "src/misc/util" /I "src/misc/espresso" /I "src/misc/nm" /I "src/misc/vec" /I "src/misc/hash" /I "src/misc/bzlib" /I "src/misc/zlib" /I "src/opt/cut" /I "src/opt/dec" /I "src/opt/fxu" /I "src/opt/rwr" /I "src/opt/sim" /I "src/opt/ret" /I "src/opt/res" /I "src/opt/lpk" /I "src/sat/bsat" /I "src/sat/csat" /I "src/sat/msat" /I "src/sat/fraig" /I "src/sat/nsat" /I "src/sat/psat" /I "src/aig/ivy" /I "src/aig/hop" /I "src/aig/rwt" /I "src/aig/deco" /I "src/aig/mem" /I "src/aig/dar" /I "src/aig/fra" /I "src/aig/cnf" /I "src/aig/csw" /I "src/aig/ioa" /I "src/aig/aig" /I "src/aig/kit" /I "src/aig/bdc" /I "src/aig/bar" /I "src/aig/ntl" /I "src/aig/nwk" /I "src/aig/tim" /I "src/opt/mfs" /I "src/aig/mfx" /I "src/aig/saig" /I "src/aig/bbr" /I "src/aig/int" /I "src/aig/dch" /I "src/aig/ssw" /I "src/sat/lsat" /I "src/aig/cec" /I "src/aig/cgt" /I "src/aig/sec" /I "src/map/amap" /I "src/aig/fsim" /I "src/aig/gia" /I "src/aig/bbl" /I "src/aig/sky" /I "src/aig/_sky" /I "src/aig/llb" /I "src/aig/_nal" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D ABC_DLL=ABC_DLLEXPORT /D "_CRT_SECURE_NO_DEPRECATE" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\abcd.lib"

!ENDIF 

# Begin Target

# Name "abclib - Win32 Release"
# Name "abclib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "base"

# PROP Default_Filter ""
# Begin Group "abc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\base\abc\abc.h
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcAig.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcBlifMv.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcCheck.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcDfs.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcFanio.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcFunc.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcHie.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcInt.h
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcLatch.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcLib.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcMinBase.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcNames.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcNetlist.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcNtk.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcObj.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcRefs.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcShow.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcSop.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abc\abcUtil.c
# End Source File
# End Group
# Begin Group "abci"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\base\abci\abc.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcAbc8.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcAttach.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcAuto.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcBalance.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcBidec.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcBm.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcBmc.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcCas.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcCascade.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcCollapse.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcCut.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcDar.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcDebug.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcDress.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcDress2.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcDsd.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcExtract.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcFpga.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcFpgaFast.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcFraig.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcFxu.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcGen.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcHaig.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcIf.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcIfMux.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcIvy.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcLog.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcLut.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcLutmin.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcMap.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcMeasure.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcMerge.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcMini.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcMiter.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcMulti.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcMv.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcNtbdd.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcOdc.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcOrder.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcPart.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcPrint.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcProve.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcQbf.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcQuant.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcReach.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcReconv.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcRefactor.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcRenode.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcReorder.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcRestruct.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcResub.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcRewrite.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcRr.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcSat.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcScorr.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcSense.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcSpeedup.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcStrash.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcSweep.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcSymm.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcTiming.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcUnate.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcUnreach.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcVerify.c
# End Source File
# Begin Source File

SOURCE=.\src\base\abci\abcXsim.c
# End Source File
# End Group
# Begin Group "cmd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\base\cmd\cmd.c
# End Source File
# Begin Source File

SOURCE=.\src\base\cmd\cmd.h
# End Source File
# Begin Source File

SOURCE=.\src\base\cmd\cmdAlias.c
# End Source File
# Begin Source File

SOURCE=.\src\base\cmd\cmdApi.c
# End Source File
# Begin Source File

SOURCE=.\src\base\cmd\cmdFlag.c
# End Source File
# Begin Source File

SOURCE=.\src\base\cmd\cmdHist.c
# End Source File
# Begin Source File

SOURCE=.\src\base\cmd\cmdInt.h
# End Source File
# Begin Source File

SOURCE=.\src\base\cmd\cmdLoad.c
# End Source File
# Begin Source File

SOURCE=.\src\base\cmd\cmdUtils.c
# End Source File
# End Group
# Begin Group "io"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\base\io\io.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioabc.h
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioInt.h
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioReadAiger.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioReadBaf.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioReadBblif.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioReadBench.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioReadBlif.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioReadBlifAig.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioReadBlifMv.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioReadDsd.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioReadEdif.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioReadEqn.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioReadPla.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioReadVerilog.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioUtil.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteAiger.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteBaf.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteBblif.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteBench.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteBlif.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteBlifMv.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteBook.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteCnf.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteDot.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteEqn.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteGml.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteList.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWritePla.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteSmv.c
# End Source File
# Begin Source File

SOURCE=.\src\base\io\ioWriteVerilog.c
# End Source File
# End Group
# Begin Group "main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\base\main\libSupport.c
# End Source File
# Begin Source File

SOURCE=.\src\base\main\main.h
# End Source File
# Begin Source File

SOURCE=.\src\base\main\mainFrame.c
# End Source File
# Begin Source File

SOURCE=.\src\base\main\mainInit.c
# End Source File
# Begin Source File

SOURCE=.\src\base\main\mainInt.h
# End Source File
# Begin Source File

SOURCE=.\src\base\main\mainLib.c
# End Source File
# Begin Source File

SOURCE=.\src\base\main\mainUtils.c
# End Source File
# End Group
# Begin Group "ver"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\base\ver\ver.h
# End Source File
# Begin Source File

SOURCE=.\src\base\ver\verCore.c
# End Source File
# Begin Source File

SOURCE=.\src\base\ver\verFormula.c
# End Source File
# Begin Source File

SOURCE=.\src\base\ver\verParse.c
# End Source File
# Begin Source File

SOURCE=.\src\base\ver\verStream.c
# End Source File
# End Group
# Begin Group "dummy"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\base\dummy\dummy_old.c
# End Source File
# End Group
# Begin Group "dummy2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\base\dummy2\dummy2.c
# End Source File
# End Group
# End Group
# Begin Group "bdd"

# PROP Default_Filter ""
# Begin Group "cudd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\bdd\cudd\cudd.h
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddAddAbs.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddAddApply.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddAddFind.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddAddInv.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddAddIte.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddAddNeg.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddAddWalsh.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddAndAbs.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddAnneal.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddApa.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddAPI.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddApprox.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddBddAbs.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddBddCorr.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddBddIte.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddBridge.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddCache.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddCheck.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddClip.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddCof.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddCompose.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddDecomp.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddEssent.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddExact.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddExport.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddGenCof.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddGenetic.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddGroup.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddHarwell.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddInit.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddInt.h
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddInteract.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddLCache.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddLevelQ.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddLinear.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddLiteral.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddMatMult.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddPriority.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddRead.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddRef.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddReorder.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddSat.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddSign.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddSolve.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddSplit.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddSubsetHB.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddSubsetSP.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddSymmetry.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddTable.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddUtil.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddWindow.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddZddCount.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddZddFuncs.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddZddGroup.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddZddIsop.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddZddLin.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddZddMisc.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddZddPort.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddZddReord.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddZddSetop.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddZddSymm.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cudd\cuddZddUtil.c
# End Source File
# End Group
# Begin Group "epd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\bdd\epd\epd.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\epd\epd.h
# End Source File
# End Group
# Begin Group "mtr"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\bdd\mtr\mtr.h
# End Source File
# Begin Source File

SOURCE=.\src\bdd\mtr\mtrBasic.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\mtr\mtrGroup.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\mtr\mtrInt.h
# End Source File
# End Group
# Begin Group "parse"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\bdd\parse\parse.h
# End Source File
# Begin Source File

SOURCE=.\src\bdd\parse\parseCore.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\parse\parseEqn.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\parse\parseInt.h
# End Source File
# Begin Source File

SOURCE=.\src\bdd\parse\parseStack.c
# End Source File
# End Group
# Begin Group "dsd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\bdd\dsd\dsd.h
# End Source File
# Begin Source File

SOURCE=.\src\bdd\dsd\dsdApi.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\dsd\dsdCheck.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\dsd\dsdInt.h
# End Source File
# Begin Source File

SOURCE=.\src\bdd\dsd\dsdLocal.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\dsd\dsdMan.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\dsd\dsdProc.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\dsd\dsdTree.c
# End Source File
# End Group
# Begin Group "reo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\bdd\reo\reo.h
# End Source File
# Begin Source File

SOURCE=.\src\bdd\reo\reoApi.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\reo\reoCore.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\reo\reoProfile.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\reo\reoShuffle.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\reo\reoSift.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\reo\reoSwap.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\reo\reoTest.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\reo\reoTransfer.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\reo\reoUnits.c
# End Source File
# End Group
# Begin Group "cas"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\bdd\cas\cas.h
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cas\casCore.c
# End Source File
# Begin Source File

SOURCE=.\src\bdd\cas\casDec.c
# End Source File
# End Group
# End Group
# Begin Group "sat"

# PROP Default_Filter ""
# Begin Group "msat"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\sat\msat\msat.h
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatActivity.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatClause.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatClauseVec.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatInt.h
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatMem.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatOrderH.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatQueue.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatRead.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatSolverApi.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatSolverCore.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatSolverIo.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatSolverSearch.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatSort.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\msat\msatVec.c
# End Source File
# End Group
# Begin Group "fraig"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\sat\fraig\fraig.h
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigApi.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigCanon.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigChoice.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigFanout.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigFeed.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigInt.h
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigMan.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigMem.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigNode.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigPrime.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigSat.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigTable.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigUtil.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\fraig\fraigVec.c
# End Source File
# End Group
# Begin Group "csat"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\sat\csat\csat_apis.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\csat\csat_apis.h
# End Source File
# End Group
# Begin Group "bsat"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\sat\bsat\satInter.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\bsat\satInterA.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\bsat\satInterB.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\bsat\satInterP.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\bsat\satMem.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\bsat\satMem.h
# End Source File
# Begin Source File

SOURCE=.\src\sat\bsat\satSolver.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\bsat\satSolver.h
# End Source File
# Begin Source File

SOURCE=.\src\sat\bsat\satStore.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\bsat\satStore.h
# End Source File
# Begin Source File

SOURCE=.\src\sat\bsat\satTrace.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\bsat\satUtil.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\bsat\satVec.h
# End Source File
# End Group
# Begin Group "proof"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\sat\proof\pr.c
# End Source File
# Begin Source File

SOURCE=.\src\sat\proof\pr.h
# End Source File
# End Group
# Begin Group "psat"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\sat\psat\m114p.h
# End Source File
# Begin Source File

SOURCE=.\src\sat\psat\m114p_types.h
# End Source File
# End Group
# Begin Group "nsat"

# PROP Default_Filter ""
# End Group
# Begin Group "lsat"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\sat\lsat\solver.h
# End Source File
# End Group
# End Group
# Begin Group "opt"

# PROP Default_Filter ""
# Begin Group "fxu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\opt\fxu\fxu.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\fxu\fxu.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\fxu\fxuCreate.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\fxu\fxuHeapD.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\fxu\fxuHeapS.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\fxu\fxuInt.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\fxu\fxuList.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\fxu\fxuMatrix.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\fxu\fxuPair.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\fxu\fxuPrint.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\fxu\fxuReduce.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\fxu\fxuSelect.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\fxu\fxuSingle.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\fxu\fxuUpdate.c
# End Source File
# End Group
# Begin Group "rwr"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\opt\rwr\rwr.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\rwr\rwrDec.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\rwr\rwrEva.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\rwr\rwrExp.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\rwr\rwrLib.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\rwr\rwrMan.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\rwr\rwrPrint.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\rwr\rwrTemp.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\rwr\rwrUtil.c
# End Source File
# End Group
# Begin Group "cut"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\opt\cut\cut.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\cut\cutApi.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\cut\cutCut.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\cut\cutExpand.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\cut\cutInt.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\cut\cutList.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\cut\cutMan.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\cut\cutMerge.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\cut\cutNode.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\cut\cutOracle.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\cut\cutPre22.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\cut\cutSeq.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\cut\cutTruth.c
# End Source File
# End Group
# Begin Group "dec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\opt\dec\dec.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\dec\decAbc.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\dec\decFactor.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\dec\decMan.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\dec\decPrint.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\dec\decUtil.c
# End Source File
# End Group
# Begin Group "sim"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\opt\sim\sim.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\sim\simMan.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\sim\simSat.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\sim\simSeq.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\sim\simSupp.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\sim\simSwitch.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\sim\simSym.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\sim\simSymSat.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\sim\simSymSim.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\sim\simSymStr.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\sim\simUtils.c
# End Source File
# End Group
# Begin Group "ret"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\opt\ret\retArea.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\ret\retCore.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\ret\retDelay.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\ret\retFlow.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\ret\retIncrem.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\ret\retInit.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\ret\retInt.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\ret\retLvalue.c
# End Source File
# End Group
# Begin Group "res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\opt\res\res.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\res\resCore.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\res\resDivs.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\res\resFilter.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\res\resInt.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\res\resSat.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\res\resSim.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\res\resStrash.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\res\resWin.c
# End Source File
# End Group
# Begin Group "lpk"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\opt\lpk\lpk.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\lpk\lpkAbcDec.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\lpk\lpkAbcDsd.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\lpk\lpkAbcMux.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\lpk\lpkAbcUtil.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\lpk\lpkCore.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\lpk\lpkCut.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\lpk\lpkInt.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\lpk\lpkMan.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\lpk\lpkMap.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\lpk\lpkMulti.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\lpk\lpkMux.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\lpk\lpkSets.c
# End Source File
# End Group
# Begin Group "fret"

# PROP Default_Filter ""
# End Group
# Begin Group "mfs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\opt\mfs\mfs.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\mfs\mfsCore.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\mfs\mfsDiv.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\mfs\mfsGia.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\mfs\mfsInt.h
# End Source File
# Begin Source File

SOURCE=.\src\opt\mfs\mfsInter.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\mfs\mfsMan.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\mfs\mfsResub.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\mfs\mfsSat.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\mfs\mfsStrash.c
# End Source File
# Begin Source File

SOURCE=.\src\opt\mfs\mfsWin.c
# End Source File
# End Group
# End Group
# Begin Group "map"

# PROP Default_Filter ""
# Begin Group "fpga"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\map\fpga\fpga.c
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpga.h
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpgaCore.c
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpgaCreate.c
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpgaCut.c
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpgaCutUtils.c
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpgaFanout.c
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpgaInt.h
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpgaLib.c
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpgaMatch.c
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpgaSwitch.c
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpgaTime.c
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpgaTruth.c
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpgaUtils.c
# End Source File
# Begin Source File

SOURCE=.\src\map\fpga\fpgaVec.c
# End Source File
# End Group
# Begin Group "mapper"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\map\mapper\mapper.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapper.h
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperCanon.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperCore.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperCreate.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperCut.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperCutUtils.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperFanout.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperInt.h
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperLib.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperMatch.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperRefs.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperSuper.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperSwitch.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperTable.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperTime.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperTree.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperTruth.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperUtils.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mapper\mapperVec.c
# End Source File
# End Group
# Begin Group "mio"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\map\mio\mio.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mio\mio.h
# End Source File
# Begin Source File

SOURCE=.\src\map\mio\mioApi.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mio\mioFunc.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mio\mioInt.h
# End Source File
# Begin Source File

SOURCE=.\src\map\mio\mioRead.c
# End Source File
# Begin Source File

SOURCE=.\src\map\mio\mioUtils.c
# End Source File
# End Group
# Begin Group "super"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\map\super\super.c
# End Source File
# Begin Source File

SOURCE=.\src\map\super\super.h
# End Source File
# Begin Source File

SOURCE=.\src\map\super\superAnd.c
# End Source File
# Begin Source File

SOURCE=.\src\map\super\superGate.c
# End Source File
# Begin Source File

SOURCE=.\src\map\super\superInt.h
# End Source File
# Begin Source File

SOURCE=.\src\map\super\superWrite.c
# End Source File
# End Group
# Begin Group "if"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\map\if\if.h
# End Source File
# Begin Source File

SOURCE=.\src\map\if\ifCore.c
# End Source File
# Begin Source File

SOURCE=.\src\map\if\ifCut.c
# End Source File
# Begin Source File

SOURCE=.\src\map\if\ifLib.c
# End Source File
# Begin Source File

SOURCE=.\src\map\if\ifMan.c
# End Source File
# Begin Source File

SOURCE=.\src\map\if\ifMap.c
# End Source File
# Begin Source File

SOURCE=.\src\map\if\ifReduce.c
# End Source File
# Begin Source File

SOURCE=.\src\map\if\ifSeq.c
# End Source File
# Begin Source File

SOURCE=.\src\map\if\ifTime.c
# End Source File
# Begin Source File

SOURCE=.\src\map\if\ifTruth.c
# End Source File
# Begin Source File

SOURCE=.\src\map\if\ifUtil.c
# End Source File
# End Group
# Begin Group "amap"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\map\amap\amap.h
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapCore.c
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapGraph.c
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapInt.h
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapLib.c
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapLiberty.c
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapMan.c
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapMatch.c
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapMerge.c
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapOutput.c
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapParse.c
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapPerm.c
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapRead.c
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapRule.c
# End Source File
# Begin Source File

SOURCE=.\src\map\amap\amapUniq.c
# End Source File
# End Group
# Begin Group "cov"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\map\cov\cov.h
# End Source File
# Begin Source File

SOURCE=.\src\map\cov\covBuild.c
# End Source File
# Begin Source File

SOURCE=.\src\map\cov\covCore.c
# End Source File
# Begin Source File

SOURCE=.\src\map\cov\covInt.h
# End Source File
# Begin Source File

SOURCE=.\src\map\cov\covMan.c
# End Source File
# Begin Source File

SOURCE=.\src\map\cov\covMinEsop.c
# End Source File
# Begin Source File

SOURCE=.\src\map\cov\covMinMan.c
# End Source File
# Begin Source File

SOURCE=.\src\map\cov\covMinSop.c
# End Source File
# Begin Source File

SOURCE=.\src\map\cov\covMinUtil.c
# End Source File
# End Group
# End Group
# Begin Group "misc"

# PROP Default_Filter ""
# Begin Group "extra"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\misc\extra\extra.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraBddAuto.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraBddCas.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraBddImage.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraBddKmap.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraBddMisc.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraBddSymm.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraBddUnate.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraUtilBitMatrix.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraUtilCanon.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraUtilFile.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraUtilMemory.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraUtilMisc.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraUtilProgress.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraUtilReader.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraUtilTruth.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\extra\extraUtilUtil.c
# End Source File
# End Group
# Begin Group "st"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\misc\st\st.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\st\st.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\st\stmm.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\st\stmm.h
# End Source File
# End Group
# Begin Group "mvc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\misc\mvc\mvc.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvc.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcApi.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcCompare.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcContain.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcCover.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcCube.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcDivide.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcDivisor.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcList.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcLits.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcMan.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcOpAlg.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcOpBool.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcPrint.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcSort.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\mvc\mvcUtils.c
# End Source File
# End Group
# Begin Group "vec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\misc\vec\vec.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\vec\vecAtt.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\vec\vecFlt.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\vec\vecInt.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\vec\vecPtr.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\vec\vecStr.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\vec\vecVec.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\vec\vecWrd.h
# End Source File
# End Group
# Begin Group "util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\misc\util\abc_global.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\util\util_hack.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\util\utilMem.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\util\utilMem.h
# End Source File
# End Group
# Begin Group "nm"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\misc\nm\nm.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\nm\nmApi.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\nm\nmInt.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\nm\nmTable.c
# End Source File
# End Group
# Begin Group "hash"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\misc\hash\hash.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\hash\hashFlt.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\hash\hashInt.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\hash\hashPtr.h
# End Source File
# End Group
# Begin Group "bzlib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\misc\bzlib\blocksort.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\bzlib\bzlib.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\bzlib\bzlib.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\bzlib\bzlib_private.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\bzlib\compress.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\bzlib\crctable.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\bzlib\decompress.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\bzlib\huffman.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\bzlib\randtable.c
# End Source File
# End Group
# Begin Group "zlib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\misc\zlib\adler32.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\compress_.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\crc32.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\crc32.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\deflate.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\deflate.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\gzclose.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\gzguts.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\gzlib.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\gzread.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\gzwrite.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\infback.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\inffast.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\inffast.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\inffixed.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\inflate.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\inflate.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\inftrees.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\inftrees.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\trees.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\trees.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\uncompr.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\zconf.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\zlib.h
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\zutil.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\zlib\zutil.h
# End Source File
# End Group
# End Group
# Begin Group "ai"

# PROP Default_Filter ""
# Begin Group "hop"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\hop\hop.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\hop\hopBalance.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\hop\hopCheck.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\hop\hopDfs.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\hop\hopMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\hop\hopMem.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\hop\hopObj.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\hop\hopOper.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\hop\hopTable.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\hop\hopTruth.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\hop\hopUtil.c
# End Source File
# End Group
# Begin Group "ivy"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\ivy\ivy.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyBalance.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyCanon.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyCheck.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyCut.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyCutTrav.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyDfs.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyDsd.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyFanout.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyFastMap.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyFraig.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyHaig.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyMem.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyMulti.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyObj.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyOper.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyResyn.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyRwr.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivySeq.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyShow.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyTable.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ivy\ivyUtil.c
# End Source File
# End Group
# Begin Group "rwt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\rwt\rwt.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\rwt\rwtDec.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\rwt\rwtMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\rwt\rwtUtil.c
# End Source File
# End Group
# Begin Group "deco"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\deco\deco.h
# End Source File
# End Group
# Begin Group "mem"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\mem\mem.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\mem\mem.h
# End Source File
# End Group
# Begin Group "ioa"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\ioa\ioa.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\ioa\ioaReadAig.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ioa\ioaUtil.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ioa\ioaWriteAig.c
# End Source File
# End Group
# Begin Group "dar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\dar\dar.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\dar\darBalance.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dar\darCore.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dar\darCut.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dar\darData.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dar\darInt.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\dar\darLib.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dar\darMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dar\darPrec.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dar\darRefact.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dar\darResub.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dar\darScript.c
# End Source File
# End Group
# Begin Group "fra"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\fra\fra.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraBmc.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraCec.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraClass.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraClau.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraClaus.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraCnf.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraCore.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraHot.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraImp.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraInd.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraIndVer.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraLcr.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraPart.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraSat.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraSec.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\fra\fraSim.c
# End Source File
# End Group
# Begin Group "cnf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\cnf\cnf.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\cnf\cnfCore.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cnf\cnfCut.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cnf\cnfData.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cnf\cnfMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cnf\cnfMap.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cnf\cnfPost.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cnf\cnfUtil.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cnf\cnfWrite.c
# End Source File
# End Group
# Begin Group "csw"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\csw\csw.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\csw\cswCore.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\csw\cswCut.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\csw\cswInt.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\csw\cswMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\csw\cswTable.c
# End Source File
# End Group
# Begin Group "kit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\kit\cloud.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\kit\cloud.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\kit\kit.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\kit\kitAig.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\kit\kitBdd.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\kit\kitCloud.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\kit\kitDsd.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\kit\kitFactor.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\kit\kitGraph.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\kit\kitHop.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\kit\kitIsop.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\kit\kitPla.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\kit\kitSop.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\kit\kitTruth.c
# End Source File
# End Group
# Begin Group "bdc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\bdc\bdc.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\bdc\bdcCore.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\bdc\bdcDec.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\bdc\bdcInt.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\bdc\bdcTable.c
# End Source File
# End Group
# Begin Group "aig"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\aig\aig.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigCanon.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigCheck.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigCuts.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigDfs.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigDup.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigFact.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigFanout.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigFrames.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigInter.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigMem.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigMffc.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigObj.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigOper.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigOrder.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigPart.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigPartReg.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigPartSat.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigRepr.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigRet.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigRetF.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigScl.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigShow.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigSplit.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigTable.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigTiming.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigTruth.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigTsim.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigUtil.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\aig\aigWin.c
# End Source File
# End Group
# Begin Group "bar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\bar\bar.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\bar\bar.h
# End Source File
# End Group
# Begin Group "ntl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\ntl\ntl.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlCheck.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlCore.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlEc.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlExtract.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlFraig.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlInsert.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlMap.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlNames.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlnwk.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlObj.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlReadBlif.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlSweep.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlTable.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlTime.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlUtil.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ntl\ntlWriteBlif.c
# End Source File
# End Group
# Begin Group "tim"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\tim\tim.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\tim\tim.h
# End Source File
# End Group
# Begin Group "nwk"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\nwk\nwk.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkAig.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkBidec.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkCheck.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkDfs.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkFanio.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkFlow.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkMap.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkMerge.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkMerge.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkObj.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkSpeedup.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkStrash.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkTiming.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\nwk\nwkUtil.c
# End Source File
# End Group
# Begin Group "mfx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\mfx\mfx.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\mfx\mfxCore.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\mfx\mfxDiv.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\mfx\mfxInt.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\mfx\mfxInter.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\mfx\mfxMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\mfx\mfxResub.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\mfx\mfxSat.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\mfx\mfxStrash.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\mfx\mfxWin.c
# End Source File
# End Group
# Begin Group "bbr"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\bbr\bbr.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\bbr\bbrCex.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\bbr\bbrImage.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\bbr\bbrNtbdd.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\bbr\bbrReach.c
# End Source File
# End Group
# Begin Group "saig"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\saig\saig.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigAbs.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigAbs2.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigBmc.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigBmc2.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigBmc3.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigCone.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigConstr.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigConstr2.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigDup.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigHaig.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigInd.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigIoa.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigMiter.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigPba.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigPhase.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigRetFwd.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigRetMin.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigRetStep.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigScl.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigSimExt.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigSimFast.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigSimMv.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigSimSeq.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigStrSim.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigSwitch.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigSynch.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigTrans.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\saig\saigWnd.c
# End Source File
# End Group
# Begin Group "int"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\int\int.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\int\intContain.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\int\intCore.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\int\intCtrex.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\int\intDup.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\int\intFrames.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\int\intInt.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\int\intInter.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\int\intM114.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\int\intM114p.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\int\intMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\int\intUtil.c
# End Source File
# End Group
# Begin Group "dch"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\dch\dch.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\dch\dchAig.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dch\dchChoice.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dch\dchClass.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dch\dchCnf.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dch\dchCore.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dch\dchInt.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\dch\dchMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dch\dchSat.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dch\dchSim.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dch\dchSimSat.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\dch\dchSweep.c
# End Source File
# End Group
# Begin Group "ssw"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\ssw\ssw.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswAig.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswBmc.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswClass.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswCnf.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswConstr.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswCore.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswDyn.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswFilter.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswInt.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswIslands.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswLcorr.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswPairs.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswPart.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswSat.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswSemi.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswSim.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswSimSat.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswSweep.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\ssw\sswUnique.c
# End Source File
# End Group
# Begin Group "cec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\cec\cec.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cec.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecCec.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecChoice.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecClass.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecCore.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecCorr.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecInt.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecIso.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecPat.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecSeq.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecSim.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecSolve.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecSweep.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cec\cecSynth.c
# End Source File
# End Group
# Begin Group "cgt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\cgt\cgt.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\cgt\cgtAig.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cgt\cgtCore.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cgt\cgtDecide.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cgt\cgtInt.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\cgt\cgtMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\cgt\cgtSat.c
# End Source File
# End Group
# Begin Group "gia"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\gia\gia.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\gia.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaAbs.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaAig.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaAig.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaAiger.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaBidec.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaCof.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaCSat.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaCSatOld.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaCTas.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaDfs.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaDup.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaEmbed.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaEnable.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaEquiv.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaEra.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaEra2.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaFanout.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaForce.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaFrames.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaFront.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaGiarf.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaGlitch.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaHash.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaHcd.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaIf.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaMem.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaPat.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaReparam.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaRetime.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaScl.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaShrink.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaSim.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaSort.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaSpeedup.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaSupMin.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaSwitch.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaTsim.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\gia\giaUtil.c
# End Source File
# End Group
# Begin Group "bbl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\bbl\bblif.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\bbl\bblif.h
# End Source File
# End Group
# Begin Group "live"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\live\liveness.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\live\liveness_sim.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\live\ltl_parser.c
# End Source File
# End Group
# Begin Group "sky"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\sky\sky.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\sky\skyAbc.c
# End Source File
# End Group
# Begin Group "llb"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aig\llb\llb.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\llb\llbCex.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\llb\llbCluster.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\llb\llbConstr.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\llb\llbCore.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\llb\llbFlow.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\llb\llbHint.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\llb\llbInt.h
# End Source File
# Begin Source File

SOURCE=.\src\aig\llb\llbMan.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\llb\llbMatrix.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\llb\llbPart.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\llb\llbPivot.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\llb\llbReach.c
# End Source File
# Begin Source File

SOURCE=.\src\aig\llb\llbSched.c
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
