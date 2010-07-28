/**CFile****************************************************************

  FileName    [ioWriteVerilog.c]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Command processing package.]

  Synopsis    [Procedures to output a special subset of Verilog.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 20, 2005.]

  Revision    [$Id: ioWriteVerilog.c,v 1.00 2005/06/20 00:00:00 alanmi Exp $]

***********************************************************************/

#include "io.h"
#include "main.h"
#include "mio.h"

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

static void Io_WriteVerilogInt( FILE * pFile, Abc_Ntk_t * pNtk, int fVerLibStyle );
static void Io_WriteVerilogPis( FILE * pFile, Abc_Ntk_t * pNtk, int Start );
static void Io_WriteVerilogPos( FILE * pFile, Abc_Ntk_t * pNtk, int Start );
static void Io_WriteVerilogWires( FILE * pFile, Abc_Ntk_t * pNtk, int Start );
static void Io_WriteVerilogRegs( FILE * pFile, Abc_Ntk_t * pNtk, int Start );
static void Io_WriteVerilogGates( FILE * pFile, Abc_Ntk_t * pNtk );
static void Io_WriteVerilogNodes( FILE * pFile, Abc_Ntk_t * pNtk );
static void Io_WriteVerilogLatches( FILE * pFile, Abc_Ntk_t * pNtk );
static void Io_WriteVerilogVerLibStyle( FILE * pFile, Abc_Ntk_t * pNtk );
static int Io_WriteVerilogCheckNtk( Abc_Ntk_t * pNtk );
static char * Io_WriteVerilogGetName( Abc_Obj_t * pObj );
static int Io_WriteVerilogWiresCount( Abc_Ntk_t * pNtk );

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Write verilog.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Io_WriteVerilog( Abc_Ntk_t * pNtk, char * pFileName, int fVerLibStyle )
{
    FILE * pFile;
    if ( !Abc_NtkIsAigNetlist(pNtk) )
    {
        printf( "Io_WriteVerilog(): Can produce Verilog for AIG netlists only.\n" );
        return;
    }
    if ( Abc_NtkLatchNum(pNtk) > 0 )
    {
        printf( "Io_WriteVerilog(): Currently cannot write verilog for sequential networks.\n" );
        return;
    }

/*
    if ( !(Abc_NtkIsNetlist(pNtk) && (Abc_NtkHasMapping(pNtk) || Io_WriteVerilogCheckNtk(pNtk))) )
    {
        printf( "Io_WriteVerilog(): Can produce Verilog for a subset of logic networks.\n" );
        printf( "The network should be either an AIG or a network after technology mapping.\n" );
        printf( "The current network is not in the subset; the output files is not written.\n" );
        return;
    }
*/
    // start the output stream
    pFile = fopen( pFileName, "w" );
    if ( pFile == NULL )
    {
        fprintf( stdout, "Io_WriteVerilog(): Cannot open the output file \"%s\".\n", pFileName );
        return;
    }

    // write the equations for the network
    fprintf( pFile, "// Benchmark \"%s\" written by ABC on %s\n", pNtk->pName, Extra_TimeStamp() );
    Io_WriteVerilogInt( pFile, pNtk, fVerLibStyle );
	fprintf( pFile, "\n" );
	fclose( pFile );
}

