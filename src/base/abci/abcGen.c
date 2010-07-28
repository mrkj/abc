/**CFile****************************************************************

  FileName    [abc_.c]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Network and node package.]

  Synopsis    []

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 20, 2005.]

  Revision    [$Id: abc_.c,v 1.00 2005/06/20 00:00:00 alanmi Exp $]

***********************************************************************/

#include "abc.h"

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

void Abc_WriteLayer( FILE * pFile, int nVars, int fSkip1 );
void Abc_WriteComp( FILE * pFile );
void Abc_WriteFullAdder( FILE * pFile );

void Abc_GenAdder( char * pFileName, int nVars );
void Abc_GenSorter( char * pFileName, int nVars );

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    []

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Abc_GenAdder( char * pFileName, int nVars )
{
    FILE * pFile;
    int i;

    assert( nVars > 0 );

    pFile = fopen( pFileName, "w" );
    fprintf( pFile, "# %d-bit ripple-carry adder generated by ABC on %s\n", nVars, Extra_TimeStamp() );
    fprintf( pFile, ".model Adder%02d\n", nVars );

    fprintf( pFile, ".inputs" );
    for ( i = 0; i < nVars; i++ )
        fprintf( pFile, " a%02d", i );
    for ( i = 0; i < nVars; i++ )
        fprintf( pFile, " b%02d", i );
    fprintf( pFile, "\n" );

    fprintf( pFile, ".outputs" );
    for ( i = 0; i <= nVars; i++ )
        fprintf( pFile, " y%02d", i );
    fprintf( pFile, "\n" );

    fprintf( pFile, ".names c\n" );
    if ( nVars == 1 )
        fprintf( pFile, ".subckt FA a=a00 b=b00 cin=c s=y00 cout=y01\n" );
    else
    {
        fprintf( pFile, ".subckt FA a=a00 b=b00 cin=c s=y00 cout=%02d\n", 0 );
        for ( i = 1; i < nVars-1; i++ )
            fprintf( pFile, ".subckt FA a=a%02d b=b%02d cin=%02d s=y%02d cout=%02d\n", i, i, i-1, i, i );
        fprintf( pFile, ".subckt FA a=a%02d b=b%02d cin=%02d s=y%02d cout=y%02d\n", i, i, i-1, i, i+1 );
    }
    fprintf( pFile, ".end\n" ); 
    fprintf( pFile, "\n" );

    Abc_WriteFullAdder( pFile );
    fclose( pFile );
}

