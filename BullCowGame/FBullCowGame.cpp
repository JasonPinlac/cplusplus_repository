#pragma once
#include "FBullCowGame.h"

using FString = std::string;
using int32 = int;

// getters
int32 FBullCowGame::getCurrentTry() const { return myCurrentTry; }
int32 FBullCowGame::getHiddenWordLength() const { return myhiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bGameIsWon; }

// constructors
FBullCowGame::FBullCowGame() {
	reset();
}

// methods	
void FBullCowGame::reset() {
	myhiddenWord = "planet";
	myMaxTries = getMaxTries();
	myCurrentTry = 1;
	bGameIsWon = false;
}

int32 FBullCowGame::getMaxTries() const { 
	std::map<int32, int32> wordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20}, {8,25}, {9,30}, {10,40} };
	return wordLengthToMaxTries[myhiddenWord.length()];
}

std::string FBullCowGame::getValidGuess() {
	FString guess = "";
	EGuessStatus status = EGuessStatus::invalid;
	do {
		std::cout << "\nTry " << myCurrentTry << " out of " << myMaxTries << ". ";
		std::cout << "Enter your guess: ";
		std::getline(std::cin, guess);

		// validity check
		status = checkGuessValidity(guess);

		switch (status) {
		case EGuessStatus::not_isogram:
			std::cout << "You're guess is not an isogram. An isogram word contains no duplicate letters. Try again." << std::endl;
			break;
		case EGuessStatus::wrong_length:
			std::cout << "You're guess is not the correct word length. Try again using a word that has a length of " << getHiddenWordLength() << " characters." << std::endl;
			break;
		case EGuessStatus::not_all_lower_case:
			std::cout << "You're guess is not all lower case. Try again using a word with all lower case letters." << std::endl;
			break;
		default:
			//std::cout << "You're guess is valid." << std::endl;
			break;
		}
	} while (status != EGuessStatus::ok);
	return guess;
}

FBullCowCount FBullCowGame::submitValidGuess(const FString &guess) {
	myCurrentTry++;
	FBullCowCount bullCowCount;
	// loop through all letters in the hidden word
	// compare letters of guess against the hidden word letters
	// if they match then increment bulls if they are in the same place and increment cows if they are not in the same place
	for (int32 i = 0; i < myhiddenWord.length(); i++) {
		for (int32 j = 0; j < guess.length(); j++) {
			if (myhiddenWord[i] == guess[j]) {
				if (i == j) {
					bullCowCount.bulls++;
				}
				else {
					bullCowCount.cows++;
				}
			}
		}
	}
	if (bullCowCount.bulls == myhiddenWord.length()) {
		bGameIsWon = true;
	}
	return bullCowCount;
}

// helper methods
EGuessStatus FBullCowGame::checkGuessValidity(const FString &guess) const {
	if (!isIsogramCheck(guess)) {
		return EGuessStatus::not_isogram;
	}
	else if (!isWordLengthCheck(guess)) {
		return EGuessStatus::wrong_length;
	}
	else if (!isLowerCaseCheck(guess)) {
		return EGuessStatus::not_all_lower_case;
	}
	else {
		return EGuessStatus::ok;
	}
}

bool FBullCowGame::isWordLengthCheck(const FString &guess) const {
	return (guess.length() == myhiddenWord.length());
}

bool FBullCowGame::isIsogramCheck(const FString &guess) const {
	// treat 0 or 1 letter words as isograms
	if (guess.length() <= 1) {
		return true;
	}
	// use a map as you iterate to see if there is a duplicate letter in the guess
	std::map<char, bool> letterSeen;
	for (auto letter : guess) {
		letter = tolower(letter);
		if (letterSeen[letter]) {
			return false;
		}
		else {
			letterSeen[letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::isLowerCaseCheck(const FString &guess) const {
	// iterate through each letter of the string guess. Check each letter if its lower case. if any letter is not lower case, return false. if all letters are lower case return true.
	for (auto letter : guess) {
		if (!islower(letter)) {
			return false;
		}
	}
	return true;
}
