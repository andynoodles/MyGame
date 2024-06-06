#ifndef LEVEL_HPP
#define LEVEL_HPP
#include<vector>
#include<string>
#include<cassert>
#include "config.hpp"

class Level{
public:
	Level();

	//Setter
    void SetLevel(unsigned int level);
    void AddLevel(unsigned int delta);

	//Getter
	unsigned int GetCurrentLevel();
	int GetFrightTime();
	int GetBounsScore();
	float GetPacmanSpeedMul();
	float GetPacmanFrightSpeedMul();
	float GetGhostSpeedMul();
	float GetGhostFrightSpeedMul();
	float GetGhostTunnelSpeedMul();
	std::string GetBonusImgPath();
	std::string GetBonusImgPath(unsigned int index);

private:
    unsigned int CurrentLevel;
	std::vector<int> frightTime ,bonusScore;
	std::vector<float> pacmanSpeedMul ,pacmanFrightSpeedMul ,ghostSpeedMul ,ghostFrightSpeedMul,ghostTunnelSpeedMul;
	std::vector<std::string> bonusImgPath;
};

#endif
