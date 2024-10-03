#pragma once
#include <string>
#include <vector>

class HighScore {
public:
    void Serialize(std::ofstream& outFile, char delimiter) const;

    static void SaveHighScores(const std::string& filePath, const std::vector<HighScore>& highScores);

    static void ShowHighScores(const std::vector<HighScore>& highScores);

    HighScore(const std::string& name, int score); // Constructor declaration

    std::string GetName() const; // Getter for the name field
    void SetName(const std::string& name); // Setter for the name field

    int GetScore() const; // Getter for the score field
    void SetScore(int score); // Setter for the score field

    HighScore(const std::string& csvData, char delimiter); // Constructor that deserializes from CSV data

    void Deserialize(const std::string& csvData, char delimiter); // Deserialize method

    static std::vector<HighScore> LoadHighScores(const std::string& filePath); // Load high scores from a file

private:
    std::string _name;
    int _score;
};

