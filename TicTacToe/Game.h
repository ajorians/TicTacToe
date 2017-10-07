#pragma once

#include "GameBoard.h"
#include "GameLogic.h"

struct SDL_Surface;
struct SDL_Renderer;
struct SDL_Texture;
class DisplayMetrics;

class Game
{
public:
	Game(SDL_Renderer* renderer, DisplayMetrics* pMetrics, int nDimension);
	~Game();
	bool Loop(SDL_Renderer* renderer);

private:
	void Render(SDL_Renderer* renderer);

	bool IsGameOver() const;

private:
	//The image we will load and show on the screen
	SDL_Surface* m_GameOverSurface= nullptr;
	SDL_Texture * m_GameOverTexture = nullptr;

	SDL_Surface* m_XSurface = nullptr;
	SDL_Texture * m_XTexture = nullptr;

	SDL_Surface* m_OSurface = nullptr;
	SDL_Texture * m_OTexture = nullptr;

	GameBoard m_Board;
	GameLogic m_Logic;

	DisplayMetrics* m_pMetrics;//Does not own
};
