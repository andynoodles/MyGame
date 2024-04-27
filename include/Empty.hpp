#ifndef EMPTY_HPP
#define EMPTY_HPP

#include "Util/GameObject.hpp"

class Empty : public Util::GameObject {
public:
    Empty(const std::string imagePath) : GameObject(std::make_unique<Util::Image>(imagePath) ,100){
		m_Transform.scale = {2 ,2};
	}
	void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
	
private:
};

#endif 
