#include <iostream>
#include <string>
#include <bits/stdc++.h> 
#include "unistd.h"

using namespace std;

vector<string> readFile(std::string fileName);
int smith_waterman(string sequence1Name, string sequence1, string sequence2Name, string sequence2,
					int gapopen, int gapext, int matchScore, int mismatchPenalty);
int needleman_wunsch(string sequence1Name, string sequence1, string sequence2Name, string sequence2,
					int gapopen, int gapext, int matchScore, int mismatchPenalty);

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "usage: ./out <textFileName patternFileName>\n"); 
		return -1; 
	}
	
	vector<string> sequences = readFile(argv[1]);
	
	int gapopen = -5;
	int gapext = -2;
	int matchScore = 2;
	int mismatchPenalty = -3;
		
	needleman_wunsch(sequences[0], sequences[1], sequences[2], sequences[3], gapopen, gapext, matchScore, mismatchPenalty);
	
	smith_waterman(sequences[0], sequences[1], sequences[2], sequences[3], gapopen, gapext, matchScore, mismatchPenalty);
}