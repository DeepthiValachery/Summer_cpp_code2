/*	
	Student Name	:	Deepthi Jibu Valahery
	Student ID		:	[redact]
	Course Code		:	COMP1602 (Summer)
	Course Name		:	Computer Programming II
	Assignment		:	2
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

struct str {
	string s;
};

int tries = 12;
string message = "You have 12 chances!";

int readWords (str data[]){
	ifstream in;     
	string w;                  
	
	in.open("words.txt");     
	
	if (!in.is_open()) {         
		cout << "File could not be opened. Aborting..." << endl;         
		return -1;
	}         
	
	int numWords = 0; 
	in >> w;  
	   
	while (w!="ENDDATA") {           
		data[numWords].s = w;      
		numWords++;          
		in >> w;     
	}   
	cout<<"Printing Words from InputFile Words.txt: \n";  
    for (int i=0;i<numWords;i++){
		for (int j=0;j<4;j++){
			cout << setw(20) << data[i].s;
			i++;
		}
		cout << "\n";
	}       
	in.close();    
	return numWords; 
}

bool binarySearch (str data[], int numWords, string key) {
    int low, high, mid;
     
	low = 0;
    high = numWords - 1;
     
    while (low <= high) {
        mid = (low + high) / 2;
        if (key == data[mid].s) 
            return mid;
        else
        if (key > data[mid].s)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return false;
}

int removeDuplicates (str data[], int n){
	if (n==0 || n==1){
		return n;
	}
	str temp[n];
	int j=0;
	
	for (int i=0;i<n-1;i++){
		if (data[i].s!=data[i+1].s){
			temp[j++] = data[i];
		}
	}
	temp[j++] = data[n-1];
	
	for (int i=0;i<j;i++)
        data[i] = temp[i];
 
    return j;	
}

int start(str data[], int numWords){
	string word;
	
	for(int i=0;i<numWords;i++){
		word = data[i].s;
		char* char_array = new char[word.length()+1]; 
		for (int x=0;x<word.length();x++){
			char_array[x] = word[x];
			if (char_array[x] >= 'A' && char_array[x] <= 'Z' ){
				char_array[x] = char_array[x] + 32;
			}
			word[x] = char_array[x];
		}
		data[i].s = word;
	}
	
    for (int i=0;i<numWords-1;i++) {
		int minLoc = i; 

		for (int j=i+1;j<=numWords-1;j++){
			if(data[j].s < data[minLoc].s) 	
				minLoc = j; 
		}
		str temp = data[i];
		data[i] = data[minLoc];
		data[minLoc] = temp; 
	}

	numWords = removeDuplicates(data, numWords);
	cout << "\n\nPrinting all distinct words: \n"; 
	for (int i=0;i<numWords;i++){
		for (int j=0;j<4;j++){
			cout << setw(20) << data[i].s;
			i++;
		}
		cout << "\n";
	}
return numWords;
}

void hangman(char c){
	string hang = "|";
	string stage = "=====";
	if (c == 'f'){
		hang = " ";
	}
	else if (c == 'h'){
		stage = "     ";
	}
	cout << "\t\t\t\t   "<< message << endl;
	cout << "\t\t\t\t___________________" << endl;
	cout << "\t\t\t\t        "<< hang<<"         |" << endl;
	cout << "\t\t\t\t        O         |" << endl;
	cout << "\t\t\t\t       /|\\        |" << endl;
	cout << "\t\t\t\t        |         |" << endl;
	cout << "\t\t\t\t       / \\        |" << endl;
	cout << "\t\t\t\t|====="<< stage <<"=======|" << endl;
	cout << "\t\t\t\t|                 |" << endl;
	cout << "\t\t\t\t|_________________|" << endl;
}

int checkGuess(char guess, string realWord, string &hide_word){ 
	int match = 0;
	int len = realWord.length();
	
	for (int i=0;i<len;i++){
		if (guess == hide_word[i]){
			return 0;
		}
		if(guess == realWord[i]){
			hide_word[i] = guess;
			match++;
		}
	}
	return match;
}

void playGame(){
	str data[100];
	int win = 0;
	int num = readWords(data);				//read words off file
	int numWords = start(data, num);		//sort in ascending order and remove duplicate words
	char letter, choice;
	string word;
	
	cout << "Do you want to play? (Y/N)";
	cin >> choice;
	system("cls");
	for(int i=0;i<numWords;i++){
		word = data[i].s;
		string hide_word(word.length(), '*');//hide words in ***
		if(choice=='Y'){		
			while (tries!=0){
				hangman('n');
				cout << "Lives left: " << tries << endl;
				cout << hide_word << endl;
				cout << "Guess a letter: ";
				cin >> letter;
				
				system("cls");
			
				if (checkGuess(letter, word, hide_word) == 0){
					message = "Incorrect!";
					tries--;
				} 
				else{
					message = "Nice Guess!";
				}
		
				if (hide_word == word){
					message = "You've Won!";
					hangman('f');
					cout << "Lives left: " << tries << endl;
					cout << "The word is: " << word << endl;
					win++;
					cout << "Games you have won: " << win << endl;
					break;
				}
			}
			if (tries==0){
				message = "You've Failed!";
				hangman('h');
				cout << "Lives left: " << tries << endl;
				cout << "The word is: " << word << endl;
				cout << "Games you have won: " << win;
				break;
			}
		}
		else if(choice=='N'){
			cout << "You have decided to quit. Thank you for playing!";
			break;
		}
	}
}

int main() {
	playGame();
	return 0;
}
