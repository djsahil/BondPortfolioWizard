/*
 * Controller.cpp
 *
 *  Created on: Sep 26, 2023
 *  Author: Sahil Shah - Rutgers MQF OOP 1 - FALL 2023
 */
/* MAIN DRIVER FOR BOND PORTFOLIO WIZARD
 *
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include "csviostream.h"
#include "prettyprintutils.h"
#include "PortfolioManager.h"

using namespace std;

int switchLoginMode(int mode) {
	switch(mode) { 
		case 1: {
			string id;
			printToConsole("Enter User Id: ");
			cin >> id;

			if(isInUsersDB(id)) {
				string pass;
				printToConsole("Enter password: ");
				cin >> pass;

				if(authenticateUser(id,pass)) {

					// Instantiate PortfolioManager with the User's Portfolio
					Portfolio portfolio = getPortfolioForUser(id);
					PortfolioManager portfolioManager(portfolio);
					portfolioManager.manage();

					//Once user is done interacting, grab the updated Portfolio from Portfolio Manager
					Portfolio updatedPortfolio = portfolioManager.getPortfolio();

					//Persist state of Portfolio back to csv
					updateUserPortfolio(id,updatedPortfolio);


				}
			}
			break;
		}
		case 2: {
			printToConsole("YOU HAVE BEEN PROVIDED AN EMPTY DEMO PORTFOLIO - THIS WILL BE DISCARDED WHEN YOU EXIT!\n\n");

			// Create a blank Portfolio
    		Portfolio portfolio;

		    // Instantiate PortfolioManager with the blank Portfolio
		    PortfolioManager portfolioManager(portfolio);
		    portfolioManager.manage();

			return mode;
		}
		case 3:
			return mode;
		default:
			printNoFunction();
			break;
	}
	return mode;
		

}
void run() { 

	int loginMode{0};
	while(loginMode != 3) {
		printWelcomeHeader();
		printLoginPrompt();
		cin >> loginMode;
		loginMode = switchLoginMode(loginMode);
	}
	printExitFooter();
	sleep(1);

}

void init() { 

	loadZeroCurve();
	loadBondsData(); 
	loadUsers(); 
	sleep(1);
}

int main() { 

	init(); 
	run(); 
	return 0; 
}




