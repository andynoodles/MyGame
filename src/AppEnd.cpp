#include "App.hpp"

void App::End() { // NOLINT(this method will mutate members in the future)
	if(m_Pacman->IsDead()) LOG_DEBUG("Game Over");
	if(m_Score->IsFoodAllEaten()) LOG_DEBUG("Win:)");
    LOG_TRACE("End");
}
