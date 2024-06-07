#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <string>
#include <cmath> 
#include "pch.hpp" // IWYU pragma: export
#include "SDL.h"

#include "Util/Renderer.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Animation.hpp"
#include "Util/Time.hpp"

#include "config.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "BackgroundImage.hpp"
#include "ShowText.hpp"
#include "Food.hpp"
#include "Score.hpp"
#include "Level.hpp"
#include "BGM.hpp"
#include "SFX.hpp"
#include "Empty.hpp"
#include "RankSystem.hpp"
#include "KeyBoard.hpp"
#include "Bonus.hpp"
#include "LevelUp.hpp"

class App {
public:
    enum class State {
		INIT,
        START,
        UPDATE,
        DEAD,
        REVIVE,
        LEVEL_CHANGE,
        NEXT_LEVEL_INIT,
        SCORE_BOARD,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

	unsigned long Init();
    unsigned long Start(unsigned long InitTime);
    unsigned long Update();
    unsigned long Dead(unsigned long InitTime);
    unsigned long Revive(unsigned long ReviveTime);
    unsigned long LevelChange(unsigned long InitTime);
    unsigned long NextLevelInit(unsigned long InitTime);
    unsigned long LevelInit(unsigned long InitTime);
    unsigned long ScoreBoard();
    void ReadKeyBoard();
    void End(); // NOLINT(readability-convert-member-functions-to-static)

    //Misc 
    unsigned long MyElapsedTime();
    void ScoreUpdate();
	void GhostCollision();//Pacman collided with ghost.
	void BGMCtrl(); //BGM control.
    void TimeOutFlashText();
    //Ghost
    void GhostStateProcess();
    void GhostMoveProcess();
	std::pair<int ,int> GetGhostTargetTile(std::shared_ptr<Ghost> ghost);
	void SetGhostSpeedMul(std::shared_ptr<Ghost> g);

	//Food
    void FoodCollision(); 	
	int FoodEatenNum(); //How many food be eaten.

    //Pacman Related
	template<class T>
	bool IfCollides(const std::shared_ptr<T> other);
	bool IfPacmanCollidesWall();
	void PacmanMoveProcess();
	std::string InputManager();
	void SetPacmanSpeedMul();
	void ChangeDirectionIfPossible();
	void Stop();
    void PacmanDead();
	std::pair<int ,int> GetTileIntented(std::string newDirection);
	void AddLifeDetect();

	//Bonus
	void BonusCtrl();

private:
    State m_CurrentState = State::INIT;
	Util::Renderer m_Renderer, m_Renderer_ScoreBorad, m_Renderer_LevelUp;
    Util::Time m_Time;
    
    std::shared_ptr<Score> m_FlashText, m_Score;
	std::shared_ptr<ShowText> m_ReadyText, m_GameOverText;
    std::shared_ptr<Food> m_SmallFood[SMALL_FOOD_NUM];
    std::shared_ptr<Food> m_LargeFood[LARGE_FOOD_NUM];
    
    std::shared_ptr<LevelUp> m_LevelUp;
    std::shared_ptr<BackgroundImage> m_BackgroundImage;
    std::shared_ptr<Pacman> m_Pacman, m_PacmanDead;
    std::shared_ptr<Ghost> m_Red, m_Pink, m_Cyan, m_Orange;
	std::shared_ptr<Empty> m_Empty1 ,m_Empty2; //16x16 black img.
	std::vector<std::shared_ptr<Empty>> m_LifeIcons ,m_BonusIcons; 
    SFX m_SFX;
    BGM m_BGM;
	std::shared_ptr<Bonus> m_Bonus;

    //custom classes
    unsigned long FoodEffectMarker = 0;
    bool alreadyStage1 = false ,alreadyStage2 = false ,alreadyAddIife;
    bool cheatMode = false;
    Level currentLevel;
    std::shared_ptr<RankSystem> m_ScoreBoard;
};

#endif
