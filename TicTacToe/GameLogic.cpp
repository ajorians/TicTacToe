#include "GameLogic.h"
#include "GameBoard.h"

GameLogic::GameLogic(GameBoard& board)
	: m_Board(board)
{
	ResetGame();
}

void GameLogic::ResetGame()
{
	m_Board.ClearBoard();
	m_CurrentTurn = X;
}

void GameLogic::PlaceNextPiece(int x, int y)
{
	if (IsGameOver())
		return;

	if (!m_Board.HasPiece(x, y))
	{
		m_Board.SetPieceAt(x, y, m_CurrentTurn);
		m_CurrentTurn = m_CurrentTurn == X ? O : X;
	}
}

bool GameLogic::IsGameOver() const
{
	return false;
}

