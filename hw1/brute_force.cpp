#include <string>

int brute_force(std::string text, std::string pattern){
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