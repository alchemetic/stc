#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void display_help() {
    printf("Usage: stc [OPTION] [STRING]...\n");
    printf("Concatenate STRING to standard output.\n");
    printf("\n  -f <file>            specifies a file as the standard output\n");
}

int main(int argc, char** argv) {
    int opt;
    char buffer[BUFFER_SIZE];
    FILE *output = stdout;

    while((opt = getopt(argc, argv, "f:h")) != -1) {
        switch(opt) {
            case 'f':
                if(access(optarg, F_OK) != 0) {
                    printf("stc: -f: %s: %s\n", optarg, strerror(errno));
                    return EXIT_FAILURE;
                }

                output = fopen(optarg, "a");
                fseek(output, 0, SEEK_END);
                break;
            case 'h':
                display_help();
                return EXIT_SUCCESS;
            default:
                printf("Try \"stc -h\" for more information.\n");
        }
    }

    if(argc - optind >= 1) {
        while(optind < argc) {
            snprintf(buffer, BUFFER_SIZE, "%s ", argv[optind]);
            fprintf(output, "%s", buffer);
            optind++;
        }
    }

    fclose(output);
    return EXIT_SUCCESS;
}