#include <iostream>
#include <string>

using namespace std;
int writeToFile(string sequence1Name, string sequence1, string sequence2Name, string sequence2, int score, string fileName);

int smith_waterman(string sequence1Name, string sequence1, string sequence2Name, string sequence2,
					int gapopen, int gapext, int matchScore, int mismatchPenalty) {

	int text1Length = sequence1.size();
	int text2Length = sequence2.size();

	int table[text1Length + 1][text2Length + 1]; // table of scores
	char directionTable[text1Length + 1][text2Length + 1]; // table of directions
	
	table[0][0] = 0;
	
	// Fill in the 0th columns
	for(int i = 1; i < text1Length + 1; i++){
		table[i][0] = 0;
		directionTable[i][0] = 'u';
	}

	// Fill in the 0th rows
	for(int j = 1; j < text2Length + 1; j++){
		table[0][j] = 0;
		directionTable[0][j] = 'l';
	}
	
	int iMaxValue = 0;
	int jMaxValue = 0;
	int maxValue = 0;

	// Fill in the tables
	for(int i = 1; i < text1Length + 1; i++){
		for(int j = 1; j < text2Length + 1; j++){
			
			int diagonalExtra = sequence1.at(i - 1) == sequence2.at(j - 1) ? matchScore : mismatchPenalty;
			int leftExtra = directionTable[i][j-1] == 'l' ? (gapext) : (gapext + gapopen);
			int upExtra = directionTable[i-1][j] == 'u' ? (gapext) : (gapext + gapopen);

			if(0 >= table[i-1][j-1] + diagonalExtra && 0 >= table[i][j-1] + leftExtra && 0 >= table[i-1][j] + upExtra){
				table[i][j] = 0;
				directionTable[i][j] = '0';
			}
			else if(table[i-1][j-1] + diagonalExtra >= table[i][j-1] + leftExtra && table[i-1][j-1] + diagonalExtra >= table[i-1][j] + upExtra){
				table[i][j] = table[i-1][j-1] + diagonalExtra;
				directionTable[i][j] = 'd';
			} else if(table[i][j-1] + leftExtra >= table[i-1][j-1] + diagonalExtra && table[i][j-1] + leftExtra >= table[i-1][j] + upExtra){
				table[i][j] = table[i][j-1] + leftExtra;
				directionTable[i][j] = 'l';
			} else{
				table[i][j] = table[i-1][j] + upExtra;
				directionTable[i][j] = 'u';
			}


			if(table[i][j] > maxValue){
				iMaxValue = i;
				jMaxValue = j;
				maxValue = table[i][j];
			}
		}
	}
	
	// Backtracking
	string matchedSequence1;
	string matchedSequence2;
	int i = iMaxValue, j = jMaxValue;

	while(table[i][j] != 0){
		if(directionTable[i][j] == 'd'){
			matchedSequence1.insert (0, 1, sequence1.at(i - 1));
			matchedSequence2.insert (0, 1, sequence2.at(j - 1));
			i--; j--;
		} else if(directionTable[i][j] == 'l'){
			matchedSequence1.insert (0, 1, '-');
			matchedSequence2.insert (0, 1, sequence2.at(j - 1));
			j--;
		} else if(directionTable[i][j] == 'u'){
			matchedSequence1.insert (0, 1, sequence1.at(i - 1));
			matchedSequence2.insert (0, 1, '-');
			i--;
		} else{
			cout << "Error while backtracking." << endl;
			return -1;
		}
	}
	
	/*
	// Print tables to console
	for(int i = 0; i < text1Length + 1; i++){
		for(int j = 0; j < text2Length + 1; j++)
			printf("%*c",4,directionTable[i][j]);
		printf("\n");
	}
	printf("\n");
	for(int i = 0; i < text1Length + 1; i++){
		for(int j = 0; j < text2Length + 1; j++)
			printf("%*d",4,table[i][j]);
		printf("\n");
	}
	*/

	// Print results to file
	if(gapopen == 0)
		writeToFile(sequence1Name, matchedSequence1, sequence2Name, matchedSequence2, maxValue, "local-naiveGap.aln");
	else
		writeToFile(sequence1Name, matchedSequence1, sequence2Name, matchedSequence2, maxValue, "local-affineGap.aln");
	
	return 0;
}