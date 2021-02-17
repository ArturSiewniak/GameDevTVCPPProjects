// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString HiddenWordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(HiddenWordList, *HiddenWordListPath);

    Isograms = GetValidWords(HiddenWordList);

    SetupGame();
    
    PrintLine(TEXT("The number of possible words is %i"), HiddenWordList.Num());
    PrintLine(TEXT("The number of valid words is %i"), GetValidWords(HiddenWordList).Num());
    PrintLine(TEXT("The words in array are: "));
    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
       
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Welcome to Bull and Cows game!"));
    PrintLine(TEXT("Guess a %i letter isogram"), HiddenWord.Len());
    PrintLine(TEXT("You have %i chances"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess:"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("The HiddenWord was: %s"), *HiddenWord);
    PrintLine(TEXT("\nPress enter to continue..."));
}

void UBullCowCartridge::ProcessGuess(const FString& Input)
{
    PrintLine(TEXT("Your guess was: %s"), *Input);
    
    if (Input == HiddenWord) 
    {
        PrintLine(TEXT("gg"));
        EndGame();
        return;
    }

    if (Input.Len() != HiddenWord.Len())
    {
		PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
		PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining."), Lives);
		return;
    }

    if (!IsIsogram(Input))
    {
		PrintLine(TEXT("No repeating letters, guess again!"));
		return;
    }

	PrintLine(TEXT("Lost a life!"));
	--Lives;

	if (Lives <= 0)
	{
		ClearScreen();
		PrintLine(TEXT("You have no lives left!"));
		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
		EndGame();
		return;
	}

	FBullCowCount Score = GetBullCows(Input);

	PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

	PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Input) const
{
    for (int32 i = 0; i < Input.Len(); i++)
    {
        for (int32 j = 0; j < i; j++)
        {
            if (Input[i] == Input[j])
            {
                return false;
            }
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& HiddenWordList)
{
    TArray<FString> ValidWords;

    for (FString Word : HiddenWordList)
    {
        if (Word.Len() > 2 && Word.Len() < 5)
        {
            if (IsIsogram(Word))  
            {
                ValidWords.Emplace(Word);
            }
        }
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Input) const
{
    FBullCowCount Count;

    for (int32 i = 0; i < Input.Len(); ++i)
    {
        if (Input[i] == HiddenWord[i])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 j = 0; j < HiddenWord.Len(); j++)
        {
             if (Input[i] == HiddenWord[j])
                {
                    Count.Cows++;
                    break;
                }
         }
        
    }
    return Count;
}