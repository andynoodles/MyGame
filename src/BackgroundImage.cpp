#include<cassert>

#include "BackgroundImage.hpp"
#include "Util/Logger.hpp"

BackgroundImage::BackgroundImage(const std::string imagePath) : GameObject(std::make_unique<Util::Image>(RESOURCE_DIR+imagePath), -10) { 
	m_Transform.scale = {2,2};
	m_Transform.translation = {0, 2};
}

int BackgroundImage::typeOfPixel(float pixelX ,float pixelY){
	int newX = pixelX+GetScaledSize().x/2 ,newY = GetScaledSize().y/2 - pixelY;
	return mapDesign[newY/GetPixelPerTile()][newX/GetPixelPerTile()];	
}

int BackgroundImage::GetPixelPerTile(){
	assert(GetScaledSize().x/GetNumberOfTilesX()== GetScaledSize().y/GetNumberOfTilesY());
	return GetScaledSize().x/GetNumberOfTilesX();
}

float BackgroundImage::GetUpperLeftX(){
	return -(GetScaledSize().x/2)+GetPixelPerTile()/2;
}

float BackgroundImage::GetUpperLeftY(){
	return GetScaledSize().y/2-GetPixelPerTile()/2;

}
const int BackgroundImage::GetNumberOfTilesX(){
	return NumberOfTilesX;
}

const int BackgroundImage::GetNumberOfTilesY(){
	return NumberOfTilesY;
}

unsigned int BackgroundImage::GetLayout(int x, int y){
	return mapDesign[x][y];
}
