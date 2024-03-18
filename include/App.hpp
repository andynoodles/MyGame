#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Util/Root.hpp"
#include "AnimatedCharacter.hpp"
#include "BackgroundImage.hpp"
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

  std::shared_ptr<BackgroundImage> backgroundImage;
    std::shared_ptr<AnimatedCharacter> m_Pacman;
    std::shared_ptr<AnimatedCharacter> m_Red;
    std::shared_ptr<AnimatedCharacter> m_Pink;
    std::shared_ptr<AnimatedCharacter> m_Cyan;
    std::shared_ptr<AnimatedCharacter> m_Orange;
};

#endif
