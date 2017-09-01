#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

// function prototypes
void printIntro();
void playGame();
void printGameSummary();
bool askToPlayAgain();

// global variables
FBullCowGame BCGame;

// main
int main() {
	do {
		printIntro();
		playGame();
		printGameSummary();
		BCGame.reset();
	} while (askToPlayAgain());
	system("pause");
	return 0;
}

// function definitions
void printIntro() {
	std::cout << "          }   {        <___> " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / |BULLS |O    AND     O| COWS | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you try and guess the " << BCGame.getHiddenWordLength() << " letter isogram word I'm thinking of?\n";
	return;
}

void playGame() {
	FText guess = "";
	while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= BCGame.getMaxTries()) {
		// get valid guess
		guess = BCGame.getValidGuess();
		std::cout << "Your guess was: " << guess << std::endl;
		// submit valid guess to the game
		FBullCowCount bullCowCount = BCGame.submitValidGuess(guess);
		// print number of bulls and cows
		std::cout << "Bulls: " << bullCowCount.bulls << ", Cows: " << bullCowCount.cows << std::endl;
	}
}

void printGameSummary() {
	if (BCGame.isGameWon()) {
		std::cout << "\nCongratulations, you won the game!" << std::endl;
	}
	else
	{
		std::cout << "\nGame over! You've run out of tries." << std::endl;
	}
}

bool askToPlayAgain() {
	std::cout << "Do you want to play again? (y/n): ";
	FText response = "";
	std::getline(std::cin, response);
	std::cout << std::endl;
	return (response[0] == 'y' || response[0] == 'Y');
}



