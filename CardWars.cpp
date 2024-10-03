#include <iostream>
#include "Console.h"
#include "Input.h"
#include "WarGame.h"
#include "Tester.h"
#include "HighScore.h"

int main() {
    Tester cardWarsTest;
    Console::ResizeWindow(150, 30);

    int menuSelection = 0;
    std::vector<std::string> menuOptions{ "1. Show Cards", "2. Show High Scores", "3. Play Card Wars", "4. Exit" };
    std::string highScoreFile = "HighScores.csv";
    std::string cardsFile = "cards.csv";

    WarGame war(cardsFile);
    auto highScores = HighScore::LoadHighScores(highScoreFile); // Load high scores once

    do {
        Console::Clear();
        menuSelection = Input::GetMenuSelection(menuOptions);
        Console::Clear();

        switch (menuSelection) {
        case 1:
            WarGame::ShowCards(); // Call to display all cards
            break;
        case 2:
            for (const auto& hs : highScores) { // Display high scores
                std::cout << hs.GetName() << ": " << hs.GetScore() << std::endl;
            }
            break;
        case 3:
        {
            std::string playerName = Input::GetString("Enter your name: ");
            war.PlayGame(playerName, highScores, highScoreFile);
        }
        break;
        default:
            break;
        }

        Input::PressEnter(); // Wait for user input before continuing

    } while (menuSelection != menuOptions.size());

    return 0; // Ensure proper program termination
}
