%module pyabc
%{
    
#include <main.h>
#include <stdlib.h>
#include <signal.h>

void sigint_signal_handler(int sig)
{
    _exit(1);
}

    
int n_ands()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();
    Abc_Ntk_t * pNtk = Abc_FrameReadNtk(pAbc);

    if ( pNtk && Abc_NtkIsStrash(pNtk) )
    {        
        return Abc_NtkNodeNum(pNtk);
    }

    return -1;
}

int n_pis()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();
    Abc_Ntk_t * pNtk = Abc_FrameReadNtk(pAbc);

    if ( pNtk && Abc_NtkIsStrash(pNtk) )
    {        
        return Abc_NtkPiNum(pNtk);
    }

    return -1;
}


int n_pos()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();
    Abc_Ntk_t * pNtk = Abc_FrameReadNtk(pAbc);

    if ( pNtk && Abc_NtkIsStrash(pNtk) )
    {        
        return Abc_NtkPoNum(pNtk);
    }

    return -1;
}

int n_latches()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();
    Abc_Ntk_t * pNtk = Abc_FrameReadNtk(pAbc);

    if ( pNtk && Abc_NtkIsStrash(pNtk) )
    {        
        return Abc_NtkLatchNum(pNtk);
    }

    return -1;
}

int run_command(char* cmd)
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();
    int fStatus = Cmd_CommandExecute(pAbc, cmd);
    
    return fStatus;
}

bool has_comb_model()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();
    Abc_Ntk_t * pNtk = Abc_FrameReadNtk(pAbc);

    return pNtk && pNtk->pModel;
}

bool has_seq_model()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();
    Abc_Ntk_t * pNtk = Abc_FrameReadNtk(pAbc);

    return pNtk && pNtk->pSeqModel;
}

int n_bmc_frames()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();
    return Abc_FrameReadBmcFrames(pAbc);
}

int prob_status()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();
    return Abc_FrameReadProbStatus(pAbc);
}

bool is_valid_cex()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();
    Abc_Ntk_t * pNtk = Abc_FrameReadNtk(pAbc);

    return pNtk && Abc_FrameReadCex(pAbc) && Abc_NtkIsValidCex( pNtk, Abc_FrameReadCex(pAbc) );
}

bool is_true_cex()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();
    Abc_Ntk_t * pNtk = Abc_FrameReadNtk(pAbc);

    return pNtk && Abc_FrameReadCex(pAbc) && Abc_NtkIsTrueCex( pNtk, Abc_FrameReadCex(pAbc) );
}

int n_cex_pis()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();

    return Abc_FrameReadCex(pAbc) ? Abc_FrameReadCexPiNum( Abc_FrameReadCex(pAbc) ) : -1;
}

int n_cex_regs()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();

    return Abc_FrameReadCex(pAbc) ? Abc_FrameReadCexRegNum( Abc_FrameReadCex(pAbc) ) : -1;
}

int cex_po()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();

    return Abc_FrameReadCex(pAbc) ? Abc_FrameReadCexPo( Abc_FrameReadCex(pAbc) ) : -1;
}

int cex_frame()
{
    Abc_Frame_t* pAbc = Abc_FrameGetGlobalFrame();

    return Abc_FrameReadCex(pAbc) ? Abc_FrameReadCexFrame( Abc_FrameReadCex(pAbc) ) : -1;
}

%}

%init 
%{
    Abc_Start();
    signal(SIGINT, sigint_signal_handler);
%}

int n_ands();
int n_pis();
int n_pos();
int n_latches();

int run_command(char* cmd);

bool has_comb_model();
bool has_seq_model();

int  n_bmc_frames();
int  prob_status();

bool is_valid_cex();
bool is_true_cex();
int  n_cex_pis();
int  n_cex_regs();
int  cex_po();
int  cex_frame();


