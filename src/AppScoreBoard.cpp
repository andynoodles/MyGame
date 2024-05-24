#include "App.hpp"

void App::ScoreBoard(){
    std::vector<ScoreEntity> scores = m_ScoreBoard->getScore();
    std::string text = "";
    if(scores.size() == 0){
        text = "--Enter To Start--";
    }
    else{
        for(const auto& item : scores){
	        text.append(item.name + " " + std::to_string(item.score) + "\n");
        }
    }
    
    m_ScoreBoard->SetText(text);

    m_Renderer_ScoreBorad.Update();

    if (Util::Input::IsKeyUp(Util::Keycode::RETURN)){
        m_CurrentState = State::START;
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}