/**Function*************************************************************

  Synopsis    []

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Abc_GenSorter( char * pFileName, int nVars )
{
    FILE * pFile;
    int i, k, Counter, nDigits;

    assert( nVars > 1 );

    pFile = fopen( pFileName, "w" );
    fprintf( pFile, "# %d-bit sorter generated by ABC on %s\n", nVars, Extra_TimeStamp() );
    fprintf( pFile, ".model Sorter%02d\n", nVars );

    fprintf( pFile, ".inputs" );
    for ( i = 0; i < nVars; i++ )
        fprintf( pFile, " x%02d", i );
    fprintf( pFile, "\n" );

    fprintf( pFile, ".outputs" );
    for ( i = 0; i < nVars; i++ )
        fprintf( pFile, " y%02d", i );
    fprintf( pFile, "\n" );

    Counter = 0;
    nDigits = Extra_Base10Log( (nVars-2)*nVars );
    if ( nVars == 2 )
        fprintf( pFile, ".subckt Comp a=x00 b=x01 x=y00 y=y01\n" );
    else
    {
        fprintf( pFile, ".subckt Layer0" );
        for ( k = 0; k < nVars; k++ )
            fprintf( pFile, " x%02d=x%02d", k, k );
        for ( k = 0; k < nVars; k++ )
            fprintf( pFile, " y%02d=%0*d", k, nDigits, Counter++ );
        fprintf( pFile, "\n" );
        Counter -= nVars;
        for ( i = 1; i < nVars-2; i++ )
        {
            fprintf( pFile, ".subckt Layer%d", (i&1) );
            for ( k = 0; k < nVars; k++ )
                fprintf( pFile, " x%02d=%0*d", k, nDigits, Counter++ );
            for ( k = 0; k < nVars; k++ )
                fprintf( pFile, " y%02d=%0*d", k, nDigits, Counter++ );
            fprintf( pFile, "\n" );
            Counter -= nVars;
        }
        fprintf( pFile, ".subckt Layer%d", (i&1) );
        for ( k = 0; k < nVars; k++ )
            fprintf( pFile, " x%02d=%0*d", k, nDigits, Counter++ );
        for ( k = 0; k < nVars; k++ )
            fprintf( pFile, " y%02d=y%02d", k, k );
        fprintf( pFile, "\n" );
    }
    fprintf( pFile, ".end\n" ); 
    fprintf( pFile, "\n" );

    Abc_WriteLayer( pFile, nVars, 0 );
    Abc_WriteLayer( pFile, nVars, 1 );
    Abc_WriteComp( pFile );
    fclose( pFile );
}

/**Function*************************************************************

  Synopsis    []

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Abc_WriteLayer( FILE * pFile, int nVars, int fSkip1 )
{
    int i;
    fprintf( pFile, ".model Layer%d\n", fSkip1 );
    fprintf( pFile, ".inputs" ); 
    for ( i = 0; i < nVars; i++ )
        fprintf( pFile, " x%02d", i ); 
    fprintf( pFile, "\n" ); 
    fprintf( pFile, ".outputs" ); 
    for ( i = 0; i < nVars; i++ )
        fprintf( pFile, " y%02d", i ); 
    fprintf( pFile, "\n" ); 
    if ( fSkip1 )
    {
        fprintf( pFile, ".names x00 y00\n" ); 
        fprintf( pFile, "1 1\n" ); 
        i = 1;
    }
    else
        i = 0;
    for ( ; i + 1 < nVars; i += 2 )
        fprintf( pFile, ".subckt Comp a=x%02d b=x%02d x=y%02d y=y%02d\n", i, i+1, i, i+1 );
    if ( i < nVars )
    {
        fprintf( pFile, ".names x%02d y%02d\n", i, i ); 
        fprintf( pFile, "1 1\n" ); 
    }
    fprintf( pFile, ".end\n" ); 
    fprintf( pFile, "\n" ); 
}

/**Function*************************************************************

  Synopsis    []

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Abc_WriteComp( FILE * pFile )
{
    fprintf( pFile, ".model Comp\n" );
    fprintf( pFile, ".inputs a b\n" ); 
    fprintf( pFile, ".outputs x y\n" ); 
    fprintf( pFile, ".names a b x\n" ); 
    fprintf( pFile, "11 1\n" ); 
    fprintf( pFile, ".names a b y\n" ); 
    fprintf( pFile, "1- 1\n" ); 
    fprintf( pFile, "-1 1\n" ); 
    fprintf( pFile, ".end\n" ); 
    fprintf( pFile, "\n" ); 
}

/**Function*************************************************************

  Synopsis    []

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Abc_WriteFullAdder( FILE * pFile )
{
    fprintf( pFile, ".model FA\n" );
    fprintf( pFile, ".inputs a b cin\n" ); 
    fprintf( pFile, ".outputs s cout\n" ); 
    fprintf( pFile, ".names a b k\n" ); 
    fprintf( pFile, "10 1\n" ); 
    fprintf( pFile, "01 1\n" ); 
    fprintf( pFile, ".names k cin s\n" ); 
    fprintf( pFile, "10 1\n" ); 
    fprintf( pFile, "01 1\n" ); 
    fprintf( pFile, ".names a b cin cout\n" ); 
    fprintf( pFile, "11- 1\n" ); 
    fprintf( pFile, "1-1 1\n" ); 
    fprintf( pFile, "-11 1\n" ); 
    fprintf( pFile, ".end\n" ); 
    fprintf( pFile, "\n" ); 
}

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////

