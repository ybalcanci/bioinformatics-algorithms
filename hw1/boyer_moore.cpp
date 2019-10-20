#include <string>
#include <iostream>

int badChar(const std::string pattern, const int failureIndex, const char failedChar){
	int i = failureIndex;
	while(i >= 0){
		if(pattern.at(i) == failedChar)
			return failureIndex - i;
		i--;
	}
	return failureIndex + 1;
}

int boyer_moore(std::string text, std::string pattern){
	int textLength = text.size();
	int patternLength = pattern.size();
	int numOfCharComparisons = 0;
	int i = 0, j = 0; // i -> text || j -> pattern
	while(i < textLength - patternLength + 1){
		j = 0;
		for(int k = patternLength - 1; k >= 0; k--){
			numOfCharComparisons++;
			if(pattern.at(k) != text.at(i + k)){
				i += badChar(pattern, k, text.at(i + k));
				break;
			}
			if(k == 0){
				std::cout << "Boyer-Moore # of char comparions: " << numOfCharComparisons << std::endl;
				return i;
			}
				
		}
	}	
	std::cout << "Boyer-Moore # of char comparions: " << numOfCharComparisons << std::endl;
	return -1;
}