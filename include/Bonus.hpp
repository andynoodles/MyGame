#ifndef BONUS_HPP	
#define BONUS_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <string>
#include <cstdlib> //For random

class Bonus : public Util::GameObject {
public:
    Bonus(const std::string imagePath) : GameObject(std::make_unique<Util::Image>(imagePath) ,100){
		m_Transform.scale = {2 ,2};
	}

	//Setter
//	void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
	void SetImage(std::string);
	void SetAppearTime();
	
private:
	float appearTime; //How long Bonus symbol appears on screen(between 9~10 sec).	
};

#endif 
