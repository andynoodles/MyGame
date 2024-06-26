#ifndef BGM_HPP
#define BGM_HPP

#include "Util/BGM.hpp"
#include "config.hpp"

class BGM{
public:
	enum class BGMState{
		START, //Game start.
		NORMAL, //Ghost is chasing Pacman.
		RETREAT, //Ghost is going home.
		POWER, //Pacman is chasing ghost.
		OTHER
	};

	BGM();

	void PlayStart();
	void PlayNormal(unsigned int currentFoodScore);
	void PlayRetreat();
	void PlayPower();
	void Pause();
	void Resume();
	
	//Setter
	void SetLastBGM(BGMState st){lastBGM = st;}

	//Getter
	BGMState GetCurBGM(){return curBGM;} 
private:
	std::shared_ptr<Util::BGM> bgm; //Current BGM.
	BGMState curBGM ,lastBGM;
};

#endif
