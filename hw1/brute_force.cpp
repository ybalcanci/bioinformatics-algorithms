#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string readFile(std::ifstream& in);

int brute_force(string textFileName, string patternFileName){
	ifstream myTextFile(textFileName);
	string text = readFile(myTextFile);
	
	ifstream myPatternFile(patternFileName);
	string pattern = readFile(myPatternFile);
	
	cout << "text: " << text << endl;
	cout << "pattern: " <<  pattern << endl;
	
	cout << "text.size(): " << text.size() << endl;
	cout << "pattern.size(): " <<  pattern.size() << endl;
	
	int textLength = text.size();
	int patternLength = pattern.size();
	
	for(int i = 0; i < textLength - patternLength; i++){
		/*
		 text: compared string.
		 parameters of compare:
			i: Position of the first character in the compared string.
			patternLength: Length of compared string.
			pattern: comparing string.
		*/
		if(text.compare(i, patternLength, pattern) == 0){ 
			return i;
		}
	}
	
	return -1;
}

int main() {
	int res = brute_force("text.fa", "pattern.fa");
	cout << "Res: " << res << endl;
}