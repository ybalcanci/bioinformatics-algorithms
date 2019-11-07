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
	
	ifstream file1(argv[1]);	
	ifstream file2(argv[2]);
	
	string text, pattern, text1 = readFile(file1), text2 = readFile(file2);
	text = text1.at(1) == 't' ? text1.substr(6) : text2.substr(6);
	pattern = text2.at(1) == 'p' ? text2.substr(9) : text1.substr(9);
	
	int textLength = text.size();
	int patternLength = pattern.size();
		
	auto start = high_resolution_clock::now();
	int bruteForceRes = brute_force(text, pattern);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Brute force execution time: " << duration.count() << endl;
	cout << "Brute force found pattern in index: " << bruteForceRes << endl;
	cout << endl;
	
	start = high_resolution_clock::now();
	int KMPRes = knuth_morris_pratt(text, pattern);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Knuth-Morris-Pratt execution time: " << duration.count() << endl;
	cout << "Knuth-Morris-Pratt found pattern in index: " << KMPRes << endl;
	cout << endl;
	
	start = high_resolution_clock::now();
	int BoyerMooreRes = boyer_moore(text, pattern);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Boyer-Moore execution time: " << duration.count() << endl;
	cout << "Boyer-Moore found pattern in index " << BoyerMooreRes << endl;
	cout << endl;
	
	start = high_resolution_clock::now();
	int rabinKarpRes = rabin_karp(text, pattern);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Rabin-Karp execution time: " << duration.count() << endl;
	cout << "Rabin-Karp found pattern in index: " << rabinKarpRes << endl;
}