/**Function*************************************************************

  Synopsis    [Write verilog.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Io_WriteVerilogLibrary( Abc_Lib_t * pLibrary, char * pFileName )
{
    FILE * pFile;
    Abc_Ntk_t * pNtk, * pNetlist;
    int i;

    // start the output stream
    pFile = fopen( pFileName, "w" );
    if ( pFile == NULL )
    {
        fprintf( stdout, "Io_WriteVerilogLibrary(): Cannot open the output file \"%s\".\n", pFileName );
        return;
    }

    fprintf( pFile, "// Verilog library \"%s\" written by ABC on %s\n", pFileName, Extra_TimeStamp() );
	fprintf( pFile, "\n" );
    // write modules
    Vec_PtrForEachEntry( pLibrary->vModules, pNtk, i )
    {
        // create netlist
//        pNetlist = Abc_NtkLogicToNetlist( pNtk, 0 );
        assert( Abc_NtkIsNetlist(pNtk) );
        pNetlist = pNtk;
        // write the equations for the network
        Io_WriteVerilogInt( pFile, pNetlist, 1 );
	    fprintf( pFile, "\n" );
        // delete the netlist
//        Abc_NtkDelete( pNetlist );
    }

	fclose( pFile );
}

/**Function*************************************************************

  Synopsis    [Writes verilog.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Io_WriteVerilogInt( FILE * pFile, Abc_Ntk_t * pNtk, int fVerLibStyle )
{
    // write inputs and outputs
//    fprintf( pFile, "module %s ( gclk,\n   ", Abc_NtkName(pNtk) );
    fprintf( pFile, "module %s ( \n   ", Abc_NtkName(pNtk) );
    Io_WriteVerilogPis( pFile, pNtk, 3 );
    fprintf( pFile, ",\n   " );
    Io_WriteVerilogPos( pFile, pNtk, 3 );
    fprintf( pFile, "  );\n" );
    // write inputs, outputs, registers, and wires
//    fprintf( pFile, "  input gclk," );
    fprintf( pFile, "  input " );
    Io_WriteVerilogPis( pFile, pNtk, 10 );
    fprintf( pFile, ";\n" );
    fprintf( pFile, "  output" );
    Io_WriteVerilogPos( pFile, pNtk, 5 );
    fprintf( pFile, ";\n" );
    if ( Abc_NtkLatchNum(pNtk) > 0 )
    {
    fprintf( pFile, "  reg" );
    Io_WriteVerilogRegs( pFile, pNtk, 4 );
    fprintf( pFile, ";\n" );
    }
    if ( Io_WriteVerilogWiresCount(pNtk) > 0 )
    {
    fprintf( pFile, "  wire" );
    Io_WriteVerilogWires( pFile, pNtk, 4 );
    fprintf( pFile, ";\n" );
    }
    // write nodes
    if ( fVerLibStyle )
        Io_WriteVerilogVerLibStyle( pFile, pNtk );        
    else if ( Abc_NtkHasMapping(pNtk) )
        Io_WriteVerilogGates( pFile, pNtk );
    else
        Io_WriteVerilogNodes( pFile, pNtk );
    // write registers
    Io_WriteVerilogLatches( pFile, pNtk );
    // finalize the file
    fprintf( pFile, "endmodule\n\n" );
} 

/**Function*************************************************************

  Synopsis    [Writes the primary inputs.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Io_WriteVerilogPis( FILE * pFile, Abc_Ntk_t * pNtk, int Start )
{
    Abc_Obj_t * pTerm, * pNet;
    int LineLength;
    int AddedLength;
    int NameCounter;
    int i;

    LineLength  = Start;
    NameCounter = 0;
    Abc_NtkForEachPi( pNtk, pTerm, i )
    {
        pNet = Abc_ObjFanout0(pTerm);
        // get the line length after this name is written
        AddedLength = strlen(Io_WriteVerilogGetName(pNet)) + 2;
        if ( NameCounter && LineLength + AddedLength + 3 > IO_WRITE_LINE_LENGTH )
        { // write the line extender
            fprintf( pFile, "\n   " );
            // reset the line length
            LineLength  = 3;
            NameCounter = 0;
        }
        fprintf( pFile, " %s%s", Io_WriteVerilogGetName(pNet), (i==Abc_NtkPiNum(pNtk)-1)? "" : "," );
        LineLength += AddedLength;
        NameCounter++;
    }
} 

/**Function*************************************************************

  Synopsis    [Writes the primary outputs.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Io_WriteVerilogPos( FILE * pFile, Abc_Ntk_t * pNtk, int Start )
{
    Abc_Obj_t * pTerm, * pNet;
    int LineLength;
    int AddedLength;
    int NameCounter;
    int i;

    LineLength  = Start;
    NameCounter = 0;
    Abc_NtkForEachPo( pNtk, pTerm, i )
    {
        pNet = Abc_ObjFanin0(pTerm);
        // get the line length after this name is written
        AddedLength = strlen(Io_WriteVerilogGetName(pNet)) + 2;
        if ( NameCounter && LineLength + AddedLength + 3 > IO_WRITE_LINE_LENGTH )
        { // write the line extender
            fprintf( pFile, "\n   " );
            // reset the line length
            LineLength  = 3;
            NameCounter = 0;
        }
        fprintf( pFile, " %s%s", Io_WriteVerilogGetName(pNet), (i==Abc_NtkPoNum(pNtk)-1)? "" : "," );
        LineLength += AddedLength;
        NameCounter++;
    }
}

/**Function*************************************************************

  Synopsis    [Counts the number of wires.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Io_WriteVerilogWiresCount( Abc_Ntk_t * pNtk )
{
    Abc_Obj_t * pTerm, * pNet;
    int i, nNodes;
    nNodes = Abc_NtkLatchNum(pNtk);
    Abc_NtkForEachNode( pNtk, pTerm, i )
    {
        if ( i == 0 ) 
            continue;
        pNet = Abc_ObjFanout0(pTerm);
        if ( Abc_ObjIsCo(Abc_ObjFanout0(pNet)) )
            continue;
        nNodes++;
    }
    return nNodes;
}

/**Function*************************************************************

  Synopsis    [Writes the wires.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Io_WriteVerilogWires( FILE * pFile, Abc_Ntk_t * pNtk, int Start )
{
    Abc_Obj_t * pTerm, * pNet;
    int LineLength;
    int AddedLength;
    int NameCounter;
    int i, Counter, nNodes;

    // count the number of wires
    nNodes = Io_WriteVerilogWiresCount( pNtk );

    // write the wires
    Counter = 0;
    LineLength  = Start;
    NameCounter = 0;
    Abc_NtkForEachNode( pNtk, pTerm, i )
    {
        if ( i == 0 ) 
            continue;
        pNet = Abc_ObjFanout0(pTerm);
        if ( Abc_ObjIsCo(Abc_ObjFanout0(pNet)) )
            continue;
        Counter++;
        // get the line length after this name is written
        AddedLength = strlen(Io_WriteVerilogGetName(pNet)) + 2;
        if ( NameCounter && LineLength + AddedLength + 3 > IO_WRITE_LINE_LENGTH )
        { // write the line extender
            fprintf( pFile, "\n   " );
            // reset the line length
            LineLength  = 3;
            NameCounter = 0;
        }
        fprintf( pFile, " %s%s", Io_WriteVerilogGetName(pNet), (Counter==nNodes)? "" : "," );
        LineLength += AddedLength;
        NameCounter++;
    }
    Abc_NtkForEachLatch( pNtk, pTerm, i )
    {
        pNet = Abc_ObjFanin0(Abc_ObjFanin0(pTerm));
        Counter++;
        // get the line length after this name is written
        AddedLength = strlen(Io_WriteVerilogGetName(pNet)) + 2;
        if ( NameCounter && LineLength + AddedLength + 3 > IO_WRITE_LINE_LENGTH )
        { // write the line extender
            fprintf( pFile, "\n   " );
            // reset the line length
            LineLength  = 3;
            NameCounter = 0;
        }
        fprintf( pFile, " %s%s", Io_WriteVerilogGetName(pNet), (Counter==nNodes)? "" : "," );
        LineLength += AddedLength;
        NameCounter++;
    }
    assert( Counter == nNodes );
}

/**Function*************************************************************

  Synopsis    [Writes the regs.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Io_WriteVerilogRegs( FILE * pFile, Abc_Ntk_t * pNtk, int Start )
{
    Abc_Obj_t * pLatch, * pNet;
    int LineLength;
    int AddedLength;
    int NameCounter;
    int i, Counter, nNodes;

    // count the number of latches
    nNodes = Abc_NtkLatchNum(pNtk);

    // write the wires
    Counter = 0;
    LineLength  = Start;
    NameCounter = 0;
    Abc_NtkForEachLatch( pNtk, pLatch, i )
    {
        pNet = Abc_ObjFanout0(Abc_ObjFanout0(pLatch));
        Counter++;
        // get the line length after this name is written
        AddedLength = strlen(Io_WriteVerilogGetName(pNet)) + 2;
        if ( NameCounter && LineLength + AddedLength + 3 > IO_WRITE_LINE_LENGTH )
        { // write the line extender
            fprintf( pFile, "\n   " );
            // reset the line length
            LineLength  = 3;
            NameCounter = 0;
        }
        fprintf( pFile, " %s%s", Io_WriteVerilogGetName(pNet), (Counter==nNodes)? "" : "," );
        LineLength += AddedLength;
        NameCounter++;
    }
}

/**Function*************************************************************

  Synopsis    [Writes the latches.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Io_WriteVerilogLatches( FILE * pFile, Abc_Ntk_t * pNtk )
{
    Abc_Obj_t * pLatch;
    int i;
    Abc_NtkForEachLatch( pNtk, pLatch, i )
    {
//        fprintf( pFile, "  always@(posedge  gclk) begin %s",     Abc_ObjName(Abc_ObjFanout0(pLatch)) );
        fprintf( pFile, "  always begin %s",     Io_WriteVerilogGetName(Abc_ObjFanout0(Abc_ObjFanout0(pLatch))) );
        fprintf( pFile, " = %s; end\n", Io_WriteVerilogGetName(Abc_ObjFanin0(Abc_ObjFanin0(pLatch))) );
        if ( Abc_LatchInit(pLatch) == ABC_INIT_ZERO )
//            fprintf( pFile, "  initial begin %s = 1\'b0; end\n", Io_WriteVerilogGetName(Abc_ObjFanout0(pLatch)) );
            fprintf( pFile, "  initial begin %s = 0; end\n", Io_WriteVerilogGetName(Abc_ObjFanout0(Abc_ObjFanout0(pLatch))) );
        else if ( Abc_LatchInit(pLatch) == ABC_INIT_ONE )
//            fprintf( pFile, "  initial begin %s = 1\'b1; end\n", Io_WriteVerilogGetName(Abc_ObjFanout0(pLatch)) );
            fprintf( pFile, "  initial begin %s = 1; end\n", Io_WriteVerilogGetName(Abc_ObjFanout0(Abc_ObjFanout0(pLatch))) );
    }
}

/* // fix by Zhihong
void Io_WriteVerilogLatches( FILE * pFile, Abc_Ntk_t * pNtk )
{
    Abc_Obj_t * pLatch;
    int i;
    Abc_NtkForEachLatch( pNtk, pLatch, i )
    {
        if ( Abc_LatchInit(pLatch) == ABC_INIT_ZERO )
            fprintf( pFile, "  initial begin %s <= 1\'b0; end\n", Io_WriteVerilogGetName(Abc_ObjFanout0(Abc_ObjFanout0(pLatch))) );
        else if ( Abc_LatchInit(pLatch) == ABC_INIT_ONE )
            fprintf( pFile, "  initial begin %s <= 1\'b1; end\n", Io_WriteVerilogGetName(Abc_ObjFanout0(Abc_ObjFanout0(pLatch))) );
        fprintf( pFile, "  always@(posedge  gclk) begin %s",     Io_WriteVerilogGetName(Abc_ObjFanout0(Abc_ObjFanout0(pLatch))) );
        fprintf( pFile, " <= %s; end\n", Io_WriteVerilogGetName(Abc_ObjFanin0(Abc_ObjFanin0(pLatch))) );
    }
}
*/

