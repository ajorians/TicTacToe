#include "DisplayMetrics.h"
#include <SDL.h>

DisplayMetrics::DisplayMetrics(int width, int height)
	: m_nWidth(width), m_nHeight(height)
{

}

int DisplayMetrics::GetGameAreaWidth() const
{
	return m_nWidth - (GetGameAreaLeft() * 2);
}

int DisplayMetrics::GetGameAreaHeight() const
{
	return m_nHeight - (GetGameAreaTop() * 2);
}

int DisplayMetrics::GetGameAreaTop() const
{
	return 80;
}

int DisplayMetrics::GetGameAreaLeft() const
{
	return 80;
}

int DisplayMetrics::GetColumnWidth(int boardDimension) const
{
	return GetGameAreaWidth() / boardDimension;
}

int DisplayMetrics::GetRowHeight(int boardDimension) const
{
	return GetGameAreaHeight() / boardDimension;
}

SDL_Rect DisplayMetrics::GetSpotRect(int boardDimension, int x, int y) const
{
	SDL_Rect r = { 
		x*GetColumnWidth(boardDimension) + GetGameAreaLeft(), 
		y*GetRowHeight(boardDimension) + GetGameAreaTop(),
		GetColumnWidth(boardDimension),
		GetRowHeight(boardDimension)
	};

	return r;
}

bool DisplayMetrics::GetSpot(int boardDimension, int x, int y, int& nX, int& nY) const
{
	if (x > GetGameAreaLeft() &&
		x < (GetGameAreaLeft() + GetGameAreaWidth()) &&
		y > GetGameAreaTop() &&
		y < (GetGameAreaTop() + GetGameAreaHeight())
		)
	{
		x -= GetGameAreaLeft();
		y -= GetGameAreaTop();

		nX = x / GetColumnWidth(boardDimension);
		nY = y / GetRowHeight(boardDimension);
		return true;
	}

	return false;
}

int DisplayMetrics::GetNumLines(int boardDimension) const
{
	return boardDimension - 1;
}

