#ifndef SFX_HPP
#define SFX_HPP

#include "Util/SFX.hpp"
#include "config.hpp"

class SFX{
public:
	SFX();

	void PlayMunch();
private:
    std::shared_ptr<Util::SFX> munch;
};

#endif 