/**Function*************************************************************

  Synopsis    [Writes the nodes and boxes.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Io_WriteVerilogVerLibStyle( FILE * pFile, Abc_Ntk_t * pNtk )
{
    Vec_Vec_t * vLevels;
    Abc_Ntk_t * pNtkGate;
    Abc_Obj_t * pObj, * pTerm, * pFanin;
    Hop_Obj_t * pFunc;
    int i, k, Counter, nDigits;

    Counter = 1;
    nDigits = Extra_Base10Log( Abc_NtkNodeNum(pNtk) );

    // write boxes
    Abc_NtkForEachBox( pNtk, pObj, i )
    {
        pNtkGate = pObj->pData;
        fprintf( pFile, "  %s g%0*d", pNtkGate->pName, nDigits, Counter++ );
        fprintf( pFile, "(" );
        Abc_NtkForEachPi( pNtkGate, pTerm, k )
        {
            fprintf( pFile, ".%s ",   Io_WriteVerilogGetName(Abc_ObjFanout0(pTerm)) );
            fprintf( pFile, "(%s), ", Io_WriteVerilogGetName(Abc_ObjFanin(pObj,k)) );
        }
        Abc_NtkForEachPo( pNtkGate, pTerm, k )
        {
            fprintf( pFile, ".%s ",   Io_WriteVerilogGetName(Abc_ObjFanin0(pTerm)) );
            fprintf( pFile, "(%s)%s", Io_WriteVerilogGetName(Abc_ObjFanout(pObj,k)), k==Abc_NtkPoNum(pNtkGate)-1? "":", " );
        }
        fprintf( pFile, ");\n" );
    }
    // write nodes
    vLevels = Vec_VecAlloc( 10 );
    Abc_NtkForEachNode( pNtk, pObj, i )
    {
        pFunc = pObj->pData;
        fprintf( pFile, "  assign %s = ", Io_WriteVerilogGetName(Abc_ObjFanout0(pObj)) );
        // set the input names
        Abc_ObjForEachFanin( pObj, pFanin, k )
            Hop_IthVar(pNtk->pManFunc, k)->pData = Extra_UtilStrsav(Io_WriteVerilogGetName(pFanin));
        // write the formula
        Hop_ObjPrintVerilog( pFile, pFunc, vLevels, 0 );
        fprintf( pFile, ";\n" );
        // clear the input names
        Abc_ObjForEachFanin( pObj, pFanin, k )
            free( Hop_IthVar(pNtk->pManFunc, k)->pData );
    }
    Vec_VecFree( vLevels );
}

/**Function*************************************************************

  Synopsis    [Writes the gates.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Io_WriteVerilogGates( FILE * pFile, Abc_Ntk_t * pNtk )
{
    Mio_Gate_t * pGate;
    Mio_Pin_t * pGatePin;
    Abc_Obj_t * pObj;
    int i, k, Counter, nDigits, nFanins;

    Counter = 1;
    nDigits = Extra_Base10Log( Abc_NtkNodeNum(pNtk) );
    Abc_NtkForEachNode( pNtk, pObj, i )
    {
        pGate = pObj->pData;
        nFanins = Abc_ObjFaninNum(pObj);
        fprintf( pFile, "  %s g%0*d", Mio_GateReadName(pGate), nDigits, Counter++ );
        fprintf( pFile, "(.%s (%s),", Mio_GateReadOutName(pGate), Io_WriteVerilogGetName(Abc_ObjFanout0(pObj)) );
        for ( pGatePin = Mio_GateReadPins(pGate), k = 0; pGatePin; pGatePin = Mio_PinReadNext(pGatePin), k++ )
            fprintf( pFile, " .%s (%s)%s", Mio_PinReadName(pGatePin), Io_WriteVerilogGetName(Abc_ObjFanin(pObj,k)), k==nFanins-1? "":"," );
        fprintf( pFile, ");\n" );
    }
}


/**Function*************************************************************

  Synopsis    [Writes the nodes.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Io_WriteVerilogNodes2( FILE * pFile, Abc_Ntk_t * pNtk )
{
    Abc_Obj_t * pObj, * pFanin;
    int i, k, nFanins;
    char * pName;

    Abc_NtkForEachNode( pNtk, pObj, i )
    {
        assert( Abc_SopGetCubeNum(pObj->pData) == 1 );
        nFanins = Abc_ObjFaninNum(pObj);
        if ( nFanins == 0 )
        {
//            fprintf( pFile, "  assign %s = 1'b%d;\n", Io_WriteVerilogGetName(Abc_ObjFanout0(pObj)), !Abc_SopIsComplement(pObj->pData) );
            fprintf( pFile, "  assign %s = %d;\n", Io_WriteVerilogGetName(Abc_ObjFanout0(pObj)), !Abc_SopIsComplement(pObj->pData) );
            continue;
        }
        if ( nFanins == 1 )
        {
            pName = Abc_SopIsInv(pObj->pData)? "not" : "and";
            fprintf( pFile, "  %s(%s, ", pName, Io_WriteVerilogGetName(Abc_ObjFanout0(pObj)) );
            fprintf( pFile, "%s);\n", Io_WriteVerilogGetName(Abc_ObjFanin0(pObj)) );
            continue;
        }
        pName = Abc_SopIsComplement(pObj->pData)? "or" : "and";
        fprintf( pFile, "  %s(%s, ", pName, Io_WriteVerilogGetName(Abc_ObjFanout0(pObj)) );
//        Abc_ObjForEachFanin( pObj, pFanin, k )
//            fprintf( pFile, "%s%s", Io_WriteVerilogGetName(pFanin), (k==nFanins-1? "" : ", ") );
        Abc_ObjForEachFanin( pObj, pFanin, k ) 
        {
            char *cube = pObj->pData;
            fprintf( pFile, "%s", cube[k] == '0' ? "~" : "");
                fprintf( pFile, "%s%s", Io_WriteVerilogGetName(pFanin), (k==nFanins-1? "" : ", ") );
        }
        fprintf( pFile, ");\n" );
    }
}

/**Function*************************************************************

  Synopsis    [Writes the nodes.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Io_WriteVerilogNodes( FILE * pFile, Abc_Ntk_t * pNtk )
{
    Abc_Obj_t * pObj, * pFanin;
    int i, k, nFanins;
    char pOper[] = " ? ", Symb;
    Abc_NtkForEachNode( pNtk, pObj, i )
    {
        assert( Abc_SopGetCubeNum(pObj->pData) == 1 );
        nFanins = Abc_ObjFaninNum(pObj);
        if ( nFanins == 0 )
        {
            fprintf( pFile, "  assign %s = 1'b%d;\n", Io_WriteVerilogGetName(Abc_ObjFanout0(pObj)), !Abc_SopIsComplement(pObj->pData) );
            continue;
        }
        fprintf( pFile, "  assign %s = ", Io_WriteVerilogGetName(Abc_ObjFanout0(pObj)) );
        pOper[1] = Abc_SopIsComplement(pObj->pData) ? '|' : '&';
        Abc_ObjForEachFanin( pObj, pFanin, k )
        {
            Symb = ((char*)pObj->pData)[k];
            assert( Symb == '0' || Symb == '1' );
            if ( Symb == '0' )
                fprintf( pFile, "~" );
            fprintf( pFile, "%s%s", Io_WriteVerilogGetName(pFanin), (k==nFanins-1? "" : pOper) );
        }
        fprintf( pFile, ";\n" );
    }
}

/**Function*************************************************************

  Synopsis    []

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
int Io_WriteVerilogCheckNtk( Abc_Ntk_t * pNtk )
{
    Abc_Obj_t * pObj;
    int i;
    Abc_NtkForEachNode( pNtk, pObj, i )
    {
        if ( Abc_SopGetCubeNum(pObj->pData) > 1 )
        {
            printf( "Node %s contains a cover with more than one cube.\n", Abc_ObjName(pObj) );
            return 0;
        }
    }
    return 1;
}

/**Function*************************************************************

  Synopsis    [Prepares the name for writing the Verilog file.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
char * Io_WriteVerilogGetName( Abc_Obj_t * pObj )
{
    static char Buffer[500];
    char * pName;
    int Length, i;
    pName = Abc_ObjName(pObj);
    Length = strlen(pName);
    // consider the case of a signal having name "0" or "1"
    if ( !(Length == 1 && (pName[0] == '0' || pName[0] == '1')) )
    {
        for ( i = 0; i < Length; i++ )
            if ( !((pName[i] >= 'a' && pName[i] <= 'z') || 
                 (pName[i] >= 'A' && pName[i] <= 'Z') || 
                 (pName[i] >= '0' && pName[i] <= '9') || pName[i] == '_') )
                 break;
        if ( i == Length )
            return pName;
    }
    // create Verilog style name
    Buffer[0] = '\\';
    for ( i = 0; i < Length; i++ )
        Buffer[i+1] = pName[i];
    Buffer[Length+1] = ' ';
    Buffer[Length+2] = 0;
    return Buffer;
}

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////


