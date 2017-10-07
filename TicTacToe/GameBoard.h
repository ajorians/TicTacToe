#pragma once

#include <vector>
#include "SpotType.h"

class GameBoard
{
public:
	GameBoard(int nDimension);

	void ClearBoard();

	int GetDimension() const { return (int)m_Board.size(); }
	int GetWidth() const     { return GetDimension(); }
	int GetHeight() const    { return GetDimension(); }

	bool HasPiece(int nX, int nY) const;
	SpotType GetPieceAt(int nX, int nY) const;

	void SetPieceAt(int nX, int nY, SpotType eType);

private:
	std::vector<std::vector<SpotType>> m_Board;
};
