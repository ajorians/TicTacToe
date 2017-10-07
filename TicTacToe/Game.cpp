#include "Game.h"
#include "DisplayMetrics.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

Game::Game(SDL_Renderer* renderer, DisplayMetrics* pMetrics, int nDimension)
	: m_Board(nDimension), m_Logic(m_Board), m_pMetrics(pMetrics)
{
	m_GameOverSurface = IMG_Load("GameOver.png");
	if (m_GameOverSurface == nullptr)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "Something.png", SDL_GetError());
	}

	m_GameOverTexture = SDL_CreateTextureFromSurface(renderer, m_GameOverSurface);

	m_XSurface = IMG_Load("X.png");
	if (m_XSurface == nullptr)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "X.png", SDL_GetError());
	}

	m_XTexture = SDL_CreateTextureFromSurface(renderer, m_XSurface);

	m_OSurface = IMG_Load("O.png");
	if (m_XSurface == nullptr)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "O.png", SDL_GetError());
	}

	m_OTexture = SDL_CreateTextureFromSurface(renderer, m_OSurface);
}

Game::~Game()
{
	//Deallocate surface
	SDL_DestroyTexture(m_XTexture);
	SDL_FreeSurface(m_XSurface);

	SDL_DestroyTexture(m_OTexture);
	SDL_FreeSurface(m_OSurface);

	SDL_DestroyTexture(m_GameOverTexture);
	SDL_FreeSurface(m_GameOverSurface);
}

bool Game::Loop(SDL_Renderer* renderer)
{
	Render(renderer);

	//Event handler
	SDL_Event e;

	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		//User presses a key
		else if (e.type == SDL_KEYDOWN)
		{
			//Select surfaces based on key press
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return false;

			case SDLK_F2:
				m_Logic.ResetGame();
				break;

			default:
				break;
			}
		}
		//If mouse event happened
		else if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
		{
			//Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);

			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				int nX = -1, nY = -1;
				if (m_pMetrics->GetSpot(m_Board.GetDimension(), x, y, nX, nY))
				{
					m_Logic.PlaceNextPiece(nX, nY);
				}
			}
		}
	}

	return true;
}

void Game::Render(SDL_Renderer* renderer)
{
	// Set render color to red ( background will be rendered in this color )
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Clear winow
	SDL_RenderClear(renderer);

	// Set render color to blue ( rect will be rendered in this color )
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	// Draw board
	int numLines = m_pMetrics->GetNumLines( m_Board.GetDimension() );

	int lineThickness = 20;
	for (int i = 0; i < numLines; i++)
	{
		int verticalSpacing = m_pMetrics->GetColumnWidth(m_Board.GetDimension());
		int horizontalSpacing = m_pMetrics->GetRowHeight(m_Board.GetDimension());

		// Draw vertical lines
		SDL_Rect rVertical{ m_pMetrics->GetGameAreaLeft() + (i+1)*verticalSpacing - lineThickness /2, m_pMetrics->GetGameAreaTop(), lineThickness, horizontalSpacing*(numLines+1) };

		// Render rect
		SDL_RenderFillRect(renderer, &rVertical);

		// Draw horizontal lines
		SDL_Rect rHorizontal{ m_pMetrics->GetGameAreaLeft(), m_pMetrics->GetGameAreaTop() + (i+1)*horizontalSpacing - lineThickness / 2, verticalSpacing*(numLines+1), lineThickness };

		// Render rect
		SDL_RenderFillRect(renderer, &rHorizontal);
	}

	for (int x = 0; x < m_Board.GetDimension(); x++)
	{
		for (int y = 0; y < m_Board.GetDimension(); y++)
		{
			SpotType eType = m_Board.GetPieceAt(x, y);
			if (eType == Empty)
				continue;

			SDL_Rect dstRect = m_pMetrics->GetSpotRect(m_Board.GetDimension(), x, y);
			dstRect.x += lineThickness / 2;
			dstRect.y += lineThickness / 2;
			dstRect.w -= lineThickness;
			dstRect.h -= lineThickness;
			SDL_RenderCopy(renderer, eType == X ? m_XTexture : m_OTexture, NULL, &dstRect);
		}
	}

	if (IsGameOver())
	{
		SDL_Rect dstRect = { m_pMetrics->GetGameAreaLeft(), m_pMetrics->GetGameAreaTop(), m_pMetrics->GetGameAreaWidth(), m_pMetrics->GetGameAreaHeight() };
		SDL_RenderCopy(renderer, m_GameOverTexture, NULL, &dstRect);
	}

	// Render the rect to the screen
	SDL_RenderPresent(renderer);
}

bool Game::IsGameOver() const
{
	return m_Logic.IsGameOver();
}

