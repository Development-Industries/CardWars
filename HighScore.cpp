#include <fstream>
#include <sstream>
#include "HighScore.h"
#include <iostream>


void HighScore::Serialize(std::ofstream& outFile, char delimiter) const
{
   outFile << _name << delimiter << _score << std::endl;
}

void HighScore::SaveHighScores(const std::string& filePath, const std::vector<HighScore>& highScores) {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    char delimiter = ','; // Set your desired delimiter
    for (const auto& hs : highScores) {
        hs.Serialize(outFile, delimiter);
    }

    outFile.close();
}

void HighScore::ShowHighScores(const std::vector<HighScore>& highScores)
{
    std::cout << "High Scores\n" << std::endl;
    for (const auto& hs : highScores) {
        std::cout << "\x1B[32m" << hs.GetName() << "\x1B[0m" << "    " << "\x1B[31m" << hs.GetScore() << "\x1B[0m" << std::endl;
    }
}

HighScore::HighScore(const std::string& name, int score) : _name(name), _score(score) {}

std::string HighScore::GetName() const {
    return _name;
}

void HighScore::SetName(const std::string& name) {
    _name = name;
}

int HighScore::GetScore() const {
    return _score;
}

void HighScore::SetScore(int score) {
    _score = score;
}

HighScore::HighScore(const std::string& csvData, char delimiter) {
    Deserialize(csvData, delimiter);
}

void HighScore::Deserialize(const std::string& csvData, char delimiter) {
    std::stringstream ss(csvData);
    std::getline(ss, _name, delimiter);
    std::string scoreStr;
    std::getline(ss, scoreStr);

    // Manually convert scoreStr to an integer instead of using Stoi
    _score = 0;
    for (char c : scoreStr) {
        if (c < '0' || c > '9') {
            std::cerr << "Invalid score value: contains non-digit characters.\n";
            _score = 0; // Reset score to 0 or some default value on error
            return;
        }
        _score = _score * 10 + (c - '0');
    }
}

std::vector<HighScore> HighScore::LoadHighScores(const std::string& filePath) {
    std::vector<HighScore> highScores;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << '\n';
        return highScores; // Early return if file can't be opened
    }
    std::string line;
    while (std::getline(file, line)) {
        HighScore highScore(line, ','); // Assuming ',' as delimiter
        highScores.push_back(highScore);
    }
    return highScores;
}


