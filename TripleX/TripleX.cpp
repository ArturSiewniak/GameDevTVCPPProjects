#include <iostream>
#include <ctime>

void PrintIntroduction()
{
    //Game start
    std::cout << "You approach a lone man with a long white beard, strange blue-goldish cloak and a long staff made from a birch wood.\n";
    std::cout << "He says that if you answer his riddles correctly, he will give you a precious gem.\n\n";
}

bool PlayGame(int Difficulty)
{
    const int NumberA = rand() % Difficulty + 1;
    const int NumberB = rand() % Difficulty + 1;
    const int NumberC = rand() % Difficulty + 1;

    const int GameSum = NumberA + NumberB + NumberC;
    const int GameMultiplication = NumberA * NumberB * NumberC;

    //Test
    std::cout << "On to the riddle number " << Difficulty << "\n\n";
    std::cout << "There are three numbers hidden within these two:\n";
    std::cout << "Sum of their power in this number: " << GameSum << '\n';
    std::cout << "Multiplication of their power in this number: " << GameMultiplication << "\n\n";
    std::cout << "What three numbers are these?: ";

    int PlayerGuessA, PlayerGuessB, PlayerGuessC;

    std::cin >> PlayerGuessA >> PlayerGuessB >> PlayerGuessC;

    int PlayerGuessSum = PlayerGuessA + PlayerGuessB + PlayerGuessC;
    int PlayerGuessMultiplication = PlayerGuessA * PlayerGuessB * PlayerGuessC;

    if (PlayerGuessSum == GameSum && PlayerGuessMultiplication == GameMultiplication)
    {
        std::cout << "\nWell done!\n\n";
        return true;
    }
    else
    {
        std::cout << "\n*White-bearded man sighs*\n\n";
        return false;
    }
}

int main() 
{
    srand(time(NULL));
    PrintIntroduction();

    int Difficulty = 1;
    const int MaxDifficulty = 5;
    while (Difficulty <= MaxDifficulty)
    {
        bool bLevelComplete = PlayGame(Difficulty);
        std::cin.clear();
        std::cin.ignore();

        if (bLevelComplete)
        {
            ++Difficulty;
        }
    }

    std::cout << "Very well! The gem is yours.";

    return 0;
}