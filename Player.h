#pragma once

#include <string>
#include <vector>
#include "Card.h"

class Player {
public:
    Player(const std::string& name);

    std::string GetName() const;
    void SetName(const std::string& name);

    int GetScore() const;
    void SetScore(int score);

    bool HasCards() const;
    void PushCard(const Card& card);
    Card PopCard();

    void AddCard(const Card& card);
    void AddCardsFromPile(const std::vector<Card>& cards);

    void WonCards(const std::vector<Card>& cards);

private:
    std::string _name;
    int _score;
    std::vector<Card> _pile;
    std::vector<Card> _won;
};


