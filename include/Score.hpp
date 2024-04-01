class Score{
public:
    void SetFoodScore(unsigned int score);
    void AddFoodScore(unsigned int delta);

    void SetVisiableScore(unsigned int score);
    void AddVisiableScore(unsigned int delta);

private:
    unsigned int VisiableScore = 0;
    unsigned int FoodScore = 0;

};