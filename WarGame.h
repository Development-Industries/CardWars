#pragma once
#include <string>
#include <vector>
#include "Card.h"
#include "HighScore.h"

class WarGame
{
public:
    void PlayGame(const std::string& playerName, std::vector<HighScore>& highScores, const std::string& highScoreFile);

    WarGame(std::string cardsFile); // Constructor declaration

    static void LoadCards(const std::string& filePath);

    static void ShowCards(); // Declaration of ShowCards method

private:
    static std::vector<Card> _cards; // Static member to store cards

    static void shuffle(); // Static method to shuffle cards
};
