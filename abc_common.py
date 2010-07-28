from pyabc import *

"""
The functions that are currently available from module _abc are:

int n_ands();
int n_pis();
int n_pos();
int n_latches();
int n_bmc_frames();
int n_prob_status(); 1 = unsat, 0 = sat, -1 = unsolved
int n_latches();

int run_command(char* cmd);

bool has_comb_model();
bool has_seq_model();
"""

#global variables

stackno = 0

# Function definitions:
# simple functions: ________________________________________________________________________
# set_globals, abc, q, x, has_any_model, is_sat, is_unsat, check_status, pushcurr, popcurr

def set_globals():
    global G_C, G_G
    nl=n_latches()
    na=n_ands()
    if nl < 200 & na < 3000:
        G_C = 75000
        G_G = 750000
    else:
        G_C = 500000
        G_G = 2000000
    print('values for deep BMC for local conflicts: %d'%G_C)
    print('values for deep BMC for total conflicts: %d'%G_G)

def abc():
    """this puts the system into direct abc input mode"""
    print "Entering ABC direct-input mode. Type q to quit ABC-mode"
    n = 0
    while True:
        print 'abc %d> '%n,
        n = n+1
        s = raw_input()
        if s == "q":
            break
        run_command(s) 

def q():
    exit()
    'y'

def x(s):
    """execute an ABC command"""
    print "RUNNING: ", s
    run_command(s)

def has_any_model():
    """ check if a satisfying assignment has been found"""
    res = has_comb_model() or has_seq_model()
    #print "has_any_model(): ", res
    return res

def is_unsat():
    t = prob_status()
    if t == 1:
        return True
    else:
        return False

def is_sat():
    return has_any_model()

STATUS_UNKNOWN = -1
STATUS_SAT = 0
STATUS_UNSAT = 1

def check_status():

    if is_sat():
        return STATUS_SAT
    
    if is_unsat():
        return STATUS_UNSAT
        
    return STATUS_UNKNOWN

def pushcurr():
    """ saves the current network"""
    global stackno
    s = "w curr%d.aig"%stackno
    stackno = stackno + 1
    run_command(s)

def popcurr():
    """ restores the previous network """
    global stackno
    if stackno > 0:
        s = "r curr%s.aig"%stackno
        run_command(s)
        stackno = stackno - 1
    else:
        return "stack count is wrong"


#more complex functions: ________________________________________________________
# simplify, abstract, pba, speculate, basic_verify, dprove3

def simplify():
    set_globals()
    n=n_ands()
    if n > 30000:
        if n<45000:
            x("&get;&scl;&dc2;&put;dr;&get;&lcorr;&dc2;&put;dr;&get;&scorr;&fraig;&dc2;&put;dr;&get;&scorr -F 2;&dc2;&put;w temp.aig")
        else:
            x("&get;&scl;&dc2;&put;dr;&get;&lcorr;&dc2;&put;dr;&get;&scorr;&fraig;&dc2;&put;dr;&get;&dc2;&put;w temp.aig")
    n = n_ands()
    if n < 30000:
        if n > 15000:
            x("scl;rw;dr;lcorr;rw;dr;scorr;fraig;dc2;dr;dc2rs;w temp.aig")
        else:
            x("scl;rw;dr;lcorr;rw;dr;scorr;fraig;dc2;dr;scorr -F 2;dc2rs;w temp.aig")
        
    #x("ps")
    
    if n < 10000:
        m = min( 30000/n, 8 )
        if m > 2:
            x( "scorr -F %d"%m )
            run_command("ps")



def abstract():
    set_globals()
    global G_C,G_G
    
    def loop_abstract(cmd):
    # loops (cmd; absc) until no cex is found (TRUE) or no latch reduction (FALSE)            
        
        while True:

            x(cmd)

            if not has_any_model():
                # no counterexample found
                print "No CEX found"
                return True
            
            #refine abstraction
            x("&r 1.aig; &abs_refine; &w 1.aig; &abs_derive; &put; w gabs.aig")
            
            latches_after = n_latches()
            
            if latches_before == latches_after:
                print "absc: No reduction!."
                return False
 
    # loops through simulation first then bmc. Returns FALSE if there was no latch reduction, else TRUE
    
    # initial cex based abstraction
    latches_before = n_latches()
    x("&get; &abs_start -C 10000 -R 2; &w 1.aig; &abs_derive; &put; w gabs.aig")
    run_command('ps')
    latches_after = n_latches()
    
    if latches_before == latches_after:
        print "abstart: No reduction!"
        return False
    
    # refinement loop
    if (n_ands() + n_latches() + n_pis()) < 50000:
        for cmd in [ 'simh', 'simhh' ]:
            if not loop_abstract(cmd): #if no reduction
                return False
    for cmd in [ 'bmc2' ]:
        if not loop_abstract(cmd+ ' -C %d -G %d'%(G_C,G_G)): # if no reduction
            return False        
    x('w final_abstract.aig')
    return True

