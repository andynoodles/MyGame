#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <string>
#include <cmath> 
#include "pch.hpp" // IWYU pragma: export

#include "Util/Root.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Animation.hpp"
#include "Util/Time.hpp"
#include "Util/SFX.hpp"
#include "Util/BGM.hpp"

#include "config.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "BackgroundImage.hpp"
#include "ShowText.hpp"
#include "Food.hpp"
#include "Score.hpp"
#include "Level.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

    //Misc 
    void TimeUpdate();
    void ScoreUpdate();
    void FoodCollision(); 	
	void GhostCollision();//Pacman collided with ghost.
//	bool IsFoodAllEaten();

    //Ghost
    void GhostStateProcess();
    void GhostMoveProcess();
	std::pair<int ,int> GetGhostTargetTile(std::shared_ptr<Ghost> ghost);
    
    //Time Related
    unsigned long GetElapsedTime();
    unsigned long GetDeltaTime();

    //Pacman Related
    bool IfCollides(const std::shared_ptr<Food>& other);
    bool IfCollides(const std::shared_ptr<Ghost>& other);
	bool IfPacmanCollidesWall();
	void PacmanMoveProcess();
	std::string InputManager();
	void ChangeDirectionIfPossible();
	void Stop();


	std::pair<int ,int> GetTileIntented(std::string newDirection);

private:
    State m_CurrentState = State::START;
	Util::Root m_Root;
    Util::Time m_Time;
    
    std::shared_ptr<ShowText> m_Text;
    std::shared_ptr<Score> m_Score;
    std::shared_ptr<Food> m_SmallFood[SMALL_FOOD_NUM];
    std::shared_ptr<Food> m_LargeFood[LARGE_FOOD_NUM];
    
    std::shared_ptr<BackgroundImage> m_BackgroundImage;
    std::shared_ptr<Pacman> m_Pacman;
    std::shared_ptr<Ghost> m_Red, m_Pink, m_Cyan, m_Orange;
    std::shared_ptr<Util::SFX> m_SFX;
    std::shared_ptr<Util::BGM> m_BGM;

    //custom classes
    unsigned long FoodEffectMarker = 0;
    Level currentLevel;
};

#endif
