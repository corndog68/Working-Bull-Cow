/*
this is a console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all user interaction. 
For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax unreal friendly
using int32 = int;
using Ftext = std::string;

// function prototypes as outside a class

void printintro();
void PlayGame();
Ftext GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game

//the entry point for our application

int main ()
{
	bool bplayagain = false;
	do {
		printintro();
		PlayGame();
		bplayagain = AskToPlayAgain();
	}
		while (bplayagain);
	
	return 0; //exit application

}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries ();
	std::cout << "You have " << MaxTries << " tries\n\n";
	
	//loop asking for guesses while the game
	//is NOT won and there are still tries remaining

	while ( ! BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		Ftext Guess = GetValidGuess(); // TODO make loop checking valid.

	//submit valid guess to the game, and recieve counts
		FBullCowCount BullCowCount = BCGame.SumbitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << "   Cows = " << BullCowCount.Cows << "\n\n";
	}

	// TODO summarise game 
	PrintGameSummary();
	return;
}

	Ftext GetValidGuess() //loop continually until the user gives a valid guess.
{
		Ftext Guess = "";
		EGuessStatus Status = EGuessStatus::Invalid_Status;
		do {
			//get a guess from the player
			int32 CurrentTry = BCGame.GetCurrentTry();
			std::cout << "TRY: " << CurrentTry << " of " << BCGame.GetMaxTries();
			std::cout << "\nPlease enter your guess\n";
			std::getline(std::cin, Guess);

			//check and give feedback
			Status = BCGame.CheckGuessValidity(Guess);
			switch (Status){
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
				break;
			case EGuessStatus::Not_IsoGram:
				std::cout << "Please type a word with no repeating letters (Isogram)\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter your guess in lower case\n";
			default:
				// asume the guess is valid
				break;
			}
			std::cout << std::endl;
		} while (Status != EGuessStatus::Ok); // keep looping until we get no errors
		return Guess;
}

void printintro()
{
//introduce the game
	std::cout << "\n\nWelcome to Bulls and Cows! A fun word game.\n";
	std::cout << std::endl;
	std::cout << "           }___{              ^___^  " << std::endl;
	std::cout << "          ( o o )            ( o o )" << std::endl;
	std::cout << "  /--------\\   /              \\   /----------\\" << std::endl;
	std::cout << " / | BULL  |\\ /                \\ / |  COW   | \\" << std::endl;
	std::cout << "*  |-,-----| o                  o  |------,-|  * " << std::endl;
	std::cout << "   ^       ^                       ^        ^ " << std::endl;
	std::cout << "See if you can guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram im thinking of?\n\n";
	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word?  ( Yes / No )  \n";
	Ftext response = "";
	std::getline(std::cin, response);
	return (response[0] == 'y') || (response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}