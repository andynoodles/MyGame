#include "RankSystem.hpp"
#include <string>

RankSystem::RankSystem(
            const std::string& file, 
            const std::string& font, 
            int size, 
            const std::string& text,
            const Util::Color& color)
            : Score(font, size, text, color), filename(file) {};

void RankSystem::readScores() {
    std::ifstream filein(filename);
    std::string name;
    int score;
    
    scores.clear();

    while (filein >> name >> score) {
        scores.push_back(ScoreEntity(name, score));
    }

    filein.close();
}

void RankSystem::addScore(const std::string& name, int score) {
    scores.push_back(ScoreEntity(name, score));
}

bool RankSystem::compareScores(const ScoreEntity& a, const ScoreEntity& b) {
    return a.score > b.score;
}

void RankSystem::saveScores() {
    std::sort(scores.begin(), scores.end(), [this](const ScoreEntity& a, const ScoreEntity& b) {
        return compareScores(a, b);
    });

    while (scores.size() > 10) {
        scores.pop_back();
    }

    int index = 1;

    std::ofstream fileout(filename);
    for (const auto& entry : scores) {
        fileout << std::to_string(index++) << " " << entry.score << std::endl;
    }

    fileout.close();
}

std::vector<ScoreEntity> RankSystem::getScore(){
    return scores;
}
