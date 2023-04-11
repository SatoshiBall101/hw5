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

void findAnswers(set<string> &possibleAnswers, string &currentGuess, map<char, int>& letterCount, string& guaranteedLetters, 
                  size_t idx, const set<string>& dict, size_t numBlanks);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    string currentGuess = in; // Dashes for undetermnined "places" (eg. t--al {total})
    string guaranteedLetters = floating; // unordered string of letters that are in the answer 100%
    set<string> possibleAnswers; // container to store possible answers to return 
    map<char, int> letterCount; // a map to store each guaranteed letter and how many copies are guaranteed
    size_t idx = 0;
		size_t numBlanks = 0;

		for (size_t i = 0; i < currentGuess.size(); i++)
    {
        if (currentGuess[i] == '-')
				{
					numBlanks++;
				} 
    }

    for (size_t i = 0; i < guaranteedLetters.size(); i++)
    {
        char temp = guaranteedLetters[i];
        letterCount[temp]++; 
  
    }

    findAnswers(possibleAnswers, currentGuess, letterCount, guaranteedLetters, idx, dict, numBlanks);
    
    return possibleAnswers;
    
}

// Define any helper functions here

void findAnswers(set<string>& possibleAnswers, string& currentGuess, map<char, int>& letterCount, string& guaranteedLetters, size_t idx, const set<string>& dict, size_t numBlanks) 
{

		if (idx == currentGuess.size()) // base case
		{
        if (dict.count(currentGuess) == 1) // letter combination is an actual word
				{

					// Check that the count of each guaranteed letter in the guess matches the count in the guaranteedLetters string
					bool containsAllGL = true;
					for (size_t i = 0; i < guaranteedLetters.size(); i++)
					{
						if (letterCount[guaranteedLetters[i]] > count(currentGuess.begin(), currentGuess.end(), guaranteedLetters[i]))
						{
							containsAllGL = false;
							break;
						}
					}

					if (containsAllGL)
					{
						possibleAnswers.insert(currentGuess);
					} 
        }
        return;
    }


    char fixedChar = currentGuess[idx];

    if (fixedChar == '-') 
		{

			if(numBlanks == guaranteedLetters.size()) // only need to guess from GL
			{
				for (size_t i = 0; i < guaranteedLetters.size(); i++) 
				{
            string newGuess = currentGuess;
            newGuess[idx] = guaranteedLetters[i];

            findAnswers(possibleAnswers, newGuess, letterCount, guaranteedLetters, idx + 1, dict, numBlanks);   
      	}

			}
			else
			{
				for (char c = 'a'; c <= 'z'; c++) 
				{
          string newGuess = currentGuess;
          newGuess[idx] = c;

          findAnswers(possibleAnswers, newGuess, letterCount, guaranteedLetters, idx + 1, dict, numBlanks);   
      	}
			}  
    } 
		else 
		{ // if fixedChar is not '-' it is a green letter so move on
        findAnswers(possibleAnswers, currentGuess, letterCount, guaranteedLetters, idx + 1, dict, numBlanks);
    }
}

