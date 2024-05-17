#include "Bonus.hpp"


void Bonus::SetImage(std::string imagePath){
//	std::shared_ptr<Util::Image> img = make_shared(RESOURCE_DIR+imagePath);
	this->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR+imagePath));
}

void Bonus::SetAppearTime(){
	appearTime = (float)(std::rand())/(float)(RAND_MAX) + 9; //n+9 ,n=0~1
}
