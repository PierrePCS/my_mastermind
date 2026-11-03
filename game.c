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
            secret_copy[i] = '*';
            guess_copy[i] = '*';
        }   
        i++;
    }
    int misplaced = 0;
    i = 0; 
    while (i < 4)
    {
        if (guess_copy[i] != '*')
        {
            int j = 0;
            while (j < 4)
            {
                if (guess_copy[i] == secret_copy[j])
                {
                    misplaced++;
                    secret_copy[j] = '*';
                    break;
                }
                j++;
            }
        }
        i++;
    }
    return misplaced;
}

void play_game(char *secret_code, int attempts)
{
    char guess[20];
    int round = 0;

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    while (round < attempts)
    {
        printf("---\nRound %d\n", round);
        
        while (1) 
        {
            write(1, ">", 1);
            
             if(read_input(guess) ==0) {
                return;
             }
            
            if(is_valid_code(guess) == 1) {
                break;
            }
             else printf("Wrong input!\n");
        }

        int well = count_well_placed(secret_code, guess);
        if (well == 4)
        {
            printf("Congratz! You did it!\n");
            return;
        }

        int misplaced = count_misplaced(secret_code, guess);
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well, misplaced);
        round++;
    }
}