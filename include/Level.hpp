class Level{
public:
    void SetLevel(unsigned int level);
    void AddLevel(unsigned int delta);

private:
    unsigned int CurrentLevel;
};