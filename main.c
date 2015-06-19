#include <stdlib.h>		// strcpy
#include <stdio.h>		// printf
#include <string.h>
#include <unistd.h> 	// usleep
#include <math.h>

// Outside libraries
#include "RS-232/rs232.h"

// Custom definitions
#include "headers/relay.h"
#include "headers/comms.h"
#include "headers/bank.h"

/* TODO:
 - Make read text write to the buffer provided
 - Begin creating objects: switches, bank, board
 - Create code to take commands from CL arguements
 - Create interface to use without command lind arguements
 - Create Code to figure out which port to use
 - Refactor code in to seperate headers and object files
 - Edit makefile to work right...
*/

void printHelp();

int main(int argc, char** argv)  {
	printf("DEBUG: ARGC = %i \n", argc);

	if (argc > 1) {
		printf("DEBUG: ARGV[1] = %s \n", argv[1]);
		if (strcmp(argv[1], "fetch") == 0) {

		}
	}

	printf("... initializing bank ...\n");
	struct Bank* bankZero = bankInit();

	printf("... adding relays ...\n");
	bankAddRelay(bankZero, 'P', 1);
	bankAddRelay(bankZero, 'P', 2);
	bankAddRelay(bankZero, 'V', 1);
	bankAddRelay(bankZero, 'V', 2);
	bankAddRelay(bankZero, 'V', 3);
	bankAddRelay(bankZero, 'L', 1);
	bankAddRelay(bankZero, 'L', 2);
	bankAddRelay(bankZero, 'L', 3);
	bankAddRelay(bankZero, 'L', 4);
	bankAddRelay(bankZero, 'L', 5);
	bankAddRelay(bankZero, 'L', 6);
	bankAddRelay(bankZero, 'L', 7);
	bankAddRelay(bankZero, 'L', 8);
	bankAddRelay(bankZero, 'L', 9);
	bankAddRelay(bankZero, 'L', 10);
	bankAddRelay(bankZero, 'L', 11);
	bankAddRelay(bankZero, 'L', 12);
	bankAddRelay(bankZero, 'L', 13);
	bankAddRelay(bankZero, 'L', 14);
	bankAddRelay(bankZero, 'L', 15);
	bankAddRelay(bankZero, 'L', 16);
	bankAddRelay(bankZero, 'L', 17);

	printf("... fetching relay status ...\n");
	bankFetchStatus(bankZero);

	printf("... fetching timer status ...\n");
	bankFetchTimers(bankZero);

	printf("... almost done ...\n");
	char userResponse[80];

	printf("Setup complete!\n\n");

/* TO IMPLEMENT LATER:
	printf("\n");
	printf("SYNTAX: ./gv [command] (char)(#)");
	printf("\n\n");

	printf("\t Type the following commands after './gv ' (minus the apostrophes). If you need further\n");
	printf("\t explanation of how things work, type './gv help [command]', replacing [command] with\n");
	printf("\t an option below.\n\n");
*/

	printHelp();

	while (strcmp(userResponse, "quit") != 0) {

		printf("What would you like to do? ");
		gets(userResponse);

		// Break down user response
		char firstWord[20];
		char firstChar;
		int firstNum;

		char* firstSpace = strstr(userResponse, " ");
		if (firstSpace == NULL) {
			// entry is only one word long
			strcpy(firstWord, userResponse);
			// printf("DEBUG: firstSpace == NULL\n");
			// printf("DEBUG: firstWord = %s\n", firstWord);
		} else {
			// Assign first char and first num
			// printf("DEBUG: firstSpace = %p\n", (void *)firstSpace);
			// printf("DEBUG: &userresponse = %p\n", (void *)&userResponse);
			// how many bytes does it take to get to space?
			int bytesToSpace = (int) firstSpace - (int) &userResponse;
			// printf("DEBUG: bytesToSpace = %i\n", bytesToSpace);

			firstChar = userResponse[bytesToSpace + 1];
			firstNum = (int) userResponse[bytesToSpace + 2] - '0';

			// printf("DEBUG: firstChar = %c\n", firstChar);
			// printf("DEBUG: firstNum = %i\n", firstNum);

			// TODO: add additional verifications: range char andnum
		}


		if (strstr(userResponse, "add") != NULL) {
			bankAddRelay(bankZero, firstChar, firstNum);

		} else if (strstr(userResponse, "report") != NULL) {
			bankReport(bankZero);

		} else if (strstr(userResponse, "fetch") != NULL) {
			bankFetchStatus(bankZero);
			bankFetchTimers(bankZero);

		} else if (strstr(userResponse, "switch") != NULL) {
			// bankSwitch(bankZero, firstChar, firstNum);
			printf("TODO: Create bankSwitch function\n");

		} else if (strstr(userResponse, "on") != NULL) {
			bankTurnRelayOn(bankZero, firstChar, firstNum);

		} else if (strstr(userResponse, "off") != NULL) {
			bankTurnRelayOff(bankZero, firstChar, firstNum);

		} else if (strstr(userResponse, "help") != NULL) {

		} else if (strstr(userResponse, "quit") != NULL) {
			// do nothing
		} else {

		}
	}

	return 0;
}


void printHelp() {
	printf(" GROVOLUTION CLI \n");
	printf(" OPTIONS: \n");
	printf("\t add [char][#]\t\t- add a relay, i.e.: ./gv add P 3 \n");
	printf("\t report\t\t\t- show the current status of relays \n");
	printf("\t fetch\t\t\t- get the current status of the relays from the PLC \n");
	printf("\t switch [char][#]\t- turn a relay to its opposite status i.e.: ./gv switch P3\n");
	printf("\t on [char][#]\t\t- turn relay on\n");
	printf("\t off [char][#]\t\t- turn relay off\n");
	printf("\t help\t\t\t- show this screen again\n\n");
	printf("\t quit\t\t\t- exit the program\n\n");

	return;
}
