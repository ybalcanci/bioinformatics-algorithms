#include <string>
#include <iostream>

int brute_force(std::string text, std::string pattern){
	int textLength = text.size();
	int patternLength = pattern.size();
	int numOfCharComparisons = 0;
	for(int i = 0; i < textLength - patternLength; i++){
		/*
		 text: compared string.
		 parameters of compare:
			i: Position of the first character in the compared string.
			patternLength: Length of compared string.
			pattern: comparing string.
		*/
		for(int j = 0; j < patternLength; j++){
			numOfCharComparisons++;
			if(text.at(i + j) != pattern.at(j))
				break;
			if(j == patternLength - 1){
				std::cout << "brute_force numOfCharComparisons: " << numOfCharComparisons << std::endl;
				return i;
			}
		}
	}
	std::cout << "brute_force numOfCharComparisons: " << numOfCharComparisons << std::endl;
	return -1;
}