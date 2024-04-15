#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void yellowHelper(std::string in, std::string floating, int i, std::set<std::string>& masterList, int numBlanks);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		int numBlanks = 0;
		for(int i = 0; i < in.size(); i++) {
			if(in[i] == '-') numBlanks ++;
		}
		std::set<std::string> masterList = {};
		yellowHelper(in, floating, 0, masterList, numBlanks);
		std::set<std::string> returnList = {};
		for(std::set<std::string>::iterator i = masterList.begin(); i != masterList.end(); i++) {
			if(dict.find(*i) != dict.end()) {
				returnList.insert(*i);
			}
		}
		return returnList;
}

// Define any helper functions here

//sometimes gets stuck in loop, sometimes doesn't generate all the words
// for some reason won't plug floating into  spot in cases like -r- a or a-- e or --o-- rt
void yellowHelper(std::string in, std::string floating, int i, std::set<std::string>& masterList, int numBlanks) {
	if(i > in.size()) {
		if(floating.size() == 0) {
			masterList.insert(in);
		}
		return;
	}

	if(in[i] != '-') {
		yellowHelper(in, floating, i+1, masterList, numBlanks);
		return;
	}

	for(int j = 0; j < floating.size(); j++) {
		in[i] = floating[j];
		std::string floatingTemp = floating;
		floatingTemp.erase(j, 1);
		yellowHelper(in, floatingTemp, i+1, masterList, numBlanks - 1);
	}

	if(numBlanks > floating.size()) {
		for(int j = 0; j < 26; j++) {
			in[i] = 97+j;
			yellowHelper(in, floating, i+1, masterList, numBlanks - 1);
		}
	}

}