#include "Game.h"

static Game* game = nullptr;

namespace UIFuncs
{

void connect(Game* to)
{
	game = to;
}

void newGame()
{
	// Load new game
	game->newGame();
}

void exitGame()
{
	// TODO: Clean up?
	// game->cleanUp(); ??
	exit(0);
}

void returnToMenu()
{
	game->returnToMenu();
}

void toggleOverlayMenu()
{
	game->toggleOverlay();
}

} // namespace UIFuncs