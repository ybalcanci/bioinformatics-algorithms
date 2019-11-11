#include <iostream>
#include <string>
#include <bits/stdc++.h> 
#include "unistd.h"
#include <getopt.h>

using namespace std;

vector<string> readFile(std::string fileName);
int smith_waterman(string sequence1Name, string sequence1, string sequence2Name, string sequence2,
					int gapopen, int gapext, int matchScore, int mismatchPenalty);
int needleman_wunsch(string sequence1Name, string sequence1, string sequence2Name, string sequence2,
					int gapopen, int gapext, int matchScore, int mismatchPenalty);

int main(int argc, char *argv[]) {
	int c;
	string mode;
	string fileName;
	int gapopen;
	int gapext;
	while (1) {
		static struct option long_options[] = {
			{"mode",     required_argument,       0, 'm'},
			{"input",  required_argument,       0, 'i'},
			{"gapopen",  required_argument, 0, 'o'},
			{"gapext",  required_argument, 0, 'e'},
			{0, 0, 0, 0}
		};
		/* getopt_long stores the option index here. */
		int option_index = 0;
	
		c = getopt_long (argc, argv, "m:i:o:e:",
						long_options, &option_index);
	
		/* Detect the end of the options. */
		if (c == -1)
		break;
	
		switch (c) {
        case 'm':
			mode = optarg;
			break;
	
        case 'i':
			fileName = optarg;
			break;
	
        case 'o':
			gapopen = atoi(optarg);
			break;
	
        case 'e':
			gapext = atoi(optarg);
			break;
        case '?':
			/* getopt_long already printed an error message. */
			return 1;
			break;

        default:
			abort ();
        }
    }
	
	vector<string> sequences = readFile(fileName);

	int matchScore = 2;
	int mismatchPenalty = -3;
	if(mode.compare("global") == 0){
		needleman_wunsch(sequences[0], sequences[1], sequences[2], sequences[3], 0, gapopen, matchScore, mismatchPenalty);
	} else if(mode.compare("aglobal") == 0){
		needleman_wunsch(sequences[0], sequences[1], sequences[2], sequences[3], gapopen, gapext, matchScore, mismatchPenalty);
	} else if(mode.compare("local") == 0){
		smith_waterman(sequences[0], sequences[1], sequences[2], sequences[3], 0, gapopen, matchScore, mismatchPenalty);
	} else if(mode.compare("alocal") == 0){
		smith_waterman(sequences[0], sequences[1], sequences[2], sequences[3], gapopen, gapext, matchScore, mismatchPenalty);
	}
	
	return 0;
}