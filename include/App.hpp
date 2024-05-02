#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <string>
#include <cmath> 
#include "pch.hpp" // IWYU pragma: export
#include "SDL.h"

#include "Util/Root.hpp"
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

class App {
public:
    enum class State {
		INIT,
        START,
        UPDATE,
        DEAD,
        REVIVE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

	unsigned long Init();
    unsigned long Start(unsigned long InitTime);
    unsigned long Update();
    unsigned long Dead(unsigned long InitTime);
    unsigned long Revive(unsigned long ReviveTime);

    void End(); // NOLINT(readability-convert-member-functions-to-static)

    //Misc 
    void TimeUpdate();
    void ScoreUpdate();
    void FoodCollision(); 	
	void GhostCollision();//Pacman collided with ghost.
//	bool IsFoodAllEaten();
	void BGMCtrl(); //BGM control.

    //Ghost
    void GhostStateProcess();
    void GhostMoveProcess();
	std::pair<int ,int> GetGhostTargetTile(std::shared_ptr<Ghost> ghost);

    //Pacman Related
    bool IfCollides(const std::shared_ptr<Food>& other);
    bool IfCollides(const std::shared_ptr<Ghost>& other);
	bool IfPacmanCollidesWall();
	void PacmanMoveProcess();
	std::string InputManager();
	void ChangeDirectionIfPossible();
	void Stop();
    void PacmanDead();


	std::pair<int ,int> GetTileIntented(std::string newDirection);

private:
    State m_CurrentState = State::INIT;
	Util::Root m_Root;
    Util::Time m_Time;
    
    std::shared_ptr<Score> m_FlashText, m_Score;
	std::shared_ptr<ShowText> m_ReadyText;
    std::shared_ptr<Food> m_SmallFood[SMALL_FOOD_NUM];
    std::shared_ptr<Food> m_LargeFood[LARGE_FOOD_NUM];
    
    std::shared_ptr<BackgroundImage> m_BackgroundImage;
    std::shared_ptr<Pacman> m_Pacman, m_PacmanDead;
    std::shared_ptr<Ghost> m_Red, m_Pink, m_Cyan, m_Orange;
	std::shared_ptr<Empty> m_Empty1 ,m_Empty2; //16x16 black img.
    SFX m_SFX;
    BGM m_BGM;

    //custom classes
    unsigned long FoodEffectMarker = 0;
    Level currentLevel;
};

#endif
