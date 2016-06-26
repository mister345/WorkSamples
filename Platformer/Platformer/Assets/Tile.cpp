#include "Tile.h"
int Tile::width;
int Tile::height;

Tile::Tile(int x, int y, bool passable, D3DCOLOR color)
    :
    x(x),
    y(y),
    color(color),
    passable(passable)
{}

Tile::~Tile()
{} 

void Tile::Draw(Camera & cam) const
{
    cam.DrawSolidRect(RectF((float)y, (float)(y + height), (float)x, (float)(x + width)), color);
}