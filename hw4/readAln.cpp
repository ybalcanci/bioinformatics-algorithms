#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 

std::vector<std::string> readAln(std::string fileName) {
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

        if(line.empty())
            continue;
		int blankIndex = line.find(" ");
		sequences.push_back(line.substr(0, blankIndex));
		if(std::string("ATCG").find(line.at(line.size() - 1)) == -1)
			sequences.push_back(line.substr(blankIndex + 1, line.length() - blankIndex - 2));
		else
			sequences.push_back(line.substr(blankIndex + 1));

    }

	return sequences;
}