def pba():
    """binary search for # frames to do proof based abstraction"""
    set_globals()
    #binary search 
    lower = 1
    # set upper to be the depth of bmc that can be done ia a reasonable number of resources
    c = G_C/10
    g = G_G/10
    x('bmc2 -C %d -G %d'%(c,g))
    upper = n_bmc_frames() + 1
    latches_before = n_latches()
    pushcurr()
    eps = upper - lower
    
    while eps > 1:
        run_command('r curr0.aig') # get the original file
        dp = (upper - lower)/2
        p = lower + dp
        s = "&get;&pba_start -d -C 25000 -F %d; &w 1.aig; &abs_derive; &put; w gabs.aig"%p
        x(s)
        
        latches_after = n_latches()
        if latches_after < latches_before:  # if reduction in FF
            lower = p
            run_command('ps')
        else:
            upper = p
        eps = upper - lower
    
    if (latches_before == latches_after)&(p == lower): #if last was unsat but no reduction
        print('no reduction')
        return False
            
    # re-do the abstraction on the lower number of frames
    if (p == upper): # need to redo the last successful attempt
        run_command('r curr0.aig')
        s = "&get; &pba_start -d -C 25000 -F %d; &ps; &w 1.aig; &abs_derive; &put; w gabs.aig"%lower
        x(s)
        run_command('ps')
    
    # now we have to see if abstraction is invalid (has cex) and if so continue refinement.
    if (n_ands() + n_latches() + n_pis()) < 30000:
        for cmd in [ 'simh', 'simhh']:
            while True:
                x(cmd)
                if not has_any_model(): # no counterexample found
                    #print "No CEX found"
                    break             
                #refine the abstraction with the cex
                run_command("&r 1.aig; &abs_refine; &w 1.aig; &abs_derive; &put; w gabs.aig")
                
                latches_after = n_latches()
                
                if latches_before == latches_after:
                    print "absc: No reduction!."
                    break
    latches_after = n_latches()
    #print('latches_before = %d'%latches_before)
    #print('latches_after = %d'%latches_after)
    while True:
        latches_after = n_latches()
        if latches_before == latches_after:
            # don't want to repeat anything if no
            # reduction can be obtained
            break
        # now we want to try really hard to make sure it is a good abstraction
        x('bmc2  -C %d -G %d'%(G_C,G_G)) # increase conflicts to very high
        if has_any_model(): # if has cex
            run_command('&r 1.aig; &abs_refine; &w 1.aig; &abs_derive; &put; w gabs.aig')
        else:
            break
    
    latches_after = n_latches()
    x('w final_pba.aig')
    if (latches_before > latches_after):
        print("PBA: reduction successful. Latches reduced from %d to %d"% (latches_before, latches_after))
        return True # found a reduction
    else:
        print('PBA: no reduction found')
        return False
    

def speculate():
    set_globals()
    def loop_speculate(cmd):
        # returns false if no new outputs
    
        x(cmd)
        if n_pos_before == n_pos():
            return False
        
        while has_any_model():
        
            x(cmd)
            if n_pos_before == n_pos():
                return False
        return True

    n_pos_before = n_pos()
    simplify()
    
    x("&get; &equiv -s -W 512 -F 2000; &semi -F 50; &speci -F 1000 -C 25000;&srm -s; r gsrm.aig; &w gore.aig")
    run_command('ps')
    if n_pos_before == n_pos():
        print 'No new outputs. Quitting speculation'
        return False
    
    for cmd in ['specs', 'specsh' ]:
        loop_speculate(cmd)
        
    while True: # now try real hard to get the last cex.
        print('speculating hard with BMC %d conflicts'%G_C)
        run_command('&r gore.aig;&srm ;r gsrm.aig')
        simplify()
        run_command('dprove -rcbkmiu -B 10 -D 10') # get rid of the easy outputs
        if n_pos_before == n_pos():
            print 'No new outputs. Quitting speculation'
            break
        simplify()
        run_command('bmc2  -C %d -G %d'%(G_C,G_G))
        if not has_any_model():
            break
        run_command('&resim -m; &w gore.aig')
        if n_pos_before == n_pos():
            print 'No new outputs. Quitting speculation'
            break
    x('w final_speculate.aig')
    if n_pos_before == n_pos():
        return False
    else:
        return True
    
def basic_verify():
    set_globals()
    if is_sat():
        return STATUS_SAT
    
    if ( n_latches() + n_pis() ) < 100:
        x("reachx")
        
        status = check_status()
        
        if status != STATUS_UNKNOWN:
            return status
    
    x('int  -r -C %d -F 10000'%G_C)

    status = check_status()
    
    if status != STATUS_UNKNOWN:
        return status

    x('orpos')
    x("ind -C %d -F 2000"%G_C)
    x('w final_aig.aig')

    return check_status()

def dprove3():
    # works on the currently loaded network
    if n_ands() < 10000:
        
        print ('\nRUNNING dprove')
        run_command('dprove ')
        if n_latches() == 0:
            return 'UNSAT'
        
    print('\nRUNNING simplify')
    simplify()
    if n_latches() == 0:
            return 'UNSAT'
    run_command('trm')
    
    print('\nRUNNING abstract')
    abstract()
    if n_latches() == 0:
            return 'UNSAT'
        
    print('\nRUNNING pba')
    pba()
    print('\nRUNNING speculate')
    speculate()
    if n_latches() == 0:
            return 'UNSAT'
    
    print('\nRUNNING basic verify')
    basic_verify()
    return check_status()
    
