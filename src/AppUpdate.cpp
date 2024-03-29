#include "App.hpp"

void App::Update() {
    TimeUpdate();
    InputManager();

    FoodCollision();
    FoodEffect();

    m_Pacman->Move(m_Pacman->GetDirection(), 1);

    m_Root.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}
