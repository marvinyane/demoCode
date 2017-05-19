#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int ch;
    while ((ch = getopt(argc, argv, "a:b:c")) != -1)
    {
        switch (ch)
        {
            case 'a':
                printf("-a with args : %s.\n", optarg);
                break;
            case 'b':
                printf("-b with args : %s.\n", optarg);
                break;
            case 'c':
                printf("-c\n");
                break;
        }
    }

    return 0;
}
