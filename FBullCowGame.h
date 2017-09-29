/* the game logic (no view code or direct user interaction
The game is a simple guess the word game that i am learning from
Ben Tristem on Udemy.*/


#pragma once
#include <string>
using int32 = int;
using FString = std::string;

//all values initialised to 0
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	Invalid_Status,
	Ok,
	Not_IsoGram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 
	
	void Reset(); //
	FBullCowCount SumbitValidGuess(FString); 
	
									  
private:
	// see constructor for initialisation.
	int32 MyCurrentTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};