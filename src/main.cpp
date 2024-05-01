#include "App.hpp"
#include "Core/Context.hpp"

int main(int, char**) {
    auto context = Core::Context::GetInstance();
    App app;
    unsigned long timeMarker = 100000; 
    while (!context->GetExit()) {
        switch (app.GetCurrentState()) {
			case App::State::INIT:
				timeMarker = app.Init();
				break;

            case App::State::START:
                app.Start(timeMarker);
                break;

            case App::State::DEAD:
                timeMarker = app.Dead();
                break;

            case App::State::REVIVE:
                app.Revive(timeMarker);
                break;

            case App::State::UPDATE:
                app.Update();
                break;

            case App::State::END:
                app.End();
                context->SetExit(true);
                break;
        }
        context->Update();
    }
    return 0;
}
