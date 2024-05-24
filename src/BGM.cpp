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

void BGM::PlayNormal(unsigned int currentFoodScore){
	curBGM = BGMState::NORMAL;
	int n = currentFoodScore / NORMAL_BGM_CHANGE_SCORE_THRESHOLD;
	if(curBGM != lastBGM){
		if(n < 1)
			bgm->LoadMedia(RESOURCE_DIR"/sound/normal_1.wav");
		else if(n < 2)
			bgm->LoadMedia(RESOURCE_DIR"/sound/normal_2.wav");
		else if(n < 3)
			bgm->LoadMedia(RESOURCE_DIR"/sound/normal_3.wav");		
		else if(n < 4)
			bgm->LoadMedia(RESOURCE_DIR"/sound/normal_4.wav");		
		else
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
