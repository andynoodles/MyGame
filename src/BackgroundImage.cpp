#include<cassert>

#include "BackgroundImage.hpp"
#include "Util/Logger.hpp"

BackgroundImage::BackgroundImage(const std::string imagePath) : GameObject(std::make_unique<Util::Image>(RESOURCE_DIR+imagePath), -10) { 
	m_Transform.scale = {2,2};

	assert(GetScaledSize().x/NumberOfTilesX == GetScaledSize().y/NumberOfTilesY);
	pixelPerTile = GetScaledSize().x/NumberOfTilesX;
}

int BackgroundImage::typeOfPixel(float pixelX ,float pixelY){
	int newX = pixelX+GetScaledSize().x/2 ,newY = GetScaledSize().y/2 - pixelY;
	return mapDesign[newY/pixelPerTile][newX/pixelPerTile];	
}
