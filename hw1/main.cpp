#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string readFile(std::ifstream& in);
int brute_force(string textFileName, string patternFileName);
int knuth_morris_pratt(string textFileName, string patternFileName);

int main() {
	int bruteForceRes = brute_force("text.fa", "pattern.fa");
	cout << "bruteForceRes: " << bruteForceRes << endl;
	
	int KMPRes = knuth_morris_pratt("text.fa", "pattern.fa");
	cout << "KMPRes: " << KMPRes << endl;
}