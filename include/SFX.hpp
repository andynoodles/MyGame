#ifndef SFX_HPP
#define SFX_HPP

#include "Util/SFX.hpp"
#include "config.hpp"

class SFX{
public:
	SFX();

	void PlayMunch();
	void PlayEatGhost();
	void PlayEatBonus();
	void PlayPacmanDeath();
	void PlayExtent(); // Pacman will get an extra life when he reace 10000 score.
private:
    std::shared_ptr<Util::SFX> munch;
    std::shared_ptr<Util::SFX> eatGhost;
    std::shared_ptr<Util::SFX> eatBonus;
    std::shared_ptr<Util::SFX> pacmanDeath;
	std::shared_ptr<Util::SFX> extend;
};

#endif 
