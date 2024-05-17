#ifndef RANK_SYSTEM_HPP
#define RANK_SYSTEM_HPP

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "Score.hpp"

struct ScoreEntity {
    std::string name;
    int score;
    
    ScoreEntity(const std::string _name, const int _score) : name(_name), score(_score){};
};

class RankSystem : public Score{
private:
    std::vector<ScoreEntity> scores;
    std::string filename;

    bool compareScores(const ScoreEntity& a, const ScoreEntity& b);

public:
    RankSystem(
            const std::string& file, 
            const std::string& font, 
            int size, 
            const std::string& text,
            const Util::Color& color);

    void readScores();
    void addScore(const std::string& name, int score);
    void saveScores();
    std::vector<ScoreEntity> getScore();
};

#endif // RANK_SYSTEM_HPP
