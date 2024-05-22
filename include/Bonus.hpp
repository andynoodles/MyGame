#ifndef BONUS_HPP	
#define BONUS_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "config.hpp"
#include <string>
#include <cstdlib> //For random

class Bonus : public Util::GameObject {
public:
    Bonus(const std::string imgPath);  

	//Getter
	glm::vec2 GetPosition(); 
    bool GetVisibility();
	float GetAppearTime();
	unsigned long GetMarker();

	//Setter
	void SetImage(std::string imgPath);
	void SetAppearTime();
	void SetMarker(unsigned long time);
	
private:
	float appearTime; //How long Bonus symbol appears on screen(between 9~10 sec).	
	unsigned long Marker = 0;	
};

#endif 
