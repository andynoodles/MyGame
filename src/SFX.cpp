#include "SFX.hpp"

SFX::SFX(){
	munch = std::make_shared<Util::SFX>(RESOURCE_DIR"/sound/munch.wav");
	eatGhost= std::make_shared<Util::SFX>(RESOURCE_DIR"/sound/eat_ghost.wav");
}

void SFX::PlayMunch(){
	munch->Play();
}

void SFX::PlayEatGhost(){
	eatGhost->Play();
}
