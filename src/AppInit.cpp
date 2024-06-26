#include "App.hpp"

unsigned long App::Init() {
    bool showCharacter = true;
    LOG_TRACE("Start");
    currentLevel.SetLevel(START_LEVEL);
    m_BackgroundImage = std::make_shared<BackgroundImage>("/image/background.png");

    std::vector<std::string> pacmanImage, pacmanDead, cyanImage, orangeImage, pinkImage, redImage, levelUpImage;
    levelUpImage.reserve(LEVEL_UP_ANIMATION_RESERVE);
    pacmanImage.reserve(PACMAN_ASSETS_NUM);
    cyanImage.reserve(GHOST_ASSETS_RESERVE);
    orangeImage.reserve(GHOST_ASSETS_RESERVE);
    pinkImage.reserve(GHOST_ASSETS_RESERVE);
    redImage.reserve(GHOST_ASSETS_RESERVE);

    levelUpImage.emplace_back(RESOURCE_DIR"/image/background.png");
    levelUpImage.emplace_back(RESOURCE_DIR"/image/background2.jpg");

    m_LevelUp = std::make_shared<LevelUp>(levelUpImage);
    m_LevelUp->SetLooping(true);
    m_LevelUp->SetPlaying(true);
    m_LevelUp->SetVisible(true);

    for (int i = 0; i < PACMAN_ASSETS_NUM; ++i) {
        pacmanImage.emplace_back(RESOURCE_DIR"/image/Pac/Sprite (" + std::to_string(i + 1) + ").png");
    }

    for (int i = 0; i < 15; ++i) {
        pacmanDead.emplace_back(RESOURCE_DIR"/image/PacmanDead/Sprite (" + std::to_string(i + 3) + ").png");
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
        m_Renderer.AddChild(m_LargeFood[i]);
    }
    for (int i = 0; i < SMALL_FOOD_NUM; i++) {
        m_SmallFood[i] = std::make_shared<Food>(RESOURCE_DIR"/image/Food/SmallFood.png"); 
        m_SmallFood[i]->SetZIndex(10);
        m_SmallFood[i]->SetVisible(true);
        m_Renderer.AddChild(m_SmallFood[i]);
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
    m_Pacman->SetZIndex(50);
    m_Pacman->SetVisible(showCharacter);
    m_Pacman->SetLooping(true);
    m_Pacman->SetPlaying(false);
    // m_Pacman->SetPosition({upperLeftX + PIXELPERTILE, upperLeftY - PIXELPERTILE});
	m_Pacman->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(PACMAN_STARTTILE_X,PACMAN_STARTTILE_Y));

    m_PacmanDead = std::make_shared<Pacman>(pacmanDead);
    m_PacmanDead->SetZIndex(50);
    m_PacmanDead->SetVisible(false);
    m_PacmanDead->SetLooping(false);
    m_PacmanDead->SetPlaying(false);

    m_Cyan = std::make_shared<Ghost>(cyanImage);
    m_Cyan->SetZIndex(18);
    m_Cyan->SetVisible(showCharacter);
    m_Cyan->SetLooping(true);
    m_Cyan->SetPlaying(false);
    m_Cyan->SetState(Ghost::GhostState::SCATTER);
    m_Cyan->SetVisible(false);

    m_Orange = std::make_shared<Ghost>(orangeImage);
    m_Orange->SetZIndex(17);
    m_Orange->SetVisible(showCharacter);
    m_Orange->SetLooping(true);
    m_Orange->SetPlaying(false);
    m_Orange->SetState(Ghost::GhostState::SCATTER);
    m_Orange->SetVisible(false);

    m_Pink = std::make_shared<Ghost>(pinkImage);
    m_Pink->SetZIndex(16);
    m_Pink->SetVisible(showCharacter);
    m_Pink->SetLooping(true);
    m_Pink->SetPlaying(false);
    m_Pink->SetState(Ghost::GhostState::SCATTER);
    m_Pink->SetVisible(false);

    m_Red = std::make_shared<Ghost>(redImage);
    m_Red->SetZIndex(15);
    m_Red->SetVisible(showCharacter);
    m_Red->SetLooping(true);
    m_Red->SetPlaying(false);
    m_Red->SetState(Ghost::GhostState::SCATTER);
    m_Red->SetVisible(false);

    m_FlashText = std::make_shared<Score>(RESOURCE_DIR"/Font/emulogic.ttf",
    8,
    "0",
    Util::Color(0, 255, 250));
    m_FlashText->SetVisible(false);
    m_FlashText->SetZIndex(100);

    m_Score = std::make_shared<Score>(
        RESOURCE_DIR"/Font/emulogic.ttf",
        20,
        "0",
        Util::Color(255, 255, 255));

    m_Score->SetPosition({400, 228});
    m_Score->SetVisible(true);

    m_ReadyText = std::make_shared<ShowText>(
        RESOURCE_DIR"/Font/emulogic.ttf",
        16,
        "READY!",
        Util::Color(255, 255, 0)); //yellow

    m_ReadyText->SetPosition({READY_TEXT_X, READY_TEXT_Y});
    m_ReadyText->SetVisible(true);

    m_GameOverText = std::make_shared<ShowText>(
        RESOURCE_DIR"/Font/emulogic.ttf",
        16,
        "GAME OVER",
        Util::Color(255, 0, 0)); //red

    m_GameOverText->SetPosition({ READY_TEXT_X, READY_TEXT_Y });
    m_GameOverText->SetVisible(false);

	m_Empty1=std::make_shared<Empty>(RESOURCE_DIR"/image/empty.bmp");
	m_Empty1->SetVisible(true);
	m_Empty1-> SetPosition({TP_X1 , m_BackgroundImage->GetUpperLeftY() - (PIXELPERTILE*TP_TILE_Y)});

   	m_Empty2=std::make_shared<Empty>(RESOURCE_DIR"/image/empty.bmp");
	m_Empty2->SetVisible(true);
	m_Empty2-> SetPosition({TP_X2 , m_BackgroundImage->GetUpperLeftY() - (PIXELPERTILE*TP_TILE_Y)});

	m_Bonus = std::make_shared<Bonus>(currentLevel.GetBonusImgPath());
	m_Bonus->SetVisible(false);
	m_Bonus->SetAppearTime();

	m_LifeIcons.resize(PACMAN_LIFE);
	for(int i = 0 ;i < PACMAN_LIFE ;i++){ //Life icon indicates how many life are left to die.
		std::shared_ptr<Empty> lifeIcon = std::make_shared<Empty>(RESOURCE_DIR"/image/Pac/LifeIcon.png");
		lifeIcon->SetPosition({-MAP_WIDTH/2 + (i+1)*PIXELPERTILE*2 ,-MAP_HEIGHT/2 - PIXELPERTILE});
		lifeIcon->SetVisible(false);
		m_LifeIcons[i] = lifeIcon;
		m_Renderer.AddChild(lifeIcon);
	}

	m_BonusIcons.resize(TOTAL_LEVEL);
	for(int i = 0 ; i < m_BonusIcons.size() ; i++){
		std::shared_ptr<Empty> bonusIcon= std::make_shared<Empty>(currentLevel.GetBonusImgPath(i));
		bonusIcon->SetPosition({MAP_WIDTH/2-(i+1)*PIXELPERTILE*2 ,-MAP_HEIGHT/2 - PIXELPERTILE});
		bonusIcon->SetVisible(false);
		m_BonusIcons[i] = bonusIcon;
		m_Renderer.AddChild(bonusIcon);	
	}

    m_Renderer.AddChild(m_Score);
    m_Renderer.AddChild(m_ReadyText);
    m_Renderer.AddChild(m_GameOverText);
    m_Renderer.AddChild(m_FlashText);
    m_Renderer.AddChild(m_Cyan);
    m_Renderer.AddChild(m_Orange);
    m_Renderer.AddChild(m_Pink);
    m_Renderer.AddChild(m_Red);
    m_Renderer.AddChild(m_Pacman);  
	m_Renderer.AddChild(m_BackgroundImage);
	m_Renderer.AddChild(m_Empty1);
	m_Renderer.AddChild(m_Empty2);
    m_Renderer.AddChild(m_PacmanDead);
	m_Renderer.AddChild(m_Bonus);
    
    // m_Renderer_ScoreBorad 
    m_ScoreBoard = std::make_shared<RankSystem>(
        RESOURCE_DIR"/ScoreBoard/score.txt",
        RESOURCE_DIR"/Font/emulogic.ttf",
        20,
        "0",
        Util::Color(255, 255, 255));
    m_ScoreBoard->SetZIndex(100);
    m_ScoreBoard->SetPosition({0, 0});
    m_ScoreBoard->SetVisible(true);
    m_ScoreBoard->readScores();

    m_Renderer_ScoreBorad.AddChild(m_ScoreBoard);

    // m_Renderer_LevelUp
    m_Renderer_LevelUp.AddChild(m_LevelUp);

    m_CurrentState = State::SCORE_BOARD;

    return MyElapsedTime();
}
