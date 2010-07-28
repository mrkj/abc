/**CFile****************************************************************

  FileName    [ioReadBaf.c]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Command processing package.]

  Synopsis    [Procedures to read AIG in the binary format.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 20, 2005.]

  Revision    [$Id: ioReadBaf.c,v 1.00 2005/06/20 00:00:00 alanmi Exp $]

***********************************************************************/

#include "io.h"

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Writes the AIG in the binary format.]

  Description []
  
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Ntk_t * Io_ReadBaf( char * pFileName, int fCheck )
{
    ProgressBar * pProgress;
    FILE * pFile;
    Vec_Ptr_t * vNodes;
    Abc_Obj_t * pObj, * pNode0, * pNode1;
    Abc_Ntk_t * pNtkNew;
    int nInputs, nOutputs, nLatches, nAnds, nFileSize, Num, i;
    char * pContents, * pName, * pCur;
    unsigned * pBufferNode;

    // read the file into the buffer
    nFileSize = Extra_FileSize( pFileName );
    pFile = fopen( pFileName, "rb" );
    pContents = ALLOC( char, nFileSize );
    fread( pContents, nFileSize, 1, pFile );
    fclose( pFile );

    // skip the comments (comment lines begin with '#' and end with '\n')
    for ( pCur = pContents; *pCur == '#'; )
        while ( *pCur++ != '\n' );

    // read the name
    pName = pCur;             while ( *pCur++ );
    // read the number of inputs
    nInputs = atoi( pCur );   while ( *pCur++ );
    // read the number of outputs
    nOutputs = atoi( pCur );  while ( *pCur++ );
    // read the number of latches
    nLatches = atoi( pCur );  while ( *pCur++ );
    // read the number of nodes
    nAnds = atoi( pCur );     while ( *pCur++ );

    // allocate the empty AIG
    pNtkNew = Abc_NtkAlloc( ABC_NTK_STRASH, ABC_FUNC_AIG );
    pNtkNew->pName = util_strsav( pName );
    pNtkNew->pSpec = util_strsav( pFileName );

    // prepare the array of nodes
    vNodes = Vec_PtrAlloc( 1 + nInputs + nLatches + nAnds );
    Vec_PtrPush( vNodes, Abc_NtkConst1(pNtkNew) );

    // create the PIs
    for ( i = 0; i < nInputs; i++ )
    {
        pObj = Abc_NtkCreatePi(pNtkNew);    
        Abc_NtkLogicStoreName( pObj, pCur );  while ( *pCur++ );
        Vec_PtrPush( vNodes, pObj );
    }
    // create the POs
    for ( i = 0; i < nOutputs; i++ )
    {
        pObj = Abc_NtkCreatePo(pNtkNew);   
        Abc_NtkLogicStoreName( pObj, pCur );  while ( *pCur++ ); 
    }
    // create the latches
    for ( i = 0; i < nLatches; i++ )
    {
        pObj = Abc_NtkCreateLatch(pNtkNew);
        Abc_NtkLogicStoreName( pObj, pCur );  while ( *pCur++ ); 
        Vec_PtrPush( vNodes, pObj );
        Vec_PtrPush( pNtkNew->vCis, pObj );
        Vec_PtrPush( pNtkNew->vCos, pObj );
    }

    // get the pointer to the beginning of the node array
    pBufferNode = (int *)(pContents + (nFileSize - (2 * nAnds + nOutputs + nLatches) * sizeof(int)) );
    // make sure we are at the place where the nodes begin
    if ( pBufferNode != (int *)pCur )
    {
        free( pContents );
        Vec_PtrFree( vNodes );
        Abc_NtkDelete( pNtkNew );
        printf( "Warning: Internal reader error.\n" );
        return NULL;
    }

    // create the AND gates
    pProgress = Extra_ProgressBarStart( stdout, nAnds );
    for ( i = 0; i < nAnds; i++ )
    {
        Extra_ProgressBarUpdate( pProgress, i, NULL );
        pNode0 = Abc_ObjNotCond( Vec_PtrEntry(vNodes, pBufferNode[2*i+0] >> 1), pBufferNode[2*i+0] & 1 );
        pNode1 = Abc_ObjNotCond( Vec_PtrEntry(vNodes, pBufferNode[2*i+1] >> 1), pBufferNode[2*i+1] & 1 );
        Vec_PtrPush( vNodes, Abc_AigAnd(pNtkNew->pManFunc, pNode0, pNode1) );
    }
    Extra_ProgressBarStop( pProgress );

    // read the POs
    Abc_NtkForEachCo( pNtkNew, pObj, i )
    {
        Num = pBufferNode[2*nAnds+i];
        if ( Abc_ObjIsLatch(pObj) )
        {
            Abc_ObjSetData( pObj, (void *)(Num & 3) );
            Num >>= 2;
        }
        pNode0 = Abc_ObjNotCond( Vec_PtrEntry(vNodes, Num >> 1), Num & 1 );
        Abc_ObjAddFanin( pObj, pNode0 );
    }
    free( pContents );
    Vec_PtrFree( vNodes );

    // remove the extra nodes
    Abc_AigCleanup( pNtkNew->pManFunc );

    // check the result
    if ( fCheck && !Abc_NtkCheckRead( pNtkNew ) )
    {
        printf( "Io_ReadBaf: The network check has failed.\n" );
        Abc_NtkDelete( pNtkNew );
        return NULL;
    }
    return pNtkNew;

}


////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////


