#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

string readFile(std::ifstream& in);
int brute_force(string textFileName, string patternFileName);
int knuth_morris_pratt(string textFileName, string patternFileName);
int boyer_moore(std::string text, std::string pattern);
int rabin_karp(std::string text, std::string pattern);

int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "usage: ./out <textFileName patternFileName>\n"); 
		return -1; 
	}
	
	ifstream myTextFile(argv[1]);
	string text = readFile(myTextFile);
	
	ifstream myPatternFile(argv[2]);
	string pattern = readFile(myPatternFile);
	
	int textLength = text.size();
	int patternLength = pattern.size();
	
	cout << "text: " << text << endl;
	cout << "pattern: " <<  pattern << endl;
	
	cout << "textLength: " << textLength << endl;
	cout << "patternLength: " <<  patternLength << endl;
	
	auto start = high_resolution_clock::now();
	int bruteForceRes = brute_force(text, pattern);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Brute force execution time: " << duration.count() << endl;
	cout << "bruteForceRes: " << bruteForceRes << endl;
	
	start = high_resolution_clock::now();
	int KMPRes = knuth_morris_pratt(text, pattern);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Knuth-Morris-Pratt execution time: " << duration.count() << endl;
	cout << "KMPRes: " << KMPRes << endl;
	
	start = high_resolution_clock::now();
	int BoyerMooreRes = boyer_moore(text, pattern);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Boyer-Moore execution time: " << duration.count() << endl;
	cout << "BoyerMooreRes: " << BoyerMooreRes << endl;
	
	start = high_resolution_clock::now();
	int rabinKarpRes = rabin_karp(text, pattern);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Rabin-Karp execution time: " << duration.count() << endl;
	cout << "rabinKarpRes: " << rabinKarpRes << endl;

}