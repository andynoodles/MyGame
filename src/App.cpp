#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

 	backgroundImage = std::make_shared<BackgroundImage>("/image/Background.png");

	m_Root.AddChild(backgroundImage);
	m_Root.Update();
    m_CurrentState = State::UPDATE;
}

void App::Update() {
	if(Util::Input::IsMouseMoving()){
		int x=	Util::Input::GetCursorPosition().x,y=Util::Input::GetCursorPosition().y;
		int nx=x + backgroundImage->GetScaledSize().x/2,ny=y - backgroundImage->GetScaledSize().y/2;
		LOG_DEBUG("X:{} Y:{}" ,x,y);
		LOG_DEBUG("new X:{} new Y {}",nx,ny);
		
	}	

	m_Root.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
