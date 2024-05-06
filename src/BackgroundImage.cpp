#include "BackgroundImage.hpp"

BackgroundImage::BackgroundImage(const std::string imagePath) : GameObject(std::make_unique<Util::Image>(RESOURCE_DIR+imagePath), 0) { 
	m_Transform.scale = {2,2};
	m_Transform.translation = {0, 2};
}

int BackgroundImage::typeOfPixel(float pixelX ,float pixelY){
	int newX = pixelX+GetScaledSize().x/2 ,newY = GetScaledSize().y/2 - pixelY;
	return mapDesign[newY/PIXELPERTILE][newX/PIXELPERTILE];	
}

float BackgroundImage::GetUpperLeftX(){
	return -(GetScaledSize().x/2)+PIXELPERTILE/2;
}

float BackgroundImage::GetUpperLeftY(){
	return GetScaledSize().y/2-PIXELPERTILE/2;
}

unsigned int BackgroundImage::GetLayout(int x, int y){
	return mapDesign[x][y];
}

std::pair<int ,int> BackgroundImage::GetTileOfPosition(glm::vec2 position){
	int newX = position.x+GetScaledSize().x/2 ,newY = GetScaledSize().y/2 - position.y;
		
	return {newX/PIXELPERTILE ,newY/PIXELPERTILE};
}

glm::vec2 BackgroundImage::GetCenterPositionOfTile(int x ,int y){
	glm::vec2 center = {GetUpperLeftX() + PIXELPERTILE*x ,GetUpperLeftY() - PIXELPERTILE*y};	
	return center;
}
