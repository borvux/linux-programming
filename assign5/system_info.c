#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_hostname() {
    FILE* fptr = fopen("/proc/sys/kernel/hostname", "r");
    if (fptr == NULL) {
        perror("print_hostname"); 
        exit(EXIT_FAILURE);
    }
    char hostname[64];
    fscanf(fptr, "%s", hostname);
    fclose(fptr);
    printf("Current Host Name:           %s\n", hostname);
}

void print_cpu_info() {
    FILE* fptr = fopen("/proc/cpuinfo", "r");
    if (fptr == NULL) { 
        perror("print_cpu_info");
        exit(EXIT_FAILURE);
    }
    char line[1024], vendorID[256], modelName[256];
    while (fgets(line, sizeof(line), fptr) != NULL) {
        if (strncmp(line, "vendor_id", 9) == 0) {
            sscanf(line, "%*s %*s %s", vendorID);
        } else if (strncmp(line, "model name", 10) == 0) {
            sscanf(line, "%*s %*s %*s %[^\n]", modelName);
        }
    }
    fclose(fptr);
    printf("CPU Type:                    %s\n", vendorID);
    printf("CPU Model:                   %s\n", modelName);
}

void print_kernel_version() {
    FILE* fptr = fopen("/proc/version", "r");
    if (fptr == NULL) {
        perror("print_kernel_version");
        exit(EXIT_FAILURE);
    }
    char version[1024];
    //get the character array
    fgets(version, sizeof(version), fptr);
    //close it
    fclose(fptr);
    printf("Kernel Version:              %s", version);
}

void print_memory_info() {
    FILE* fptr = fopen("/proc/meminfo", "r");
    if (fptr == NULL) {
        perror("print_memory_info");
        exit(EXIT_FAILURE);
    }
    char line[1024], mem[256];
    long int size;
    while (fgets(line, sizeof(line), fptr) != NULL) {
        // to extract a string of characters until it enounters a colon 
        if (sscanf(line, "%[^:]: %ld", mem, &size) == 2) {
            // if memtotal is found print it
            if (strcmp(mem, "MemTotal") == 0) {
                printf("Memory Configured:           %ld kB\n", size);
            // and if menavailbe is found print it
            } else if (strcmp(mem, "MemAvailable") == 0) {
                printf("Memory Available:            %ld kB\n", size);
            }
        }
    }
    fclose(fptr);
}

void print_uptime() {
    FILE* fptr = fopen("/proc/uptime", "r");
    if (fptr == NULL) {
        perror("print_uptime");
        exit(EXIT_FAILURE);
    }
    double uptime, idleTime;
    // read the uptime
    fscanf(fptr, "%lf %lf", &uptime, &idleTime);
    fclose(fptr);
    //convert it into days, hours, minutes, and seconds
    int days = (int)uptime / (24 * 3600);
    int hours = ((int)uptime % (24 * 3600)) / 3600;
    int minutes = ((int)uptime % 3600) / 60;
    int seconds = ((int)uptime % 60);
    printf("Uptime:                      %d:%02d:%02d:%02d\n", days, hours, minutes, seconds);
}

void print_user_time() {
    FILE* fptr = fopen("/proc/stat", "r");
    if (fptr == NULL) {
        perror("print_user_time");
        exit(EXIT_FAILURE);
    }
    char line[1024];
    // get the cpu userage
    fgets(line, sizeof(line), fptr);
    fclose(fptr);
    unsigned long long userTime, niceTime, systemTime;
    // get the user time
    sscanf(line, "cpu %llu %llu %llu", &userTime, &niceTime, &systemTime);
    printf("Time Spent in User Mode:     %llu ms\n", userTime);
}

void print_system_time() {
    FILE* fptr = fopen("/proc/stat", "r");
    if (fptr == NULL) {
        perror("print_system_time");
        exit(EXIT_FAILURE);
    }
    char line[1024];
    // get the cpu usage again
    fgets(line, sizeof(line), fptr);
    fclose(fptr);
    unsigned long long userTime, niceTime, systemTime;
    // get the system time
    sscanf(line, "cpu %llu %llu %llu", &userTime, &niceTime, &systemTime);
    printf("Time Spent in System Mode:   %llu ms\n", systemTime);
}

void print_idle_time() {
    FILE* fptr = fopen("/proc/stat", "r");
    if (fptr == NULL) {
        perror("print_idle_time");
        exit(EXIT_FAILURE);
    }
    char line[1024];
    // get the cpu usage again
    fgets(line, sizeof(line), fptr);
    fclose(fptr);
    unsigned long long userTime, niceTime, systemTime, idleTime;
    // get the idel time
    sscanf(line, "cpu %llu %llu %llu %llu", &userTime, &niceTime, &systemTime, &idleTime);
    printf("Time Spent in Idle Mode:     %llu ms\n", idleTime);
}

//main output
int main() {
    printf("----------------------------------------------------------------------------\n");
    printf("                             System Information\n");
    printf("----------------------------------------------------------------------------\n");
    print_hostname();
    print_cpu_info();
    print_kernel_version();
    print_memory_info();
    print_uptime();
    print_user_time();
    print_system_time();
    print_idle_time();
    printf("----------------------------------------------------------------------------\n");
    return 0;
}