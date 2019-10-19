#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string readFile(std::ifstream& in);
int brute_force(string textFileName, string patternFileName);
int knuth_morris_pratt(string textFileName, string patternFileName);
int rabin_karp(std::string text, std::string pattern);

int main() {
	
	ifstream myTextFile("text.fa");
	string text = readFile(myTextFile);
	
	ifstream myPatternFile("pattern.fa");
	string pattern = readFile(myPatternFile);
	
	int textLength = text.size();
	int patternLength = pattern.size();
	
	cout << "text: " << text << endl;
	cout << "pattern: " <<  pattern << endl;
	
	cout << "textLength: " << textLength << endl;
	cout << "patternLength: " <<  patternLength << endl;
	
	int bruteForceRes = brute_force(text, pattern);
	cout << "bruteForceRes: " << bruteForceRes << endl;
	
	int KMPRes = knuth_morris_pratt(text, pattern);
	cout << "KMPRes: " << KMPRes << endl;
	
	int rabinKarpRes = rabin_karp(text, pattern);
	cout << "rabinKarpRes: " << rabinKarpRes << endl;

}