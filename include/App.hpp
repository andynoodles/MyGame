#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <string>
#include "pch.hpp" // IWYU pragma: export

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

    void TimeUpdate();
    void SetTimeMarker();
    void FoodCollision();
    void FoodEffect();
    unsigned long GetElapsedTime();
    unsigned long GetDeltaTime();
    unsigned long GetMarker();

    bool IfCollides(const std::shared_ptr<Food>& other);
    bool IfCollides(const std::shared_ptr<Ghost>& other);

    void InputManager();
 
private:
    void ValidTask();

private:
    State m_CurrentState = State::START;
	Util::Root m_Root;
    Util::Time m_Time;
    unsigned long Marker = 0;
    bool onPill = false;
    std::shared_ptr<ShowText> m_Text;

    std::shared_ptr<Food> m_SmallFood[SMALL_FOOD_NUM];
    std::shared_ptr<Food> m_LargeFood[LARGE_FOOD_NUM];
    
    std::shared_ptr<BackgroundImage> m_BackgroundImage;
    std::shared_ptr<Pacman> m_Pacman;
    std::shared_ptr<Ghost> m_Red;
    std::shared_ptr<Ghost> m_Pink;
    std::shared_ptr<Ghost> m_Cyan;
    std::shared_ptr<Ghost> m_Orange;
};

#endif
