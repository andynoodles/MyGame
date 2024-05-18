#include "Level.hpp"

Level::Level(){
	frightTime = {6 ,5};
	bonusScore = {100 ,300 ,500 ,700 ,1000 ,2000 ,3000 ,5000};

	pacmanSpeedMul = {0.8 ,0.9};
	pacmanFrightSpeedMul = {0.9 ,0.95};

	ghostSpeedMul = {0.75 ,0.85};
	ghostFrightSpeedMul = {0.5 ,0.55};
	ghostTunnelSpeedMul = {0.4 ,0.45};

	bonusImgPath = {
		RESOURCE_DIR"/image/Bonus/Cherries.png",
		RESOURCE_DIR"/image/Bonus/Strawberry.png",
		RESOURCE_DIR"/image/Bonus/Peach.png",
		RESOURCE_DIR"/image/Bonus/Apple.png",
		RESOURCE_DIR"/image/Bonus/Grapes.png",
		RESOURCE_DIR"/image/Bonus/Galaxian.png",
		RESOURCE_DIR"/image/Bonus/Bell.png",
		RESOURCE_DIR"/image/Bonus/Key.png"
	};
}

void Level::SetLevel(unsigned int level){
    CurrentLevel = level;
}

void Level::AddLevel(unsigned int delta){
    CurrentLevel += delta;
}

unsigned int Level::GetCurrentLevel(){
	return CurrentLevel;
}

int Level::GetFrightTime(){
	return frightTime[CurrentLevel];
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
