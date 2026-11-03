#ifndef MY_MASTERMIND_H
#define MY_MASTERMIND_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// Fonctions de utils.c
int my_strlen(char *str);
void my_strcpy(char *dest, char *src);
int is_valid_code(char *str);
int is_char_in_str(char *str, char c);
void generate_random_code(char *secret_code);
int read_input(char *buffer);

// Fonctions de game.c
int count_well_placed(char *secret, char *guess);
int count_misplaced(char *secret, char *guess);
void play_game(char *secret_code, int attempts);

#endif