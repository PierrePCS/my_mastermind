#include "my_mastermind.h"

int my_strlen(char *str)
{
int nombre = 0;

while(str[nombre] != '\0') {
    nombre++;
    }
    return nombre;
}

void my_strcpy(char *dest, char *src)
{
 int nombre = 0;

while(src[nombre] != '\0') {
        dest[nombre] = src[nombre];   
     nombre++;}
   dest[nombre] = '\0';
}    

int is_valid_code(char *str)
{
    if (my_strlen(str) != 4) {
        return 0;
    }
    int nombre = 0;
    while (str[nombre] != '\0')
    {
       if(str[nombre] < '0' || str[nombre] > '8' || is_char_in_str(&str[nombre + 1], str[nombre])) {
        return 0;
       }
        nombre++;
    }
    return 1;
}
int is_char_in_str(char *str, char c)
{
    int nombre = 0;
    while (str[nombre] != '\0')
    {
       if(str[nombre] == c) {
        return 1;
       }
        nombre++;
    }
    return 0;
}

void generate_random_code(char *secret_code)
{
    srand(time(NULL));
    int i = 0;
    secret_code[0] = '\0';

    while (i < 4)
    {
        char c = (rand() % 9) + '0';
        
        if(is_char_in_str(secret_code, c) == 0) {
            secret_code[i] = c;
            i++;
            secret_code[i] ='\0';
        }
       
    }
}


int read_input(char *buffer)
{
    char c;
    int i = 0;

    while (read(0, &c, 1) > 0)
    {
       if (c == '\n')
        {
            buffer[i] = '\0';
            return 1;
        }
        else if(i < 15) {
            buffer[i] = c;
                i++;
            }
        }
        return 0;
    }

int check_code_arg(int i, int argc, char **argv, char *secret_code)
{
    if (i + 1 >= argc || !is_valid_code(argv[i + 1]))
    {
        printf("Error: -c must be followed by 4 digits from 0 to 8.\n");
        return 0;
    }
    my_strcpy(secret_code, argv[i + 1]);
    return 1;
}

int is_valid_attempts(char *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 0;
    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return atoi(str) > 0;
}

int check_attempts_arg(int i, int argc, char **argv, int *attempts)
{
    if (i + 1 >= argc || !is_valid_attempts(argv[i + 1]))
    {
        printf("Error: -t must be followed by a positive number.\n");
        return 0;
    }
    *attempts = atoi(argv[i + 1]);
    return 1;
}