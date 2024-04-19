#include "SFX.hpp"

SFX::SFX(){
	munch = std::make_shared<Util::SFX>(RESOURCE_DIR"/sound/munch.wav");
}

void SFX::PlayMunch(){
	munch->Play();
}
