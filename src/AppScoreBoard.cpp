#include "App.hpp"
#include <string>

void App::ScoreBoard(){
    std::vector<ScoreEntity> scores = m_ScoreBoard->getScore();
    std::string text = "";
    
    for(const auto& item : scores){
        text.append(item.name + " " + std::to_string(item.score) + "\n");
    }
    m_ScoreBoard->SetText(text);

    m_Renderer2.Update();

    if (Util::Input::IsKeyUp(Util::Keycode::RETURN) || Util::Input::IfExit()) {
        m_CurrentState = State::START;
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}
