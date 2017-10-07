#pragma once

struct SDL_Rect;

class DisplayMetrics
{
public:
	DisplayMetrics(int width, int height);

	int GetGameAreaWidth() const;
	int GetGameAreaHeight() const;
	int GetGameAreaTop() const;
	int GetGameAreaLeft() const;

	int GetColumnWidth(int boardDimension) const;
	int GetRowHeight(int boardDimension) const;

	SDL_Rect GetSpotRect(int boardDimension, int x, int y) const;
	bool GetSpot(int boardDimension, int x, int y, int& nX, int& nY) const;

	int GetNumLines(int boardDimension) const;

private:
	int m_nWidth;
	int m_nHeight;
};
