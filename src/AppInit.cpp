#include "App.hpp"

unsigned long App::Init() {
    bool showCharacter = true;
    LOG_TRACE("Start");
    m_BackgroundImage = std::make_shared<BackgroundImage>("/image/background.png");

    std::vector<std::string> pacmanImage, cyanImage, orangeImage, pinkImage, redImage;
    pacmanImage.reserve(PACMAN_ASSETS_NUM);
    cyanImage.reserve(GHOST_ASSETS_RESERVE);
    orangeImage.reserve(GHOST_ASSETS_RESERVE);
    pinkImage.reserve(GHOST_ASSETS_RESERVE);
    redImage.reserve(GHOST_ASSETS_RESERVE);
    for (int i = 0; i < PACMAN_ASSETS_NUM; ++i) {
        pacmanImage.emplace_back(RESOURCE_DIR"/image/Pac/Sprite (" + std::to_string(i + 1) + ").png");
    }

    for (int i = 0; i < GHOST_ASSETS_NUM; i++) {
        cyanImage.emplace_back(RESOURCE_DIR"/image/Cyan/Sprite (" + std::to_string(i + 85) + ").png");
        orangeImage.emplace_back(RESOURCE_DIR"/image/Orange/Sprite (" + std::to_string(i + 99) + ").png");
        pinkImage.emplace_back(RESOURCE_DIR"/image/Pink/Sprite (" + std::to_string(i + 71) + ").png");
        redImage.emplace_back(RESOURCE_DIR"/image/Red/Sprite (" + std::to_string(i + 57) + ").png");
    }

    for (int i = 0; i < GHOST_SCARED_ASSETS_NUM; i++) {
        cyanImage.emplace_back(RESOURCE_DIR"/image/ScaredMonster/Sprite (" + std::to_string(i + 65) + ").png");
        orangeImage.emplace_back(RESOURCE_DIR"/image/ScaredMonster/Sprite (" + std::to_string(i + 65) + ").png");
        pinkImage.emplace_back(RESOURCE_DIR"/image/ScaredMonster/Sprite (" + std::to_string(i + 65) + ").png");
        redImage.emplace_back(RESOURCE_DIR"/image/ScaredMonster/Sprite (" + std::to_string(i + 65) + ").png");
    }

    for (int i = 0; i < GHOST_EYE_ASSETS_NUM; i++) {
        cyanImage.emplace_back(RESOURCE_DIR"/image/Eyes/Look (" + std::to_string(i + 1) + ").png");
        orangeImage.emplace_back(RESOURCE_DIR"/image/Eyes/Look (" + std::to_string(i + 1) + ").png");
        pinkImage.emplace_back(RESOURCE_DIR"/image/Eyes/Look (" + std::to_string(i + 1) + ").png");
        redImage.emplace_back(RESOURCE_DIR"/image/Eyes/Look (" + std::to_string(i + 1) + ").png");
    }

    //SPAWN FOOD
    int LargeFoodCount = 0, SmallFoodCount = 0;
    for (int i = 0; i < LARGE_FOOD_NUM; i++) {
        m_LargeFood[i] = std::make_shared<Food>(RESOURCE_DIR"/image/Food/LargeFood.png"); 
        m_LargeFood[i]->SetZIndex(10);
        m_LargeFood[i]->SetVisible(true);
        m_Root.AddChild(m_LargeFood[i]);
    }
    for (int i = 0; i < SMALL_FOOD_NUM; i++) {
        m_SmallFood[i] = std::make_shared<Food>(RESOURCE_DIR"/image/Food/SmallFood.png"); 
        m_SmallFood[i]->SetZIndex(10);
        m_SmallFood[i]->SetVisible(true);
        m_Root.AddChild(m_SmallFood[i]);
    }

	float upperLeftX = m_BackgroundImage->GetUpperLeftX() ,upperLeftY = m_BackgroundImage->GetUpperLeftY();
    for (int i = 0; i <NUMBEROFTILESY ;i++) {
        for (int j = 0; j < NUMBEROFTILESX ;j++) {
            int currentDot = m_BackgroundImage->GetLayout(i, j);
            if (currentDot == 0) {
                m_SmallFood[SmallFoodCount]->SetPosition({upperLeftX + (PIXELPERTILE * j), upperLeftY - (PIXELPERTILE * i)});
                SmallFoodCount++;
            }
            else if (currentDot == 3) {
                m_LargeFood[LargeFoodCount]->SetPosition({upperLeftX + (PIXELPERTILE * j), upperLeftY - (PIXELPERTILE * i)});
                LargeFoodCount++;
            }
        }
    }

    m_Pacman = std::make_shared<Pacman>(pacmanImage);
    m_Pacman->SetZIndex(19);
    m_Pacman->SetVisible(showCharacter);
    m_Pacman->SetLooping(true);
    m_Pacman->SetPlaying(true);
//    m_Pacman->SetPosition({upperLeftX + PIXELPERTILE, upperLeftY - PIXELPERTILE});
	m_Pacman->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(PACMAN_STARTTILE_X,PACMAN_STARTTILE_Y));
    m_Pacman->FaceEast();

    m_Cyan = std::make_shared<Ghost>(cyanImage);
    m_Cyan->SetZIndex(18);
    m_Cyan->SetVisible(showCharacter);
    m_Cyan->SetLooping(true);
    m_Cyan->SetPlaying(true);
