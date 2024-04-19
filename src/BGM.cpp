#include "BGM.hpp"

BGM::BGM(){
	normal = std::make_shared<Util::BGM>(RESOURCE_DIR"/sound/ghost-normal-move.mp3");
}

void BGM::PlayNormal(){
	normal->Play();
} 

