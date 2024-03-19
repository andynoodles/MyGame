#include "App.hpp"

#include "AnimatedCharacter.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Animation.hpp"


#include<iostream>

#include "BackgroundImage.hpp"

#include<iostream>

void App::Start() {
    LOG_TRACE("Start");
    backgroundImage = std::make_shared<BackgroundImage>();
    
    std::vector<std::string> pacmanImage;
    pacmanImage.reserve(3);
    for (int i = 0; i < 3; ++i) {
        pacmanImage.emplace_back(RESOURCE_DIR"/image/Pac/Sprite (" + std::to_string(i + 1) + ").png");
    }

    m_Pacman = std::make_shared<AnimatedCharacter>(pacmanImage);
    m_Pacman->SetZIndex(5);
    m_Pacman->SetVisible(true);
    m_Pacman->SetLooping(true);
    m_Pacman->SetPlaying(true);
    
    m_Root.AddChild(m_Pacman);  
	  m_Root.AddChild(backgroundImage);
	  m_Root.Update();

    m_CurrentState = State::UPDATE;
}

void App::Update() {



	m_Root.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
