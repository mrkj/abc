/**CFile****************************************************************

  FileName    [ioUtil.c]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Command processing package.]

  Synopsis    [Procedures to write the network in BENCH format.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 20, 2005.]

  Revision    [$Id: ioUtil.c,v 1.00 2005/06/20 00:00:00 alanmi Exp $]

***********************************************************************/

#include "io.h"

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Returns the file type.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Io_FileType_t Io_ReadFileType( char * pFileName )
{
    char * pExt;
    if ( pFileName == NULL )
        return IO_FILE_NONE;
    pExt = Extra_FileNameExtension( pFileName );
    if ( pExt == NULL )
        return IO_FILE_NONE;
    if ( !strcmp( pExt, "aig" ) )
        return IO_FILE_AIGER;
    if ( !strcmp( pExt, "baf" ) )
        return IO_FILE_BAF;
    if ( !strcmp( pExt, "blif" ) )
        return IO_FILE_BLIF;
    if ( !strcmp( pExt, "bench" ) )
        return IO_FILE_BENCH;
    if ( !strcmp( pExt, "cnf" ) )
        return IO_FILE_CNF;
    if ( !strcmp( pExt, "dot" ) )
        return IO_FILE_DOT;
    if ( !strcmp( pExt, "edif" ) )
        return IO_FILE_EDIF;
    if ( !strcmp( pExt, "eqn" ) )
        return IO_FILE_EQN;
    if ( !strcmp( pExt, "gml" ) )
        return IO_FILE_GML;
    if ( !strcmp( pExt, "list" ) )
        return IO_FILE_LIST;
    if ( !strcmp( pExt, "pla" ) )
        return IO_FILE_PLA;
    if ( !strcmp( pExt, "v" ) )
        return IO_FILE_VERILOG;
    return IO_FILE_UNKNOWN;
}

