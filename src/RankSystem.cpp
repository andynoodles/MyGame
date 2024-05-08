#include "RankSystem.hpp"

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

    std::ofstream fileout(filename);
    int index = 1;
    for (const auto& entry : scores) {
        fileout << index << entry.name << "," << entry.score << std::endl;
        index++;
    }

    fileout.close();
}
