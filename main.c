

#include "my_mastermind.h"

int main(int argc, char **argv)
{
    char secret_code[5];
    int attempts = 10;
    int code_set = 0;
    int i = 1;

    while (i < argc)
    {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
        {
         
            my_strcpy(secret_code, argv[i + 1]);
                    code_set = 1;
            i++;
        }
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
        {
            
            attempts = atoi(argv[i + 1]);
            i++;
        }
        i++;
    }

    if(code_set == 0) {
        generate_random_code(secret_code);
    }
    play_game(secret_code, attempts);
    return 0;
}