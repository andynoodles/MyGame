#include "App.hpp"

void App::Update() {

  if (Util::Input::IsKeyDown(Util::Keycode::W)) {
    m_Pacman->Speed = {0, 5};
    m_Pacman->SpeedMultiplier = 1;
  } else if (Util::Input::IsKeyDown(Util::Keycode::A)) {
    m_Pacman->Speed = {-5, 0};
    m_Pacman->SpeedMultiplier = 1;
  } else if (Util::Input::IsKeyDown(Util::Keycode::S)) {
    m_Pacman->Speed = {0, -5};
    m_Pacman->SpeedMultiplier = 1;
  } else if (Util::Input::IsKeyDown(Util::Keycode::D)) {
    m_Pacman->Speed = {5, 0};
    m_Pacman->SpeedMultiplier = 1;
  }

  m_Pacman->Move(m_Pacman->Speed, m_Pacman->SpeedMultiplier);

  m_Root.Update();
  if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
    m_CurrentState = State::END;
  }
}

