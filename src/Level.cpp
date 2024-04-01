#include "Level.hpp"

void Level::SetLevel(unsigned int level){
    CurrentLevel = level;
}
void Level::AddLevel(unsigned int delta){
    CurrentLevel += delta;
}