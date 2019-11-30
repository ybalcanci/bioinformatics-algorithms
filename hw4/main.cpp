#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "unistd.h"
#include <getopt.h>

using namespace std;

vector<string> readFasta(string fileName);
vector<string> readAln(string fileName);
vector<string> msa(vector<string> sequences, string mainSequence, int gap, int match, int mismatch);
void writeToFile(vector<string> sequences, string fileName);

int main(int argc, char *argv[])
{

	int c;
	string fastaFileName;
	string alnFileName;
	string outFileName;

	int gap;
	int match;
	int mismatch;

	while (1)
	{
		static struct option long_options[] = {
			{"fasta", required_argument, 0, 'f'},
			{"aln", required_argument, 0, 'a'},
			{"out", required_argument, 0, 'o'},
			{"gap", required_argument, 0, 'g'},
			{"match", required_argument, 0, 'm'},
			{"mismatch", required_argument, 0, 'w'},
			{0, 0, 0, 0}};
		// getopt_long stores the option index here.
		int option_index = 0;

		c = getopt_long(argc, argv, "m:i:o:e:",
						long_options, &option_index);

		// Detect the end of the options.
		if (c == -1)
			break;

		switch (c)
		{
		case 'f':
			fastaFileName = optarg;
			break;

		case 'a':
			alnFileName = optarg;
			break;

		case 'o':
			outFileName = optarg;
			break;

		case 'g':
			gap = atoi(optarg);
			break;

		case 'm':
			match = atoi(optarg);
			break;

		case 'w':
			mismatch = atoi(optarg);
			break;

		case '?':
			// getopt_long already printed an error message.
			return 1;
			break;

		default:
			abort();
		}
	}

	string mainSequence = readFasta(fastaFileName)[1];
	vector<string> sequencesWithNames = readAln(alnFileName);
	vector<string> sequences;
	for (int i = 0; i < sequencesWithNames.size(); i++)
		if (i % 2 == 1)
			sequences.push_back(sequencesWithNames[i]);

	vector<string> newSequences = msa(sequences, mainSequence, gap, match, mismatch);

	// Print results to file
	writeToFile(newSequences, outFileName);

	return 0;
}