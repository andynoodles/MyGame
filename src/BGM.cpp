#include "BGM.hpp"

BGM::BGM(){
	bgm = std::make_shared<Util::BGM>(RESOURCE_DIR"/sound/ghost-normal-move.mp3");
	curBGM = BGMState::NORMAL;	
	lastBGM = BGMState::OTHER;
}

void BGM::PlayStart(){
	curBGM = BGMState::NORMAL;
	int loop = 1;
	if(curBGM != lastBGM){
		bgm->LoadMedia(RESOURCE_DIR"/sound/game_start.wav");
		bgm->Play(loop);
		lastBGM = curBGM;
	}

}

void BGM::PlayNormal(){
	curBGM = BGMState::NORMAL;
	if(curBGM != lastBGM){
		bgm->LoadMedia(RESOURCE_DIR"/sound/ghost-normal-move.mp3");
		bgm->Play();
		lastBGM = curBGM;
	}
} 

void BGM::PlayRetreat(){
	curBGM = BGMState::RETREAT;
	if(curBGM != lastBGM){
		bgm->LoadMedia(RESOURCE_DIR"/sound/retreating.wav");
		bgm->Play();
		lastBGM = curBGM;
	}
}

void BGM::PlayPower(){
	curBGM = BGMState::POWER;
	if(curBGM != lastBGM){
		bgm->LoadMedia(RESOURCE_DIR"/sound/power_pellet.wav");
		bgm->Play();
		lastBGM = curBGM;
	}

}

void BGM::PlayDeath(){
	curBGM = BGMState::DEATH;
	if(curBGM != lastBGM){
		bgm->LoadMedia(RESOURCE_DIR"/sound/death.wav");
		bgm->Play();
		lastBGM = curBGM;
	}

}
