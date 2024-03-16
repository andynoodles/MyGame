#ifndef BACKGROUND_IMAGE_HPP
#define BACKGROUND_IMAGE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class BackgroundImage : public Util::GameObject{

public:
    BackgroundImage() : GameObject(
            std::make_unique<Util::Image>(RESOURCE_DIR"/image/Background.png"), -10) {
                m_Transform.scale = {2,2};
    }

private:

};

#endif //BACKGROUND_IMAGE_HPP
