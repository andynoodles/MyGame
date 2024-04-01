#include "Score.hpp"

void Score::SetFoodScore(unsigned int score){
    FoodScore = score;
}
void Score::AddFoodScore(unsigned int delta){
    FoodScore += delta;
}

void Score::SetVisiableScore(unsigned int score){
    VisiableScore = score;
}

void Score::AddVisiableScore(unsigned int delta){
    VisiableScore += delta;
}