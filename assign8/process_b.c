#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define UNUSED (void)

sig_atomic_t send_signal_flag = 0;
sig_atomic_t send_to_pid = 0;
sig_atomic_t ack_received_flag = 0;

void signal_handler(int signum, siginfo_t* siginfo, void* context) {
    UNUSED context;
    if (signum == SIGINT) {
        // set a flag to send SIGUSR1 to a process
        send_signal_flag = 1;
        // get the dest pid
        send_to_pid = siginfo->si_value.sival_int;
    } else if (signum == SIGUSR1) {
        // handle acknowledgment signal from process A
        printf("process_b received acknowledgment signal from process A.\n");
        ack_received_flag = 1;
    }
}

void send_signal_to_pid(pid_t dest_pid) {
    // use sigqueue to send the SIGUSR1 signal along with the dest_pid
    printf("process_b sending signal to pid %d.\n", dest_pid);
    union sigval my_pid;
    my_pid.sival_int = getpid();
    if (sigqueue(dest_pid, SIGUSR1, my_pid) < 0) {
        perror("process_b.send_signal_to_pid");
    }
}

void do_work() {
    pause();
    if (send_signal_flag) {
        printf("\nSignal received. The send_to_pid is %d.\n", send_to_pid);
        send_signal_to_pid(send_to_pid);
        send_signal_flag = 0;
        send_to_pid = 0;
    } else if (ack_received_flag) {
        printf("\nAcknowledgment received.\n");
        ack_received_flag = 0;
    }
}

int main(int argc, char* argv[0]) {
    UNUSED argc;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = signal_handler;
    act.sa_flags = SA_SIGINFO;
    if (sigaction(SIGINT, &act, 0) < 0) {
        perror("process_b");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGUSR1, &act, 0) < 0) {
        perror("process_b");
        exit(EXIT_FAILURE);
    }
    printf("\n%s pid is %d.\n", argv[0], getpid());
    while (1) {
        do_work();
    }
}
