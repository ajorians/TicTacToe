#pragma once

class GameBoard;
enum SpotType;

class GameLogic
{
public:
	GameLogic(GameBoard& board);

	void ResetGame();
	void PlaceNextPiece(int x, int y);
	bool IsGameOver() const;

private:
	GameBoard& m_Board;
	SpotType m_CurrentTurn;
};
