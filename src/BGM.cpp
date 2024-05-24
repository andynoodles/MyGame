#include "BGM.hpp"

BGM::BGM(){
	bgm = std::make_shared<Util::BGM>(RESOURCE_DIR"/sound/normal_1.mp3");
	curBGM = BGMState::NORMAL;	
	lastBGM = BGMState::OTHER;
}

void BGM::PlayStart(){
	curBGM = BGMState::START;
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
		bgm->LoadMedia(RESOURCE_DIR"/sound/normal_1.mp3");
		bgm->Play();
		lastBGM = curBGM;
	}
} 

void BGM::PlayNormal(){
	curBGM = BGMState::NORMAL;
	if(curBGM != lastBGM){
		bgm->LoadMedia(RESOURCE_DIR"/sound/normal_2.wav");
		bgm->Play();
		lastBGM = curBGM;
	}
} 

void BGM::PlayNormal(){
	curBGM = BGMState::NORMAL;
	if(curBGM != lastBGM){
		bgm->LoadMedia(RESOURCE_DIR"/sound/normal_3.wav");
		bgm->Play();
		lastBGM = curBGM;
	}
} 

void BGM::PlayNormal(){
	curBGM = BGMState::NORMAL;
	if(curBGM != lastBGM){
		bgm->LoadMedia(RESOURCE_DIR"/sound/normal_4.wav");
		bgm->Play();
		lastBGM = curBGM;
	}
} 

void BGM::PlayNormal(){
	curBGM = BGMState::NORMAL;
	if(curBGM != lastBGM){
		bgm->LoadMedia(RESOURCE_DIR"/sound/normal_5.wav");
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

void BGM::Pause(){
	bgm->Pause();	
}

void BGM::Resume(){
	bgm->Resume();	
}
