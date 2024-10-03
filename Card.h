#pragma once
#include <string>

#if defined(_WIN32) || defined(__MSDOS__)
#define SPADE   '\x06'
#define CLUB    '\x05'
#define HEART   '\x03'
#define DIAMOND '\x04'
#else
#define SPADE   '\u2660'
#define CLUB    '\u2663'
#define HEART   '\u2665'
#define DIAMOND '\u2666'
#endif
//enum Suit
//{
//	Hearts=1,
//	Diamonds,
//	Clubs,
//	Spades
//};
//enum Face
//{
//	Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King
//};
class Card
{
public:
	Card(std::string suit, std::string face)
	{
		_suit = suit;
		_face = face;
	}
	int Compare(const Card& other) const;
	std::string GetName() const;
	std::string GetSuit() const { return _suit; }
	void SetSuit(std::string suit) { _suit = suit; }

	std::string GetFace() const { return _face; }
	void SetFace(std::string face) { _face = face; }

	void print();
	int compare(Card& otherCard);

private:
	std::string _suit;
	std::string _face;

	int getCardValue(std::string face);
};

