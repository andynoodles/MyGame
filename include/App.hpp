#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include "pch.hpp" // IWYU pragma: export

#include "Util/Root.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Animation.hpp"

#include "Pacman.hpp"
#include "Ghost.hpp"
#include "BackgroundImage.hpp"
#include "ShowText.hpp"

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

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;
	Util::Root m_Root;

    std::shared_ptr<ShowText> m_Text;

    std::shared_ptr<BackgroundImage> backgroundImage;
    std::shared_ptr<Pacman> m_Pacman;
    std::shared_ptr<Ghost> m_Red;
    std::shared_ptr<Ghost> m_Pink;
    std::shared_ptr<Ghost> m_Cyan;
    std::shared_ptr<Ghost> m_Orange;
};

#endif
