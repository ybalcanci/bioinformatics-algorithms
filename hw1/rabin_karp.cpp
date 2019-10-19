#include <string>

int rabin_karp(std::string text, std::string pattern){
	int q = 7;
	int hash[100];
	hash['A'] = 0;
	hash['C'] = 1;
	hash['G'] = 2;
	hash['T'] = 3;
	int ft = 0, fp = 0;
	
	int textLength = text.size();
	int patternLength = pattern.size();
	for(int i = 0; i < patternLength; i++){
		fp = (5 * fp + hash[pattern.at(i)]) % q;
		ft = (5 * ft + hash[text.at(i)]) % q;
	}
	for(int i = 0; i < textLength - patternLength; i++){
		if(fp == ft && text.compare(i, patternLength, pattern) == 0){
				return i;
		}
		ft = ((ft - hash[text.at(i)] * 5) * 5 + hash[text.at(i + patternLength)]) % q;
	}
	return -1;
}