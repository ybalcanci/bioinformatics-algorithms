#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 

//https://stackoverflow.com/questions/35251635/fasta-reader-written-in-c
std::vector<std::string> readFile(std::string fileName) {
    std::ifstream input(fileName);
	std::vector<std::string> sequences;
    if (!input.good()) {
        std::cerr << "Error opening: " << fileName << " . You have failed." << std::endl;
        return sequences;
    }
    std::string line, id, DNA_sequence;

    // Don't loop on good(), it doesn't allow for EOF!!
	int i = 0;	
    while (std::getline(input, line)) {

        // line may be empty so you *must* ignore blank lines
        // or you have a crash waiting to happen with line[0]
        if(line.empty())
            continue;

        if (line[0] == '>') {
            // output previous line before overwriting id
            // but ONLY if id actually contains something
            if(!id.empty()){
				std::string("ATCG").find(DNA_sequence.at(DNA_sequence.size() - 1)) == -1 ? sequences.push_back(DNA_sequence.substr(0, DNA_sequence.size() - 1)) : sequences.push_back(DNA_sequence);
			}
            id = line.substr(1);
			sequences.push_back(id.substr(0, id.size() - 1));
			DNA_sequence.clear();
        }
        else {//  if (line[0] != '>'){ // not needed because implicit
            DNA_sequence += line;
        }
    }

    // output final entry
    // but ONLY if id actually contains something
    if(!id.empty())
		std::string("ATCG").find(DNA_sequence.at(DNA_sequence.size() - 1)) == -1 ? sequences.push_back(DNA_sequence.substr(0, DNA_sequence.size() - 1)) : sequences.push_back(DNA_sequence);
	return sequences;
}