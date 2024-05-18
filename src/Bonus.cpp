#include "Bonus.hpp"

Bonus::Bonus(const std::string imgPath) : GameObject(std::make_unique<Util::Image>(imgPath) ,100){
	m_Transform.scale = {2 ,2};
	m_Transform.translation={READY_TEXT_X ,READY_TEXT_Y};
}

glm::vec2 Bonus::GetPosition(){ 
	return m_Transform.translation; 
}

bool Bonus::GetVisibility(){
	return m_Visible; 
}

float Bonus::GetAppearTime(){
	return appearTime;
}

unsigned long Bonus::GetMarker(){
	return Marker;
}

void Bonus::SetImage(std::string imgPath){
	this->SetDrawable(std::make_shared<Util::Image>(imgPath));
}

void Bonus::SetAppearTime(){
	appearTime = ((float)(std::rand())/(float)(RAND_MAX) + 9) * 1000; //n+9 ,n=0~1
}

void Bonus::SetMarker(unsigned long time){
	Marker = time;
}
