#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>

int main(int argc, char **argv)
{
    int c;
    int digit_optind = 0;

    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"add",     required_argument, 0, 'a'},
            {"append",  no_argument,       0, 'A'},
            {"delete",  required_argument, 0, 'd'},
            {"remove",  required_argument, 0, 0 },
            {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "a:Ad",
                long_options, &option_index);

        if (c == -1)
            break;

        switch (c) {
            case 0:
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");
                break;
            case 'a':
                printf("%s with args %s\n", long_options[0].name, optarg);
                break;
            case 'A':
                printf("%s !\n", long_options[1].name);
                break;
            case 'd':
                printf("%s with args %s\n", long_options[2].name, optarg);
                break;

            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    return 0;
}
