#include "App.hpp"
#include <iostream>
#include <stddef.h>

void App::Start() {
    bool showCharacter = true;
    LOG_TRACE("Start");
    backgroundImage = std::make_shared<BackgroundImage>("/image/background.png");

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

    //SPAWN FOOD
    int LargeFoodCount = 0, SmallFoodCount = 0;
    for (int i = 0; i < 4; i++) {
        m_LargeFood[i] = std::make_shared<Food>(RESOURCE_DIR"/image/Food/LargeFood.png"); 
        m_LargeFood[i]->SetZIndex(10 + LargeFoodCount);
        m_LargeFood[i]->SetVisible(true);
        m_Root.AddChild(m_LargeFood[i]);
    }
    for (int i = 0; i < 240; i++) {
        m_SmallFood[i] = std::make_shared<Food>(RESOURCE_DIR"/image/Food/SmallFood.png"); 
        m_SmallFood[i]->SetZIndex(10 + SmallFoodCount);
        m_SmallFood[i]->SetVisible(true);
        m_Root.AddChild(m_SmallFood[i]);
    }

	int pixelPerTile = backgroundImage->GetPixelPerTile();
	float upperLeftX = -(backgroundImage->GetScaledSize().x/2)+pixelPerTile/2 ,upperLeftY = backgroundImage->GetScaledSize().y/2-pixelPerTile/2;
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 28; j++) {
            int currentDot = backgroundImage->GetLayout(i, j);
            if (currentDot == 0) {
                m_SmallFood[SmallFoodCount]->SetPosition({upperLeftX + (pixelPerTile * j), upperLeftY - (pixelPerTile * i)});
                SmallFoodCount++;
            }
            else if (currentDot == 3) {
                m_LargeFood[LargeFoodCount]->SetPosition({upperLeftX + (pixelPerTile * j), upperLeftY - (pixelPerTile * i)});
                LargeFoodCount++;
            }
        }
    }

    m_Pacman = std::make_shared<Pacman>(pacmanImage);
    m_Pacman->SetZIndex(59);
    m_Pacman->SetVisible(showCharacter);
    m_Pacman->SetLooping(true);
    m_Pacman->SetPlaying(true);
    m_Pacman->SetPosition({-224 + 24, 248 - 24});
    m_Pacman->FaceEast();

    m_Cyan = std::make_shared<Ghost>(cyanImage);
    m_Cyan->SetZIndex(51);
    m_Cyan->SetVisible(showCharacter);
    m_Cyan->SetLooping(true);
    m_Cyan->SetPlaying(true);
    m_Cyan->SetPosition({0, 0});

    m_Orange = std::make_shared<Ghost>(orangeImage);
    m_Orange->SetZIndex(52);
    m_Orange->SetVisible(showCharacter);
    m_Orange->SetLooping(true);
    m_Orange->SetPlaying(true);
    m_Orange->SetPosition({0, 30});

    m_Pink = std::make_shared<Ghost>(pinkImage);
    m_Pink->SetZIndex(53);
    m_Pink->SetVisible(showCharacter);
    m_Pink->SetLooping(true);
    m_Pink->SetPlaying(true);
    m_Pink->SetPosition({0, 60});

    m_Red = std::make_shared<Ghost>(redImage);
    m_Red->SetZIndex(54);
    m_Red->SetVisible(showCharacter);
    m_Red->SetLooping(true);
    m_Red->SetPlaying(true);
    m_Red->SetPosition({0, 90});

    m_Text = std::make_shared<ShowText>(RESOURCE_DIR"/Font/all.ttf",
    20,
    "Press Enter To Start",
    Util::Color(255, 255, 255));

    m_Root.AddChild(m_Text);
    m_Root.AddChild(m_Cyan);
    m_Root.AddChild(m_Orange);
    m_Root.AddChild(m_Pink);
    m_Root.AddChild(m_Red);
    m_Root.AddChild(m_Pacman);  
	m_Root.AddChild(backgroundImage);
	m_Root.Update();

    m_CurrentState = State::UPDATE;
}




