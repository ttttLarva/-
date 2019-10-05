#pragma once
#define SHAPE_NUMS 5
#define COLOR_NUMS 5
class CFood
{
public:
	static char* FoodPool[SHAPE_NUMS];
	static int ColorPool[COLOR_NUMS];
	int m_nRow;
	int m_nCol;
	int m_nShapeID;
	int m_nFoodColorID;
	CFood();
	~CFood();
	void Refresh();
	void Show();
	void Cover();
};

