/* LICENSE
 * 
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>

#include "dSploitd.h"

/**
 * @brief SIGINT handler
 */
void interrupt_handler(int sig) {
  // close the main socket
  stop_daemon();
}

/**
 * @brief register main thread signal handlers
 * @returns 0 on success, -1 on error.
 */
int register_signal_handlers() {
  struct sigaction action;
  
  action.sa_handler = interrupt_handler;
  sigemptyset(&(action.sa_mask));
  action.sa_flags = 0;
  
  if(sigaction(SIGINT, &action, NULL)) {
    fprintf(stderr, "%s: sigaction: %s\n", __func__, strerror(errno));
    return -1;
  }
  
  //TODO: SIGSEGV core dumper ( like ettercap )
  
  return 0;
}