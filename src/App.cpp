#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "BackgroundImage.hpp"

#include<iostream>

void App::Start() {
    LOG_TRACE("Start");
	std::shared_ptr<BackgroundImage> backgroundImage = std::make_shared<BackgroundImage>();


	m_Root.AddChild(backgroundImage);
	m_Root.Update();

    m_CurrentState = State::UPDATE;
}

void App::Update() {

	m_Root.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
