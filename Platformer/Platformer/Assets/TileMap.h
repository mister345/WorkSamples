#pragma once
#include "Tile.h"
//#include "Rect.h"
#include "RectF.h"
#include "RectI.h"
#include "Sprite.h"
#include "Camera.h"

class TileMap
{
public:
    TileMap(const char* map, int mapWidth,
        int mapHeight, int tileWidth, int tileHeight);
    ~TileMap();
    void Draw(Camera& cam) const;
    // fill list with colliding rectangles
    void GetCRectList(CollisionRectF& cRect, RectFList& list);
    bool GetCRectSingle(CollisionRectF& cRect, CollisionRectF & rectOut);
    void DoCollision(Sprite& s);
    void DoSupport(Sprite& s);
    RectF GetBoundaries() const
    {
        return RectF(0.0f, height * Tile::GetHeight(), 0.0f, width * Tile::GetWidth());
    }

private:
    Tile* GetTile(int ix, int iy) const
    {
        return tiles[ix + width*iy];
    }

private:
    Tile** tiles;
    const int width;
    const int height;
};
