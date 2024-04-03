#include "ShowText.hpp"
#include <string>

class Score : public ShowText {
public:
    Score(  const std::string& font, 
            int size, 
            const std::string& text,
            const Util::Color& color = Util::Color(127, 127, 127))
        : ShowText(font, size, text, color) {}

    void SetFoodScore(unsigned int score);
    void AddFoodScore(unsigned int delta);
    unsigned int GetFoodScore();

    void SetVisibleScore(unsigned int score);
    void AddVisibleScore(unsigned int delta);
    unsigned int GetVisibleScore();

    void ScoreUpdate();
private:
    unsigned int VisibleScore = 0;
    unsigned int FoodScore = 0;

};