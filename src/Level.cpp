#include "Level.hpp"

Level::Level(){
	frightTime.resize(TOTAL_LEVEL);
	bonusScore.resize(TOTAL_LEVEL);
	pacmanSpeedMul.resize(TOTAL_LEVEL);
	pacmanFrightSpeedMul.resize(TOTAL_LEVEL);
	ghostSpeedMul.resize(TOTAL_LEVEL);
	ghostFrightSpeedMul.resize(TOTAL_LEVEL);
	ghostTunnelSpeedMul.resize(TOTAL_LEVEL);
	bonusImgPath.resize(TOTAL_LEVEL);

	frightTime = {6 ,5 ,4 ,5 ,2 ,5 ,3 ,3 ,5 ,3};
	bonusScore = {100 ,300 ,500 ,700 ,1000 ,2000 ,3000 ,5000 ,5000 ,5000};

	pacmanSpeedMul = {0.8 ,0.9 ,0.9 ,1 ,1 ,1 ,1 ,1 ,1 ,1};
	pacmanFrightSpeedMul = {0.9 ,0.95 ,0.95 ,1 ,1 ,1 ,1 ,1 ,1 ,1};

	ghostSpeedMul = {0.75 ,0.85 ,0.85 ,0.95 ,0.95 ,0.95 ,0.95 ,0.95 ,0.95 ,0.95};
	ghostFrightSpeedMul = {0.5 ,0.55 ,0.55 ,0.6 ,0.6 ,0.6 ,0.6 ,0.6 ,0.6 ,0.6};
	ghostTunnelSpeedMul = {0.4 ,0.45 ,0.5 ,0.5 ,0.5 ,0.5 ,0.5 ,0.5 ,0.5 ,0.5};

	bonusImgPath = {
		RESOURCE_DIR"/image/Bonus/Cherries.png",
		RESOURCE_DIR"/image/Bonus/Strawberry.png",
		RESOURCE_DIR"/image/Bonus/Peach.png",
		RESOURCE_DIR"/image/Bonus/Apple.png",
		RESOURCE_DIR"/image/Bonus/Grapes.png",
		RESOURCE_DIR"/image/Bonus/Galaxian.png",
		RESOURCE_DIR"/image/Bonus/Bell.png",
		RESOURCE_DIR"/image/Bonus/Key.png",
		RESOURCE_DIR"/image/Bonus/Key.png",
		RESOURCE_DIR"/image/Bonus/Key.png"
	};
}

void Level::SetLevel(unsigned int level){
	assert(level < TOTAL_LEVEL); //check if out of range	
    CurrentLevel = level;
}

void Level::AddLevel(unsigned int delta){
    CurrentLevel += delta;
}

unsigned int Level::GetCurrentLevel(){
	return CurrentLevel;
}

int Level::GetFrightTime(){
	return frightTime[CurrentLevel]*1000;
}

int Level::GetBounsScore(){
	return bonusScore[CurrentLevel];
}

float Level::GetPacmanSpeedMul(){
	return pacmanSpeedMul[CurrentLevel];
}

float Level::GetPacmanFrightSpeedMul(){
	return pacmanFrightSpeedMul[CurrentLevel];
}

float Level::GetGhostSpeedMul(){
	return ghostSpeedMul[CurrentLevel];
}

float Level::GetGhostFrightSpeedMul(){
	return ghostFrightSpeedMul[CurrentLevel];
}

float Level::GetGhostTunnelSpeedMul(){
	return ghostTunnelSpeedMul[CurrentLevel];
}

std::string Level::GetBonusImgPath(){
	return bonusImgPath[CurrentLevel];
}

std::string Level::GetBonusImgPath(unsigned int index){
	assert(index < TOTAL_LEVEL);
	return bonusImgPath[index];
}
