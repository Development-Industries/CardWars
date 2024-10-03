#include "Player.h"
#include <stdexcept>

Player::Player(const std::string& name) : _name(name), _score(0) {}

std::string Player::GetName() const {
    return _name;
}

void Player::SetName(const std::string& name) {
    _name = name;
}

int Player::GetScore() const {
    return _score;
}

void Player::SetScore(int score) {
    _score = score;
}

bool Player::HasCards() const {
    return !_pile.empty();
}

void Player::PushCard(const Card& card) {
    _pile.push_back(card);
}

Card Player::PopCard() {
    if (_pile.empty()) {
        throw std::out_of_range("No cards left in the pile.");
    }
    Card card = _pile.back();
    _pile.pop_back();
    return card;
}

void Player::AddCard(const Card& card) {
    _pile.push_back(card);
}

void Player::AddCardsFromPile(const std::vector<Card>& cards) {
    _pile.insert(_pile.end(), cards.begin(), cards.end());
}

void Player::WonCards(const std::vector<Card>& cards) {
    _won.insert(_won.end(), cards.begin(), cards.end());
    // Assuming the score is incremented by the number of cards won
    _score += cards.size();
}
