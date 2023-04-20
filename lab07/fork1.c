#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t ret;
    switch((ret = fork())) {
        case -1:
            perror("fork failed");
            break;
        case 0:
            //Return value from fork in the child is 0
            printf("child process, PID %d\n", getpid());
            if (execlp("ps", "ps", "-l", "--forest", NULL) == -1) {
                perror("Child exec of 'ps");
            }
            exit(EXIT_FAILURE);
        default:
            //Return value from fork in the parent is the child's PID
            printf("parent process, PID %d\n", getpid());
            printf("waiting for child, PID %d to complete \n", ret);
            pid_t child_pid = wait(0);
            printf("Child Process died, PID %d\n", child_pid);
            break;
    }

	exit(EXIT_SUCCESS);
}
