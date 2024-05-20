#include "App.hpp"
#include "Core/Context.hpp"

int main(int, char**) {
    auto context = Core::Context::GetInstance();
    App app;
    unsigned long timeMarker = 0; 
    while (!context->GetExit()) {
        switch (app.GetCurrentState()) {
			case App::State::INIT:
				timeMarker = app.Init();
				break;

            case App::State::START:
                app.Start(timeMarker);
                break;

            case App::State::DEAD:
                app.Dead(timeMarker);
                break;

            case App::State::REVIVE:
                app.Revive(timeMarker);
                break;

            case App::State::UPDATE:
                timeMarker = app.Update();
                break;

            case App::State::SCORE_BOARD:
                app.ScoreBoard();
                break;

            case App::State::LEVEL_UP:
                app.LevelUp(timeMarker);
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
