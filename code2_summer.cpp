/*	
	Student ID		:	[redacted]
	Name			:	Deepthi Jibu Valachery
	Course code		:	COMP1602 
	Course name		:	Computer Programming II
	Assignment		:	1
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Stalls{				//Structures to hold data
	string name;
	double income;
	double expense;
	double netIncome;
};

    Stalls stall [100];		//Global variables
	int numStalls;  

void viewReport(){			//function
	ifstream in;
    string name;
	double income, expense, tProfit = 0;

    in.open("stalls.txt");	//Input File checker
    if (!in.is_open()) {
       cout << "Stalls.txt could not be opened. Aborting program ..." << endl; 
       return exit(1);
    }
    in >> name;				//Read data
    numStalls = 0;

    while (name!="ENDDATA") { 					// Ends with ENDDATA
    	in >> income;
    	in >> expense;
    	stall[numStalls].name = name;			//Store data
    	stall[numStalls].netIncome = income - expense;
    	stall[numStalls].income = income;
    	stall[numStalls].expense = expense;
    	numStalls++;
    	in >> name;
    }
    in.close();
	 
    for (int i=0;i<numStalls-1;i++) {				//Using selection sort
		int minLoc = i; 

		for (int j=i+1;j<=numStalls-1;j++){
			if(stall[j].netIncome < stall[minLoc].netIncome) 	
				minLoc = j; 
		}
		Stalls temp = stall[i];
		stall[i] = stall[minLoc];
		stall[minLoc] = temp; 
	}
	
    cout << "\tREPORT" << endl << endl;
    cout << "Stall Name\tNet Income" << endl;			//Print in order of increasing net income
    cout << "=================================" << endl;
    for(int i=0;i<numStalls;i++){  
        cout << stall[i].name << "\t\t" << stall[i].netIncome <<endl;
		tProfit += stall[i].netIncome;
    }  
    
    cout << "\n=================================" << endl;
	cout << "\nNumber of Stalls: " << numStalls << endl;	//no. of stalls
	cout << "\nStall that made the most profit: " << stall[numStalls-1].name << endl;		//most profitted stall
	
	if (tProfit>0){			//profit or loss of BAZAAR
		cout << "\nThe total profit of the bazaar: " << tProfit << endl;
	}else if (tProfit<0){
		cout << "\nThe total loss of the bazaar: " << tProfit << endl;
	}
	
	cout << "\nThe stall(s) that made profit: " ;			//stall(s) that made profit
	for (int i=0;i<numStalls+1;i++){
		if (stall[i].netIncome > 0){
			cout << stall[i].name << ", ";
		}
	}
}

int main() {				//main
	viewReport();
return 0;
}
