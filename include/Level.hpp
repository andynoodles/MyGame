#include<vector>

class Level{
public:
	Level();
    void SetLevel(unsigned int level);
    void AddLevel(unsigned int delta);

	//Getter
	float GetPacmanSpeedMul();
	float GetGhostSpeedMul();

private:
    unsigned int CurrentLevel;
	std::vector<float> pacmanSpeedMul ,ghostSpeedMul;
};
