#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/prctl.h>

int main(int argc, char *argv[]) {
    // user get env to get the data
    char *execd_pgm_name = getenv("EXECD_PGM_NAME");

    // no variable print error
    if (execd_pgm_name == NULL) {
        fprintf(stderr, "no EXECD_PGM_NAME.\n");
        exit(EXIT_FAILURE);
    }

    // if the name change fail print error
    if (prctl(PR_SET_NAME, execd_pgm_name) == -1) {
        perror("prctl error");
        exit(EXIT_FAILURE);
    }

    // if system print enviroment fail print error
    if (system("printenv") == -1) {
        perror("system printenv error");
        exit(EXIT_FAILURE);
    }

    // if system ps fail print error
    if (system("ps") == -1) {
        perror("system ps error");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
