#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void display_help() {
    printf("Usage: stc [OPTION] [STRING]...\n");
    printf("Concatenate STRING to standard output.\n");
    printf("\n  -f <file>            specifies a file as the standard output\n");
}

int main(int argc, char** argv) {
    int opt;
    FILE *standard_output;

    while((opt = getopt(argc, argv, "f:h")) != -1) {
        switch(opt) {
            case 'f':
                if(access(optarg, F_OK) != 0) {
                    printf("stc: -f: %s: %s\n", optarg, strerror(errno));
                    return EXIT_FAILURE;
                }

                standard_output = fopen(optarg, "a");
                fseek(standard_output, 0, SEEK_END);
                break;
            case 'h':
                display_help();
            default:
                printf("Try \"stc -h\" for more information.\n");
        }
    }

    if (standard_output) {
        fprintf(standard_output, "%s", argv[optind]);
    } else {
        fprintf(stdout, "%s\n", argv[optind]);
    }

    fclose(standard_output);
    return 0;
}