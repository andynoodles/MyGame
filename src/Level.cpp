#include "Level.hpp"

Level::Level(){
	frightTime = {6 ,5};

	pacmanSpeedMul = {0.8 ,0.9};
	pacmanFrightSpeedMul = {0.9 ,0.95};

	ghostSpeedMul = {0.75 ,0.85};
	ghostFrightSpeedMul = {0.5 ,0.55};
	ghostTunnelSpeedMul = {0.4 ,0.45};
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
