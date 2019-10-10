#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string readFile(ifstream& in);

int* failureFunction(string pattern){
	int m = pattern.size();
	int* F = new int[m];
	int i = 1, j = 0;
	while(i < m){
		if(pattern.at(i) == pattern.at(j)){
			F[i] = j + 1;
			i++;
			j++;
		}
		else if(j > 0){
			j = F[j - 1];
		}
		else{
			F[i] = 0;
			i++;
		}
	}
	return F;
}

int knuth_morris_pratt(string textFileName, string patternFileName){
	ifstream myTextFile(textFileName);
	string text = readFile(myTextFile);
	
	ifstream myPatternFile(patternFileName);
	string pattern = readFile(myPatternFile);
		
	int textLength = text.size();
	int patternLength = pattern.size();
	
	int* F = failureFunction(pattern);
	int i = 0, j = 0;
	while(i < textLength){
		if(text.at(i) == pattern.at(j)){
			if(j == patternLength - 1){
				return i - j;
			}
			else{
				i++;
				j++;
			}
		}
		else{
			if(j > 0){
				j = F[j - 1];
			}
			else{
				i++;
				j = 0;
			}
		}
	}
	
	return -1;
}