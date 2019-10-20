#include <string>
#include <iostream>

int rabin_karp(std::string text, std::string pattern){
	int numOfCharComparisons = 0;
	int base = 5;
	int q = 7;
	int hash[100];
	hash['A'] = 0;
	hash['C'] = 1;
	hash['G'] = 2;
	hash['T'] = 3;
	int ft = 0, fp = 0;
	int c = 1;
	
	int textLength = text.size();
	int patternLength = pattern.size();
	for(int i = 0; i < patternLength; i++){
		fp = (base * fp + hash[pattern.at(i)]) % q;
		ft = (base * ft + hash[text.at(i)]) % q;
		c = c % q * base;
	}
	c /= base;
	c %= q;
	for(int i = 0; i < textLength - patternLength + 1; i++){
		if(fp == ft){
			for(int j = 0; j < patternLength; j++){
				numOfCharComparisons++;
				if(text.at(i + j) != pattern.at(j))
					break;
				if(j == patternLength - 1){
					std::cout << "rabin_karp numOfCharComparisons: " << numOfCharComparisons << std::endl;
					return i;
				}
			}
		}
		ft = ((ft - hash[text.at(i)] * c) * base + hash[text.at(i + patternLength)]) % q;
	}
	std::cout << "rabin_karp numOfCharComparisons: " << numOfCharComparisons << std::endl;
	return -1;
}