/**Function*************************************************************

  Synopsis    [Read the network from a file.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Ntk_t * Io_ReadNetlist( char * pFileName, Io_FileType_t FileType, int fCheck )
{
    FILE * pFile;
    Abc_Ntk_t * pNtk;
    if ( FileType == IO_FILE_NONE || FileType == IO_FILE_UNKNOWN )
    {
        fprintf( stdout, "The generic file reader requires a known file extension.\n" );
        return NULL;
    }
    // check if the file exists
    if ( (pFile = fopen( pFileName, "r" )) == NULL )
    {
        fprintf( stdout, "Cannot open input file \"%s\". ", pFileName );
        if ( pFileName = Extra_FileGetSimilarName( pFileName, ".blif", ".bench", ".pla", ".baf", ".aig" ) )
            fprintf( stdout, "Did you mean \"%s\"?", pFileName );
        fprintf( stdout, "\n" );
       return NULL;
    }
    fclose( pFile );
    // read the AIG
    if ( FileType == IO_FILE_AIGER || FileType == IO_FILE_BAF )
    {
        if ( FileType == IO_FILE_AIGER )
            pNtk = Io_ReadAiger( pFileName, fCheck );
        else // if ( FileType == IO_FILE_BAF )
            pNtk = Io_ReadBaf( pFileName, fCheck );
        if ( pNtk == NULL )
        {
            fprintf( stdout, "Reading AIG from file has failed.\n" );
            return NULL;
        }
        return pNtk;
    }
    // read the new netlist
    if ( FileType == IO_FILE_BLIF )
        pNtk = Io_ReadBlif( pFileName, fCheck );
    else if ( FileType == IO_FILE_BENCH )
        pNtk = Io_ReadBench( pFileName, fCheck );
    else if ( FileType == IO_FILE_EDIF )
        pNtk = Io_ReadEdif( pFileName, fCheck );
    else if ( FileType == IO_FILE_EQN )
        pNtk = Io_ReadEqn( pFileName, fCheck );
    else if ( FileType == IO_FILE_PLA )
        pNtk = Io_ReadPla( pFileName, fCheck );
    else 
    {
        fprintf( stderr, "Unknown file format.\n" );
        return NULL;
    }
    if ( pNtk == NULL )
    {
        fprintf( stdout, "Reading network from file has failed.\n" );
        return NULL;
    }
    return pNtk;
}


/**Function*************************************************************

  Synopsis    [Read the network from a file.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Ntk_t * Io_Read( char * pFileName, Io_FileType_t FileType, int fCheck )
{
    Abc_Ntk_t * pNtk, * pTemp;
    // get the netlist
    pNtk = Io_ReadNetlist( pFileName, FileType, fCheck );
    if ( pNtk == NULL )
        return NULL;
    if ( !Abc_NtkIsNetlist(pNtk) )
        return pNtk;
    // convert the netlist into the logic network
    pNtk = Abc_NtkNetlistToLogic( pTemp = pNtk );
    Abc_NtkDelete( pTemp );
    if ( pNtk == NULL )
    {
        fprintf( stdout, "Converting netlist to logic network after reading has failed.\n" );
        return NULL;
    }
    return pNtk;
}

/**Function*************************************************************

  Synopsis    [Write the network into file.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Io_Write( Abc_Ntk_t * pNtk, char * pFileName, Io_FileType_t FileType )
{
    Abc_Ntk_t * pNtkTemp, * pNtkCopy;
    // check if the current network is available
    if ( pNtk == NULL )
    {
        fprintf( stdout, "Empty network.\n" );
        return;
    }
    // check if the file extension if given
    if ( FileType == IO_FILE_NONE || FileType == IO_FILE_UNKNOWN )
    {
        fprintf( stdout, "The generic file writer requires a known file extension.\n" );
        return;
    }
    // write the AIG formats
    if ( FileType == IO_FILE_AIGER || FileType == IO_FILE_BAF )
    {
        if ( !Abc_NtkIsStrash(pNtk) )
        {
            fprintf( stdout, "Writing this format is only possible for structurally hashed AIGs.\n" );
            return;
        }
        if ( FileType == IO_FILE_AIGER )
            Io_WriteAiger( pNtk, pFileName );
        else // if ( FileType == IO_FILE_BAF )
            Io_WriteBaf( pNtk, pFileName );
        return;
    }
    // write non-netlist types
    if ( FileType == IO_FILE_CNF )
    {
        Io_WriteCnf( pNtk, pFileName );
        return;
    }
    if ( FileType == IO_FILE_DOT )
    {
        Io_WriteDot( pNtk, pFileName );
        return;
    }
    if ( FileType == IO_FILE_GML )
    {
        Io_WriteGml( pNtk, pFileName );
        return;
    }
    // convert logic network into netlist
    if ( FileType == IO_FILE_PLA )
    {
        if ( Abc_NtkLevel(pNtk) > 1 )
        {
            fprintf( stdout, "PLA writing is available for collapsed networks.\n" );
            return;
        }
        if ( Abc_NtkIsComb(pNtk) )
            pNtkTemp = Abc_NtkLogicToNetlist( pNtk, 1 );
        else
        {
            fprintf( stdout, "Latches are writen into the PLA file at PI/PO pairs.\n" );
            pNtkCopy = Abc_NtkDup( pNtk );
            Abc_NtkMakeComb( pNtkCopy );
            pNtkTemp = Abc_NtkLogicToNetlist( pNtk, 1 );
            Abc_NtkDelete( pNtkCopy );
        }
    }
    else if ( FileType == IO_FILE_BENCH )
    {
        if ( !Abc_NtkIsStrash(pNtk) )
        {
            fprintf( stdout, "Writing BENCH is available for AIGs.\n" );
            return;
        }
        pNtkTemp = Abc_NtkLogicToNetlistBench( pNtk );
    }
    else
        pNtkTemp = Abc_NtkLogicToNetlist( pNtk, 0 );
    if ( pNtkTemp == NULL )
    {
        fprintf( stdout, "Converting to netlist has failed.\n" );
        return;
    }
    if ( FileType == IO_FILE_BLIF )
        Io_WriteBlifNetlist( pNtkTemp, pFileName, 1 );
    else if ( FileType == IO_FILE_BENCH )
        Io_WriteBench( pNtkTemp, pFileName );
    else if ( FileType == IO_FILE_PLA )
        Io_WritePla( pNtkTemp, pFileName );
    else if ( FileType == IO_FILE_EQN )
    {
        if ( Abc_NtkIsSopNetlist(pNtkTemp) )
            Abc_NtkSopToAig( pNtkTemp );
        Io_WriteEqn( pNtkTemp, pFileName );
    }
    else if ( FileType == IO_FILE_VERILOG )
    {
        if ( Abc_NtkIsSopNetlist(pNtkTemp) )
            Abc_NtkSopToAig( pNtkTemp );
        Io_WriteVerilog( pNtkTemp, pFileName, 1 );
    }
    else 
        fprintf( stderr, "Unknown file format.\n" );
    Abc_NtkDelete( pNtkTemp );
}

/**Function*************************************************************

  Synopsis    [Creates PI terminal and net.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Obj_t * Io_ReadCreatePi( Abc_Ntk_t * pNtk, char * pName )
{
    Abc_Obj_t * pNet, * pTerm;
    // get the PI net
    pNet  = Abc_NtkFindNet( pNtk, pName );
    if ( pNet )
        printf( "Warning: PI \"%s\" appears twice in the list.\n", pName );
    pNet  = Abc_NtkFindOrCreateNet( pNtk, pName );
    // add the PI node
    pTerm = Abc_NtkCreatePi( pNtk );
    Abc_ObjAddFanin( pNet, pTerm );
    return pTerm;
}

/**Function*************************************************************

  Synopsis    [Creates PO terminal and net.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Obj_t * Io_ReadCreatePo( Abc_Ntk_t * pNtk, char * pName )
{
    Abc_Obj_t * pNet, * pTerm;
    // get the PO net
    pNet  = Abc_NtkFindNet( pNtk, pName );
    if ( pNet && Abc_ObjFaninNum(pNet) == 0 )
        printf( "Warning: PO \"%s\" appears twice in the list.\n", pName );
    pNet  = Abc_NtkFindOrCreateNet( pNtk, pName );
    // add the PO node
    pTerm = Abc_NtkCreatePo( pNtk );
    Abc_ObjAddFanin( pTerm, pNet );
    return pTerm;
}

/**Function*************************************************************

  Synopsis    [Creates PO terminal and net.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Obj_t * Io_ReadCreateAssert( Abc_Ntk_t * pNtk, char * pName )
{
    Abc_Obj_t * pNet, * pTerm;
    // get the PO net
    pNet  = Abc_NtkFindNet( pNtk, pName );
    if ( pNet && Abc_ObjFaninNum(pNet) == 0 )
        printf( "Warning: Assert \"%s\" appears twice in the list.\n", pName );
    pNet  = Abc_NtkFindOrCreateNet( pNtk, pName );
    // add the PO node
    pTerm = Abc_NtkCreateAssert( pNtk );
    Abc_ObjAddFanin( pTerm, pNet );
    return pTerm;
}

/**Function*************************************************************

  Synopsis    [Create a latch with the given input/output.]

  Description [By default, the latch value is unknown (ABC_INIT_NONE).]
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Obj_t * Io_ReadCreateLatch( Abc_Ntk_t * pNtk, char * pNetLI, char * pNetLO )
{
    Abc_Obj_t * pLatch, * pTerm, * pNet;
    // get the LI net
    pNet = Abc_NtkFindOrCreateNet( pNtk, pNetLI );
    // add the BO terminal
    pTerm = Abc_NtkCreateBi( pNtk );
    Abc_ObjAddFanin( pTerm, pNet );
    // add the latch box
    pLatch = Abc_NtkCreateLatch( pNtk );
    Abc_ObjAddFanin( pLatch, pTerm  );
    // add the BI terminal
    pTerm = Abc_NtkCreateBo( pNtk );
    Abc_ObjAddFanin( pTerm, pLatch );
    // get the LO net
    pNet = Abc_NtkFindOrCreateNet( pNtk, pNetLO );
    Abc_ObjAddFanin( pNet, pTerm );
    // set latch name
    Abc_ObjAssignName( pLatch, pNetLO, "L" );
    return pLatch;
}

/**Function*************************************************************

  Synopsis    [Create node and the net driven by it.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Obj_t * Io_ReadCreateNode( Abc_Ntk_t * pNtk, char * pNameOut, char * pNamesIn[], int nInputs )
{
    Abc_Obj_t * pNet, * pNode;
    int i;
    // create a new node 
    pNode = Abc_NtkCreateNode( pNtk );
    // add the fanin nets
    for ( i = 0; i < nInputs; i++ )
    {
        pNet = Abc_NtkFindOrCreateNet( pNtk, pNamesIn[i] );
        Abc_ObjAddFanin( pNode, pNet );
    }
    // add the fanout net
    pNet = Abc_NtkFindOrCreateNet( pNtk, pNameOut );
    Abc_ObjAddFanin( pNet, pNode );
    return pNode;
}

/**Function*************************************************************

  Synopsis    [Create a constant 0 node driving the net with this name.]

  Description [Assumes that the net already exists.]
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Obj_t * Io_ReadCreateConst( Abc_Ntk_t * pNtk, char * pName, bool fConst1 )
{
    Abc_Obj_t * pNet, * pTerm;
    pTerm = fConst1? Abc_NtkCreateNodeConst1(pNtk) : Abc_NtkCreateNodeConst0(pNtk);
    pNet  = Abc_NtkFindNet(pNtk, pName);    assert( pNet );
    Abc_ObjAddFanin( pNet, pTerm );
    return pTerm;
}

/**Function*************************************************************

  Synopsis    [Create an inverter or buffer for the given net.]

  Description [Assumes that the nets already exist.]
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Obj_t * Io_ReadCreateInv( Abc_Ntk_t * pNtk, char * pNameIn, char * pNameOut )
{
    Abc_Obj_t * pNet, * pNode;
    pNet  = Abc_NtkFindNet(pNtk, pNameIn);     assert( pNet );
    pNode = Abc_NtkCreateNodeInv(pNtk, pNet);
    pNet  = Abc_NtkFindNet(pNtk, pNameOut);    assert( pNet );
    Abc_ObjAddFanin( pNet, pNode );
    return pNode;
}

/**Function*************************************************************

  Synopsis    [Create an inverter or buffer for the given net.]

  Description [Assumes that the nets already exist.]
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Obj_t * Io_ReadCreateBuf( Abc_Ntk_t * pNtk, char * pNameIn, char * pNameOut )
{
    Abc_Obj_t * pNet, * pNode;
    pNet  = Abc_NtkFindNet(pNtk, pNameIn);     assert( pNet );
    pNode = Abc_NtkCreateNodeBuf(pNtk, pNet);
    pNet  = Abc_NtkFindNet(pNtk, pNameOut);    assert( pNet );
    Abc_ObjAddFanin( pNet, pNode );
    return pNet;
}


/**Function*************************************************************

  Synopsis    [Provide an fopen replacement with path lookup]

  Description [Provide an fopen replacement where the path stored
               in pathvar MVSIS variable is used to look up the path
               for name. Returns NULL if file cannot be opened.]
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
FILE * Io_FileOpen( const char * FileName, const char * PathVar, const char * Mode, int fVerbose )
{
    char * t = 0, * c = 0, * i;
    extern char * Abc_FrameReadFlag( char * pFlag ); 

    if ( PathVar == 0 )
    {
        return fopen( FileName, Mode );
    }
    else
    {
        if ( c = Abc_FrameReadFlag( (char*)PathVar ) )
        {
            char ActualFileName[4096];
            FILE * fp = 0;
            t = Extra_UtilStrsav( c );
            for (i = strtok( t, ":" ); i != 0; i = strtok( 0, ":") )
            {
#ifdef WIN32
                _snprintf ( ActualFileName, 4096, "%s/%s", i, FileName );
#else
                snprintf ( ActualFileName, 4096, "%s/%s", i, FileName );
#endif
                if ( ( fp = fopen ( ActualFileName, Mode ) ) )
                {
                    if ( fVerbose )
                    fprintf ( stdout, "Using file %s\n", ActualFileName );
                    free( t );
                    return fp;
                }
            }
            free( t );
            return 0;
        }
        else
        {
            return fopen( FileName, Mode );
        }
    }
}

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////


