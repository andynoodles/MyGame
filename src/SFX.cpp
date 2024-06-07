#include "SFX.hpp"

SFX::SFX(){
	munch = std::make_shared<Util::SFX>(RESOURCE_DIR"/sound/munch.wav");
	eatGhost = std::make_shared<Util::SFX>(RESOURCE_DIR"/sound/eat_ghost.wav");
	eatBonus = std::make_shared<Util::SFX>(RESOURCE_DIR"/sound/eat_fruit.wav");
	pacmanDeath = std::make_shared<Util::SFX>(RESOURCE_DIR"/sound/Death.mp3");
	extend = std::make_shared<Util::SFX>(RESOURCE_DIR"/sound/extend.wav");
}

void SFX::PlayMunch(){
	munch->Play();
}

void SFX::PlayEatGhost(){
	eatGhost->Play();
}

void SFX::PlayEatBonus(){
	eatBonus->Play();
}

void SFX::PlayPacmanDeath(){
	pacmanDeath->Play();
}

void SFX::PlayExtent(){
	extend->Play();
}
