#include "Card.h"
#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <sstream>
#include <iomanip>

int Card::Compare(const Card& other) const
{
	if (_face > other._face) {
		     return 1;
		 } else if (_face < other._face) {
		    return -1;
		 } else {
		    return 0;
		 }
}

std::string Card::GetName() const
{
	return _face + " of " + _suit;
}

void Card::print()
{
	std::cout << std::setw(2) << _face;


#if defined(_WIN32) || defined(__MSDOS__)
	_setmode(_fileno(stdout), _O_U16TEXT);
#endif

	if(_suit=="Hearts")
		std::wcout << HEART;
	else if(_suit== "Diamonds")
		std::wcout << DIAMOND;
	else if (_suit == "Clubs")
		std::wcout << CLUB;
	else if (_suit == "Spades")
		std::wcout << SPADE;
	std::wcout.flush();


#if defined(_WIN32) || defined(__MSDOS__)
	_setmode(_fileno(stdout), _O_TEXT);
#endif
}


int Card::compare(Card& otherCard)
{
	int pValue = getCardValue(_face);
	int cValue = getCardValue(otherCard.GetFace());
	if (pValue > cValue)
		return 1;//player wins
	else if (pValue < cValue)
		return -1;//npc wins 

	return 0;
}

int Card::getCardValue(std::string face)
{
	int value;
	if (sizeof(face) == 3) //10 card
		value = 10;
	else
	{
		char first = face[0];
		if (first == 'A')
			value = 1;
		else if (first == 'J')
			value = 11;
		else if (first =='Q')
			value = 12;
		else if (first == 'K')
			value = 13;
		else
			value = std::stoi(face);
	}

	return value;
	//return (int)face;
}