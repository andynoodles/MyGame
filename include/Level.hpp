#ifndef LEVEL_HPP
#define LEVEL_HPP
#include<vector>

class Level{
public:
	Level();

	//Setter
    void SetLevel(unsigned int level);
    void AddLevel(unsigned int delta);

	//Getter
	unsigned int GetCurrentLevel();
	int GetFrightTime();
	float GetPacmanSpeedMul();
	float GetPacmanFrightSpeedMul();
	float GetGhostSpeedMul();
	float GetGhostFrightSpeedMul();
	float GetGhostTunnelSpeedMul();

private:
    unsigned int CurrentLevel;
	std::vector<int> frightTime;
	std::vector<float> pacmanSpeedMul ,pacmanFrightSpeedMul ,ghostSpeedMul ,ghostFrightSpeedMul,ghostTunnelSpeedMul;
};

#endif
