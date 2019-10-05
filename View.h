#pragma once

#define SetConsoleColor( f , b ) ( ( f ) + ( ( b ) << 0x04 ) )

void MoveCursorTo(int nRow, int nCol);
void SetColor(int b);
