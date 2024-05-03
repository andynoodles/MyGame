#ifndef SFX_HPP
#define SFX_HPP

#include "Util/SFX.hpp"
#include "config.hpp"

class SFX{
public:
	SFX();

	void PlayMunch();
	void PlayEatGhost();
	void PlayPacmanDeath();
private:
    std::shared_ptr<Util::SFX> munch;
    std::shared_ptr<Util::SFX> eatGhost;
    std::shared_ptr<Util::SFX> pacmanDeath;
};

#endif 
