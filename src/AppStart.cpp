#include "App.hpp"

void App::Start() {
    LOG_TRACE("Start");
    backgroundImage = std::make_shared<BackgroundImage>("/image/Background.png");
    
    std::vector<std::string> pacmanImage, cyanImage, orangeImage, pinkImage, redImage;
    pacmanImage.reserve(3);
    cyanImage.reserve(9);
    orangeImage.reserve(9);
    pinkImage.reserve(9);
    redImage.reserve(9);
    for (int i = 0; i < 3; ++i) {
        pacmanImage.emplace_back(RESOURCE_DIR"/image/Pac/Sprite (" + std::to_string(i + 1) + ").png");
    }

    for (int i = 0; i < 9; i++) {
        cyanImage.emplace_back(RESOURCE_DIR"/image/Cyan/Sprite (" + std::to_string(i + 85) + ").png");
        orangeImage.emplace_back(RESOURCE_DIR"/image/Orange/Sprite (" + std::to_string(i + 99) + ").png");
        pinkImage.emplace_back(RESOURCE_DIR"/image/Pink/Sprite (" + std::to_string(i + 71) + ").png");
        redImage.emplace_back(RESOURCE_DIR"/image/Red/Sprite (" + std::to_string(i + 57) + ").png");
    }



    m_Pacman = std::make_shared<Pacman>(pacmanImage);
    m_Pacman->SetZIndex(59);
    m_Pacman->SetVisible(true);
    m_Pacman->SetLooping(true);
    m_Pacman->SetPlaying(true);
    m_Pacman->FaceEast();

    m_Cyan = std::make_shared<Ghost>(cyanImage);
    m_Cyan->SetZIndex(51);
    m_Cyan->SetVisible(true);
    m_Cyan->SetLooping(true);
    m_Cyan->SetPlaying(true);
    m_Cyan->SetPosition({0, 0});

    m_Orange = std::make_shared<Ghost>(orangeImage);
    m_Orange->SetZIndex(52);
    m_Orange->SetVisible(true);
    m_Orange->SetLooping(true);
    m_Orange->SetPlaying(true);
    m_Orange->SetPosition({0, 30});

    m_Pink = std::make_shared<Ghost>(pinkImage);
    m_Pink->SetZIndex(53);
    m_Pink->SetVisible(true);
    m_Pink->SetLooping(true);
    m_Pink->SetPlaying(true);
    m_Pink->SetPosition({0, 60});

    m_Red = std::make_shared<Ghost>(redImage);
    m_Red->SetZIndex(54);
    m_Red->SetVisible(true);
    m_Red->SetLooping(true);
    m_Red->SetPlaying(true);
    m_Red->SetPosition({0, 90});

    m_Root.AddChild(m_Cyan);
    m_Root.AddChild(m_Orange);
    m_Root.AddChild(m_Pink);
    m_Root.AddChild(m_Red);
    m_Root.AddChild(m_Pacman);  
	m_Root.AddChild(backgroundImage);
	m_Root.Update();

    m_CurrentState = State::UPDATE;
}




