#include "App.hpp"

void App::Update() {
    if (Util::Input::IsKeyDown(Util::Keycode::W)) {
        m_Pacman->Speed = {0, 5};
        m_Pacman->SpeedMultiplier = 1;
    } 
    else if (Util::Input::IsKeyDown(Util::Keycode::A)) {
        m_Pacman->Speed = {-5, 0};
        m_Pacman->SpeedMultiplier = 1;
    } 
    else if (Util::Input::IsKeyDown(Util::Keycode::S)) {
        m_Pacman->Speed = {0, -5};
        m_Pacman->SpeedMultiplier = 1;
    } 
    else if (Util::Input::IsKeyDown(Util::Keycode::D)) {
        m_Pacman->Speed = {5, 0};
        m_Pacman->SpeedMultiplier = 1;
    }

    m_Cyan->GhostMove({0,-5}, 0.5);
    m_Pacman->Move(m_Pacman->Speed, m_Pacman->SpeedMultiplier);

    // m_Text->SetText(std::to_string(m_Pacman->GetPosition().x) + 
    //                 ", " +
    //                 std::to_string(m_Pacman->GetPosition().y));

    m_Text->SetText(std::to_string(backgroundImage->typeOfPixel(m_Pacman->GetPosition().x, m_Pacman->GetPosition().y)));

    m_Root.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}
