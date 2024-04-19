#ifndef BGM_HPP
#define BGM_HPP

#include "Util/BGM.hpp"
#include "config.hpp"

class BGM{
public:
	BGM();

	void PlayNormal();
private:
    std::shared_ptr<Util::BGM> normal;
};

#endif
