#ifndef SCORE_HPP
#define SCORE_HPP

#include "ShowText.hpp"
#include <string>
#include "config.hpp"

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
	bool IsFoodAllEaten();
    
    unsigned int GetScoreMultiplier(){ return ScoreMultiplier; };
    void IncreaseScoreMultiplier(int i){ ScoreMultiplier += i; };
    void ResetScoreMultiplier(){ ScoreMultiplier = 1; };

    void SetMarker(unsigned long time){ Marker = time; };
    unsigned long GetMarker(){ return Marker; };
private:
    unsigned int VisibleScore = 0;
    unsigned int FoodScore = 0; //This is invisible.
    unsigned int ScoreMultiplier = 1;

    unsigned long Marker = 0;

};

#endif