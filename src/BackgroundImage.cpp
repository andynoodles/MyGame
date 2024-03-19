#include "BackgroundImage.hpp"

BackgroundImage::BackgroundImage(const std::string imagePath) : GameObject(std::make_unique<Util::Image>(RESOURCE_DIR+imagePath), -10) { 
	m_Transform.scale = {2,2};
}
