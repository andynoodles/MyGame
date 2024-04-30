#include "Level.hpp"

Level::Level(){
	pacmanSpeedMul = {0.8 ,0.9};
	ghostSpeedMul = {0.75 ,0.85};
}

void Level::SetLevel(unsigned int level){
    CurrentLevel = level;
}

void Level::AddLevel(unsigned int delta){
    CurrentLevel += delta;
}

float Level::GetPacmanSpeedMul(){
	return pacmanSpeedMul[CurrentLevel];
}

float Level::GetGhostSpeedMul(){
	return ghostSpeedMul[CurrentLevel];
}
