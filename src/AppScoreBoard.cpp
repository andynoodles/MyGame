#include "App.hpp"
#include <string>

unsigned long App::ScoreBoard(){
	m_BGM.Pause();
    std::vector<ScoreEntity> scores = m_ScoreBoard->getScore();

	for(auto lifeIcon : m_LifeIcons){
		lifeIcon->SetVisible(false);
	}
	for(auto bonusIcon : m_BonusIcons){
		bonusIcon->SetVisible(false);
	}

    std::string text = "";
    if(scores.size() == 0){
        text = "--Enter To Start--";
    }
    else{
        int index = 1;
        for(const auto& item : scores){
	        text.append(std::to_string(index++)+ " " + std::to_string(item.score) + "\n");
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

    return MyElapsedTime();
}
