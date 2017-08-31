#pragma once
#pragma once
#include <string>
#include <iostream>
#include <map>

using FString = std::string;
using int32 = int;

// structure for bull cow count
struct FBullCowCount {
	int32 bulls = 0;
	int32 cows = 0;
};

// enum validity checklist
enum class EGuessStatus {
	ok, // 0
	not_isogram, // 1
	wrong_length, // 2
	not_all_lower_case, // 3
	invalid //4
};

class FBullCowGame {
public:
	// constructor
	FBullCowGame();
	// getters
	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	int32 getHiddenWordLength() const;
	bool isGameWon() const;
	// methods
	void reset();
	std::string getValidGuess();
	FBullCowCount submitValidGuess(const FString &guess);
private:
	// member variables
	int32 myCurrentTry;
	int32 myMaxTries;
	FString myhiddenWord;
	bool bGameIsWon;
	// validation helper methods
	EGuessStatus checkGuessValidity(const FString &guess) const;
	bool isIsogramCheck(const FString &guess) const;
	bool isLowerCaseCheck(const FString &guess) const;
	bool isWordLengthCheck(const FString &guess) const;
};