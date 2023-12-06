/*
 * csviostream.h
 *
 *  Created on: Sep 26, 2023
 *      Author: sahil
 */

#ifndef CSVIOSTREAM_H_
#define CSVIOSTREAM_H_

#include <filesystem>
#include <unistd.h>
#include <unordered_map>
#include <string>
#include "Bond.h" 
#include "csv.hpp"
#include "Portfolio.h"
#include "prettyprintutils.h"
#include "User.h"

using namespace std;
using namespace csv;

    static unordered_map<string, Bond> zeroCurve;
    static unordered_map<string, Bond> bondsMap;
    static unordered_map<string, User> usersDB;


    void loadZeroCurve() {

		ostringstream oss;
		oss << "\nLoading Bonds Zero Curve CSV...";

		CSVReader reader("inputs/ZeroCurve.csv");
		for (CSVRow& row: reader) { //Iterate over each Bond entry

			//Extract 'Bond' Class data members
		    string cusip = row["cusip"].get<>();
		    double maturityYears = row["maturity"].get<double>();
		    double yield = row["yield"].get<double>();
		    string description = row["description"].get<>();

		    //Construct 'Bond' Object
            Bond bond(description, cusip, 100, 0, yield, maturityYears);

            //Insert into Bonds Map - <string cusip, Bond bond>
            zeroCurve.insert(make_pair(cusip, bond));
		}

		oss << to_string(zeroCurve.size()) + " Entries Loaded for Bonds Zero Curve.\n";
		printToConsole(oss.str());
	}

	double getSpotRate(double yearsToMaturity) {
		for (const auto& bond : zeroCurve) {
        	if (bond.second.getMaturityYears() == yearsToMaturity) {
        		return bond.second.getYield(); 
        	}
    	}
    	return 0;
	}


	void loadBondsData() {

		ostringstream oss;
		oss << "\nLoading Bonds Data CSV...";

		CSVReader reader("inputs/BondsCatalog.csv");
		for (CSVRow& row: reader) { //Iterate over each Bond entry

			//Extract 'Bond' Class data members
		    string cusip = row["cusip"].get<>();
		    double faceValue = row["faceValue"].get<double>();
		    double couponRate = row["couponRate"].get<double>();
		    double maturityYears = row["maturity"].get<double>();
		    double yield = row["yield"].get<double>();
		    string description = row["description"].get<>();

		    //Construct 'Bond' Object
            Bond bond(description, cusip, faceValue, couponRate, yield, maturityYears);

            //Insert into Bonds Map - <string cusip, Bond bond>
            bondsMap.insert(make_pair(cusip, bond));
		}

		oss << to_string(bondsMap.size()) + " Entries Loaded from Bonds Catalog.\n";
		printToConsole(oss.str());
	}

	bool isInBondsMap(string cusip) {
		if (bondsMap.find(cusip) != bondsMap.end()) {
			return true;
		} 
		return false;
	}

	bool isInZeroCurve(string cusip) {
	if (zeroCurve.find(cusip) != zeroCurve.end()) {
		return true;
	} 
	return false;
	}

	const Bond getBondFromCatalog(string cusip) {
		return bondsMap.at(cusip);
	}

	const Bond getBondFromZeroCurve(string cusip) {
		return zeroCurve.at(cusip);
	}

	void displayBondMap() {
		printToConsole("\n*Bonds Catalog*\nCusip:\t\tSecurity:\n");
		for (const auto& bond : zeroCurve) {
        	printToConsole(bond.first + "\t" + bond.second.toString());
    	}
		for (const auto& bond : bondsMap) {
        	printToConsole(bond.first + "\t" + bond.second.toString());
    	}
	}

	void loadUsers(){

		ostringstream oss;
		oss << "\nLoading Users Data CSV...";

		CSVReader reader("inputs/Users.csv");
		for (CSVRow& row: reader) { //Iterate over each User entry

			//Extract 'User' Class data members
		    string userId = row["userId"].get<>();
		    string pass = row["password"].get<>();

		    //Construct path to User portfolio data
		    string userPortfolioPath = "data/";
		    string ext = ".csv";
		    string filePath = userPortfolioPath + userId + ext;

		    //If portfolio file exists, open it and create a new User. Add all the bonds to the User object's portfolio.
		    if (filesystem::exists(filePath)) {

		    	User user(userId,pass);
		        CSVReader portfolioReader(filePath);

		        for (CSVRow& bondRow: portfolioReader) { //Iterate over each Bond entry
			        //Extract 'Bond' Class data members
				    string cusip = bondRow["cusip"].get<>();
				    double faceValue = bondRow["faceValue"].get<double>();
				    double couponRate = bondRow["couponRate"].get<double>();
				    double maturityYears = bondRow["maturity"].get<double>();
				    double yield = bondRow["yield"].get<double>();
				    string description = bondRow["description"].get<>();
				    double quantity = bondRow["quantity"].get<double>();

				    
			    	//Construct 'Bond' Object and add to portfolio
	            	Bond bond(description, cusip, faceValue, couponRate, yield, maturityYears);
	            	user.addBondToPortfolio(bond, quantity);
				    
				}

				//Insert into Users DB - <string userId, User user>
            	usersDB.insert(make_pair(userId, user)); 

		        
		    } else {
		        oss << "\nError loading user portfolio (" + userId + ") from filePath: " + filePath << endl;
		    }
            
		}

		oss << to_string(reader.n_rows()) + " Entries Loaded from Users DB.\n";
		printToConsole(oss.str());
	}

	bool isInUsersDB(string userId) {
		if (usersDB.find(userId) != usersDB.end()) {
			return true;
		} 
		return false;
	}

	bool authenticateUser(string userId, string password) {
		return usersDB.at(userId).getPassword() == password;
	}

	const Portfolio getPortfolioForUser(string userId) {
		return usersDB.at(userId).getPortfolio();
	}

	void updateUserPortfolio(string id, Portfolio updatedPortfolio) {


		// Open the file in read mode to read the header
		string filePath = "data/" + id + ".csv";
	    ifstream inputFile(filePath);

	    if (!inputFile.is_open()) {
	        cerr << "Error opening file!" << endl;
	    }

	    // Read the header from the file
	    string header;
	    getline(inputFile, header);

	    // Close the file
	    inputFile.close();

	    // Open the file in write mode to truncate and rewrite
	    ofstream outputFile(filePath, ios::trunc);

	    if (!outputFile.is_open()) {
	        cerr << "Error opening file!" << endl;
	    }

	    // Write the header back to the file
	    outputFile << header << endl;

	    vector<BondAsset> bonds = updatedPortfolio.getBonds();
		for (BondAsset &asset : bonds) {
			Bond thisBond = asset.getBond();

			outputFile << thisBond.getSymbol() << "," << thisBond.getFaceValue() << "," << thisBond.getCouponRate() << ","
						<< thisBond.getMaturityYears() << "," << thisBond.getYield() << ","
						<< "\"" << thisBond.getDescription() << "\"" << "," << asset.getQuantity() << endl;		    
		}

	    // Close the file
	    outputFile.close();

	    cout << "Portfolio successfully updated!" << endl;

	}


#endif
