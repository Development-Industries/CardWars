#include "WarGame.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Input.h"
#include <iostream>
#include "Player.h"
#include <Player.cpp>

std::vector<Card> WarGame::_cards;

WarGame::WarGame(std::string cardsFile) {
    LoadCards(cardsFile);
}

void WarGame::shuffle() {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (size_t i = 0; i < _cards.size(); i++) {
        int ndx1 = rand() % _cards.size();
        int ndx2 = rand() % _cards.size();
        std::swap(_cards[ndx1], _cards[ndx2]);
    }
}

void WarGame::LoadCards(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string face, suit;
            std::getline(ss, face, ',');
            std::getline(ss, suit);
            _cards.push_back(Card(face, suit));
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
}

void WarGame::ShowCards() {
    for (auto& card : _cards) {
        card.print(); // call print on each card object
    }
}

void WarGame::PlayGame(const std::string& playerName, std::vector<HighScore>& highScores, const std::string& highScoreFile) {

    // Create player instances
    Player player(playerName);
    Player npc("NPC");

    // Distribute cards to players
    bool addToPlayer = true;
    for (const auto& card : _cards) {
        if (addToPlayer)
            player.AddCard(card);
        else
            npc.AddCard(card);

        addToPlayer = !addToPlayer;
    }

    // Create unclaimed pile
    std::vector<Card> unclaimedPile;

    // Game loop
    while (!player.IsEmpty()) {
        // Draw cards from players
        Card playerCard = player.PopCard();
        Card npcCard = npc.PopCard();

        // Print cards
        std::cout << playerName << " card: " << playerCard.GetName() << std::endl;
        std::cout << "NPC card: " << npcCard.GetName() << std::endl;

        // Add cards to unclaimed pile
        unclaimedPile.push_back(playerCard);
        unclaimedPile.push_back(npcCard);

        // Compare cards
        int compareResult = playerCard.Compare(npcCard);

        if (compareResult == -1) { // NPC wins
            npc.AddCardsFromPile(unclaimedPile);
            unclaimedPile.clear();
            std::cout << "NPC wins." << std::endl;
        }
        else if (compareResult == 1) { // Player wins
            player.AddCardsFromPile(unclaimedPile);
            unclaimedPile.clear();
            std::cout << playerName << " wins." << std::endl;
        }
        else { // Tie
            std::cout << "It's a tie." << std::endl;
        }

        // Determine winner
        if (npc.GetScore() > player.GetScore()) {
            std::cout << "NPC won the round." << std::endl;
        }
        else if (npc.GetScore() == player.GetScore()) {
            std::cout << "It was a tie." << std::endl;
        }
        else {
            std::cout << playerName << " won the round." << std::endl;

            // Check for new high score
            if (player.GetScore() > highScores.back().GetScore()) {
                // Find index for new high score
                size_t index = 0;
                while (index < highScores.size() && player.GetScore() <= highScores[index].GetScore()) {
                    index++;
                }

                // Insert new high score
                highScores.insert(highScores.begin() + index, HighScore(player.GetName(), player.GetScore()));

                // Remove the smallest high score
                highScores.pop_back();

                // Save high scores
                HighScore::SaveHighScores(highScoreFile, highScores);

                // Display top 10 high scores
                HighScore::ShowHighScores(highScores);
            }
        }

        // Ask player if they want to play again
        int playAgain;
        do {
            std::cout << "Do you want to play again? (1 for yes, 2 for no): ";
            playAgain = Input::GetInteger("Choice:", 1, 2); // Provide the required argument
        } while (playAgain != 1 && playAgain != 2);

        if (playAgain == 1) {
            // Play again
            PlayGame(playerName, highScores, highScoreFile);
        }
        else {
            // End game
            std::cout << "Thanks for playing!" << std::endl;
        }
    }
}
