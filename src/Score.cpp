#include "Score.hpp"

void Score::SetFoodScore(unsigned int score){
    FoodScore = score;
}
void Score::AddFoodScore(unsigned int delta){
    FoodScore += delta;
}

void Score::SetVisibleScore(unsigned int score){
    VisibleScore = score;
}

void Score::AddVisibleScore(unsigned int delta){
    VisibleScore += delta;
}
unsigned int Score::GetFoodScore(){
    return this->FoodScore;
}

unsigned int Score::GetVisibleScore(){
    return this->VisibleScore;
}

void Score::ScoreUpdate(){
    SetText(std::to_string(this->VisibleScore));
}
bool Score::IsFoodAllEaten(){
	return (FoodScore == FULL_FOOD_SCORE) ? true :false;
}
