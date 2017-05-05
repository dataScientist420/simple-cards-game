/******************************************************************************
                         ____  ____                                                 
                 		/ __/ / __/__  __ _____________                            
                	   / /_	 _\ \/ _ \/ // / __/ __/ -_|                           
               		   \__/	/___/\___/\___/_/  \__/\__/                            
                                                                                                                                                                          
*******************************************************************************
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
  @file:    game.c                                                                                                           
  @author:  Victor Neville 
  @description: The program simulates a virtual casino with a simple cards game.
				The user must place a bet and he must guess the queen position.
				If the user got wrong, he loses his bet, otherwise he wins 
				3 times the amount of the bet. 
				When user's cash gets equal to zero, the program ends.                                                                                             
  @date: 29/5/2014                                                                                                                                                                                             
******************************************************************************/

/* avoiding warnings of fprintf and fscanf on windows */
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* windows macros */
#if defined(_WIN32) || defined(_WIN64) 
#include <windows.h>
#define CLEAR_SCREEN system("cls")   
#define SLEEP(ms)    Sleep(ms)

/* linux macros */
#elif defined(__linux__) 
#include <unistd.h>
#define CLEAR_SCREEN system("clear")    
#define SLEEP(ms)    usleep(ms * 1000)
#endif

/* this macro is a replacement of fflush(stdin) */
#define FFLUSH  { char c; do { c = getchar(); } while (c != EOF && c != '\n'); }

/****************************** CONSTANTS ************************************/
#define JACK          'J'
#define QUEEN         'Q'
#define KING          'K'
#define N             3
#define DELAY         2000
#define INITIAL_CASH  100
#define BET_MSG       "VIRTUAL CASINO\ncash = %d$\n\nEnter your bet ($): "
#define GUESS_MSG     "\nEnter the queen position (1, 2 or 3): "
#define RESULT_MSG    "\nResult = %c, %c, %c\ncash = %d$\n"

typedef enum { BET, GUESS } input_t;

/******************************************************************************
 @name: get_bet
 @description: This function allows the user to enter an integer on the keyboard.
 @parameters:
 - int: min value
 - int: max value
 - input_t: input type
 @return: an integer value between min and max                                                                                
******************************************************************************/
int get_int(int min, int max, input_t input)
{
    int val;
    
    do {
		CLEAR_SCREEN;

		switch (input) {
		case BET:
			fprintf(stdout, BET_MSG, max);
			break;
		case GUESS:
			fprintf(stdout, GUESS_MSG);
			break;
		}
		fscanf(stdin, "%d", &val);
		FFLUSH; 

	} while (val > max || val < min);
	
	return val;
}

/******************************************************************************
 @name: swap
 @description: This function swap 2 character values.
 @parameters:
 - char *: first character modified by reference
 - char *: second character modified by reference                                                                                 
******************************************************************************/
void swap(char *a, char *b)
{
    char tmp = *a; 
	     *a  = *b; 
	     *b  = tmp;
}

/******************************** ENTRY POINT ********************************/
int main()  
{
	char buf[N] = { JACK, QUEEN, KING };
	int i, guess, bet, cash = INITIAL_CASH;

	srand((unsigned)time(NULL));

	while (cash > 0) {
		bet = get_int(1, cash, BET);
		
		fprintf(stdout, "\nShuffling ...\n");
		SLEEP(DELAY);

		/* Shuffling cards */
		for (i = 0; i < N; i++) 
			swap(buf + rand() % N, buf + rand() % N);
	
		guess = get_int(1, N, GUESS);

		/* update cash */
		cash += (buf[guess-1] == QUEEN) ? N*bet : -bet; 
		
		/* display results */
		fprintf(stdout, RESULT_MSG, buf[0], buf[1], buf[2], cash);
		SLEEP(DELAY * 2);
	}
	return 0;
}

/*****************************************************************************/
