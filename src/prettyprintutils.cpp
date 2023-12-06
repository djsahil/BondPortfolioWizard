#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

void printToConsole(std::string output) {
	std::cout << output;
}

void printWelcomeHeader() {
	printToConsole("\n************************************\n\tBOND PORTFOLIO WIZARD\n************************************\n");
}

void printExitFooter() {
	printToConsole("Exiting Application...\n\n\n");
	printToConsole("\n************************************\n\tBOND PORTFOLIO WIZARD\n************************************\n");
	printToConsole("Application Closed!\n");
}


void printLoginPrompt() {
	printToConsole("\n\t1. Login as an existing user\n\t2. Run in demo mode\n\t3. Exit\n");
}

void printPortfolioManagerMenu() {
	printToConsole("\n\t1. View my Portfolio\n\t2. Assess Interest Rate Risk\n\t3. Hedge against interest rate movements\n\t4. Lookup a Bond\n\t5. Enter a Position\n\t6. Exit\n");
}

void printNewPositionMenu() {
	printToConsole("\n\t1. Enter a Bond Position by CUSIP\n\t2. Enter a Bond Position manually\n\t3. I am finished entering new positions\n");
}

void printNoFunction() {
	printToConsole("NOT AN AVAILABLE FUNCTION YET!\n\n");
}
