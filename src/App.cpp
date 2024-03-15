#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "BackgroundImage.hpp"

#include<iostream>

void App::Start() {
    LOG_TRACE("Start");
	std::shared_ptr<BackgroundImage> backgroundImage=std::make_shared<BackgroundImage>();
	backgroundImage->SetVisible(true);

	std::cout<<backgroundImage->GetScaledSize().y;

//	std::shared_ptr<Util::Image> backgroundImage=std::make_shared<Util::Image>(RESOURCE_DIR"/Image/a.png");
//	backgroundImage->Draw();

	m_Root.AddChild(backgroundImage);
	m_Root.Update();

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3
    
    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
	
//	if(Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)){
//		std::cout<<Util::Image::GetSize();
//	}

	m_Root.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
