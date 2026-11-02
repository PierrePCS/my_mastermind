#include "my_mastermind.h"

int count_well_placed(char *secret, char *guess)
{
  int well = 0;
  int i = 0;
  while(i < 4) {
    if (secret[i] == guess[i]){
        well++;
    } 
     i++;
  }
return well;
}
int count_misplaced(char *secret, char *guess)
{
    char secret_copy[5];
    char guess_copy[5];
    
    my_strcpy(secret_copy, secret);
    my_strcpy(guess_copy, guess);
    int i = 0;
    while (i < 4)
    {
        if (secret_copy[i] == guess_copy[i])
        {
         
        }
        i++;
    }
    
}