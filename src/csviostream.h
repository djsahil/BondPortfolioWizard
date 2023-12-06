/*
 * csviostream.h
 *
 *  Created on: Sep 26, 2023
 *      Author: sahil
 */

#ifndef CSVIOSTREAM_H_
#define CSVIOSTREAM_H_

#include <string>
#include "Bond.h"
#include "Portfolio.h"

	//init() functions
	void loadZeroCurve();
	void loadBondsData();
	void loadUsers();

	//utility functions
	bool isInBondsMap(std::string cusip);
	bool isInZeroCurve(std::string cusip);
	bool isInUsersDB(std::string userId);
	bool authenticateUser(std::string userId, std::string password);
	void updateUserPortfolio(std::string id, Portfolio updatedPortfolio);

	//lookups
	double getSpotRate(double yearsToMaturity);
	const Bond getBondFromCatalog(std::string cusip);
	const Bond getBondFromZeroCurve(std::string cusip);
	const Portfolio getPortfolioForUser(std::string userId);

	void displayBondMap();

#endif
