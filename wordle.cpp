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

void findAnswers(set<string> &possibleAnswers, string &currentGuess, size_t &guessLetters, string& guaranteedLetters, 
                  size_t idx, const set<string>& dictionary);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    string currentGuess = in; // Dashes for undetermnined "places" (eg. t--al {total})
    string guaranteedLetters = floating; // unordered string of letters that are in the answer 100%
    set<string> possibleAnswers; // container to store possible answers to return 
    size_t guessLetters = 0; // number of "places" or letters to guess
    size_t idx = 0;

    for (size_t i = 0; i < currentGuess.size(); i++)
    {
        char temp = currentGuess[i];

        if (temp == '-')
        {
            guessLetters++;
        }
    }

    findAnswers(possibleAnswers, currentGuess, guessLetters, guaranteedLetters, idx, dict);
    
    return possibleAnswers;
    
}

// Define any helper functions here

void findAnswers(set<string> &possibleAnswers, string &currentGuess, unsigned int &guessLetters, string& guaranteedLetters,
                  unsigned int idx, const set<string>& dictionary)
                  
{

    if(idx == currentGuess.size()) // we have recursively visited all "places" in the guess word
    {
        if(dict.find(currentGuess) != dict.end()) // word is in dictionary
        {
            possibleAnswers.insert(currentGuess);
        }

        return;
    }
    else if(currentGuess[idx] != '-') // it must be the correct letter (green), so move onto next "place"
    {
        findAnswers(possibleAnswers, currentGuess, guessLetters, guaranteedLetters, idx++, dict);
        return;
    }
    else if(guessLetters <= guaranteedLetters.size() /*&& guaranteedLetters.size() != 0*/)
    {
        for (size_t i = 0; i < guaranteedLetters.size(); i++)
        {
            string tempSave = guaranteedLetters;
            currentGuess[idx] = i;
            size_t temp = guaranteedLetters.find(i);
            guaranteedLetters.erase(temp, 1);
            findAnswers(possibleAnswers, currentGuess, guessLetters--, guaranteedLetters, idx++, dict);
            guaranteedLetters = tempSave;
        }
        currentGuess[idx] = '-';
    }
    else
    {
        for (char alpha = 'a'; alpha <= 'z'; alpha++)
        {
            currentGuess[idx] = alpha;

            if(guaranteedLetters.find(alpha) == guaranteedLetters.npos) // this letter is not guaranteed
            {
                findAnswers(possibleAnswers, currentGuess, guessLetters--, guaranteedLetters, idx++, dict);
            }
            else if(guaranteedLetters.find(alpha) != guaranteedLetters.npos)
            {
                string tempSave = guaranteedLetters;
                size_t temp = guaranteedLetters.find(alpha);
                guaranteedLetters.erase(temp, 1);
                findAnswers(possibleAnswers, currentGuess, guessLetters--, guaranteedLetters, idx++, dict);
                guaranteedLetters = tempSave;
            }
        }

        currentGuess[idx] = '-';
    }

    return;

}
