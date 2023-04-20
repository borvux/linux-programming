#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

sig_atomic_t process_b_pid = 0;

void signal_handler(int signum, siginfo_t* siginfo, void* context) {
    if (signum == SIGUSR1) {
        // set process_b_pid to the pid of the sending process
        process_b_pid = siginfo->si_value.sival_int;
    }
}

int main(int argc, char* argv[]) {
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = signal_handler;
    act.sa_flags = SA_SIGINFO;

    // register the signal handler
    if (sigaction(SIGUSR1, &act, 0) < 0) {
        perror("process_a");
        exit(EXIT_FAILURE);
    }

    printf("\n%s pid is %d.\n", argv[0], getpid());

    while (1) {
        pause();
        // check if signal received - process_b_pid should be > 0
        if (process_b_pid > 0) {
            printf("%s signal received from process B pid %d.\n", argv[0], process_b_pid);
            // send an acknowledgement
            union sigval ack_val;
            ack_val.sival_int = 0;
            if (sigqueue(process_b_pid, SIGUSR1, ack_val) < 0) {
                perror("process_a.sigqueue");
                exit(EXIT_FAILURE);
            }
            process_b_pid = 0;
        }
    }
}
