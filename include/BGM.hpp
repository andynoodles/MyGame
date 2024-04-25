#ifndef BGM_HPP
#define BGM_HPP

#include "Util/BGM.hpp"
#include "config.hpp"

class BGM{
public:
	enum class BGMState{
		NORMAL,
		RETREAT,
		OTHER
	};

	BGM();

	void PlayNormal();
	void PlayRetreat();

	BGMState GetCurBGM(){return curBGM;} 
private:
	std::shared_ptr<Util::BGM> bgm; //Current BGM.
	BGMState curBGM ,lastBGM;
};

#endif
