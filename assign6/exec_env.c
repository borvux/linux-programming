#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *variable[6];
    // assign variables 
    variable[0] = "SHELL=/bin/bash";
    variable[1] = "HOME=/home";
    variable[2] = "PWD=/";
    variable[3] = "PATH=/usr/bin";
    variable[4] = argv[2];
    variable[5] = NULL;

    /*
    
    env_vars[0] = make_env_var(SHELL, getenv(SHELL));
    env_vars[1] = make_env_var(HOME, getenv(HOME));
    env_vars[2] = make_env_var(PWD, getenv(PWD));
    env_vars[3] = make_env_var(PATH, PATH_VALUE); // or variable[3] = "PATH=/usr/bin";
    env_vars[4] = pgm_name_var;
    env_vars[5] = NULL;


    */

    // if less then 2 argument, error message
    if (argc < 3) {
        fprintf(stderr, "need at least 2 arguments\n");
        exit(EXIT_FAILURE);
    }

    // print error message if error occur
    if (execle(argv[1], argv[1], NULL, variable) == -1) {
        perror("execle error");
        exit(EXIT_FAILURE);
    }

    return 0;
}