//    m_Cyan->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(11, 14));
    m_Cyan->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(1 ,NUMBEROFTILESY-2));

    m_Orange = std::make_shared<Ghost>(orangeImage);
    m_Orange->SetZIndex(17);
    m_Orange->SetVisible(showCharacter);
    m_Orange->SetLooping(true);
    m_Orange->SetPlaying(true);
//    m_Orange->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(11, 14));
    m_Orange->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(NUMBEROFTILESX-2 ,NUMBEROFTILESY-2));

    m_Pink = std::make_shared<Ghost>(pinkImage);
    m_Pink->SetZIndex(16);
    m_Pink->SetVisible(showCharacter);
    m_Pink->SetLooping(true);
    m_Pink->SetPlaying(true);
    //m_Pink->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(11, 14));
    m_Pink->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(NUMBEROFTILESX-2 ,1));

    m_Red = std::make_shared<Ghost>(redImage);
    m_Red->SetZIndex(15);
    m_Red->SetVisible(showCharacter);
    m_Red->SetLooping(true);
    m_Red->SetPlaying(true);
    //m_Red->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(6, 5));
    m_Red->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(1 ,1));

    m_FlashText = std::make_shared<Score>(RESOURCE_DIR"/Font/emulogic.ttf",
    8,
    "FlashScore",
    Util::Color(0, 255, 250));
    m_FlashText->SetVisible(false);
    m_FlashText->SetZIndex(100);

    m_Score = std::make_shared<Score>(RESOURCE_DIR"/Font/emulogic.ttf",
    20,
    "MainScore",
    Util::Color(255, 255, 255));
    m_Score->SetPosition({400, 228});
    m_Score->SetVisible(true);

    m_ReadyText = std::make_shared<ShowText>(RESOURCE_DIR"/Font/emulogic.ttf",
    16,
    "READY!",
    Util::Color(255, 255, 0)); //yellow
    m_ReadyText->SetPosition({READY_TEXT_X, READY_TEXT_Y});
    m_ReadyText->SetVisible(true);
    
	m_Empty1=std::make_shared<Empty>(RESOURCE_DIR"/image/empty.bmp");
	m_Empty1->SetVisible(true);
	m_Empty1-> SetPosition({TP_X1 , m_BackgroundImage->GetUpperLeftY() - (PIXELPERTILE*TP_TILE_Y)});

   	m_Empty2=std::make_shared<Empty>(RESOURCE_DIR"/image/empty.bmp");
	m_Empty2->SetVisible(true);
	m_Empty2-> SetPosition({TP_X2 , m_BackgroundImage->GetUpperLeftY() - (PIXELPERTILE*TP_TILE_Y)});

    m_Root.AddChild(m_Score);
    m_Root.AddChild(m_ReadyText);
    m_Root.AddChild(m_FlashText);
    m_Root.AddChild(m_Cyan);
    m_Root.AddChild(m_Orange);
    m_Root.AddChild(m_Pink);
    m_Root.AddChild(m_Red);
    m_Root.AddChild(m_Pacman);  
	m_Root.AddChild(m_BackgroundImage);
	m_Root.AddChild(m_Empty1);
	m_Root.AddChild(m_Empty2);


    currentLevel.SetLevel(1);

    m_CurrentState = State::START;
    return m_Time.GetElapsedTimeMs();
}
