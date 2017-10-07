#include "GameBoard.h"

GameBoard::GameBoard(int nDimension)
{
	m_Board.resize(nDimension);
	for (int i = 0; i < nDimension; i++)
	{
		m_Board[i].resize(nDimension);
	}

	ClearBoard();
}

void GameBoard::ClearBoard()
{
	for (int nX = 0; nX < GetWidth(); nX++)
	{
		for (int nY = 0; nY < GetHeight(); nY++)
		{
			SetPieceAt(nX, nY, Empty);
		}
	}
}

bool GameBoard::HasPiece(int nX, int nY) const
{
	return GetPieceAt(nX, nY) != Empty;
}

SpotType GameBoard::GetPieceAt(int nX, int nY) const
{
	return m_Board[nX][nY];
}

void GameBoard::SetPieceAt(int nX, int nY, SpotType eType)
{
	m_Board[nX][nY] = eType;
}
