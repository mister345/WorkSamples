#include "TileMap.h"
#include "SpriteState.h"

TileMap::TileMap(const char* map, int mapWidth, 
    int mapHeight, int tileWidth, int tileHeight)
    :
    width(mapWidth),
    height(mapHeight)
    // Load Tile Map from txt file; can also change color of tiles and background here:
{
    Tile::SetWidthAndHeight(tileWidth, tileHeight);
    tiles = new Tile*[mapWidth * mapHeight];
    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            const int i = y* mapWidth + x;
            switch(map[y*mapWidth + x])
            {
                case ' ':
                    tiles[i] = new Tile(x*tileWidth +4, y*tileHeight +4, true, D3DCOLOR_XRGB(0x00, 0x00, 0xE0));
                    break;
                case '#':
                    tiles[i] = new Tile(x*tileWidth, y*tileHeight, false, D3DCOLOR_XRGB(0x90, 0x00, 0x00));
                    break;
                default:
                    tiles[i] = NULL;
                    break;
            }
        }
    }
}

TileMap::~TileMap()
{
    for (int i = 0; i < width * height; i++)
    {
        delete tiles[i];
    }
    delete[] tiles;
}

void TileMap::Draw(Camera& cam) const
{
    for (int i = 0; i < width * height; i++)
    {
        tiles[i]->Draw(cam);
    }
}

void TileMap::GetCRectList(CollisionRectF& cRect, RectFList & list)
{
    for (int iy = Tile::GetIndexYBiasBottom(cRect.top), iyEnd = Tile::GetIndexYBiasTop(cRect.bottom);
    iy <= iyEnd; iy++)
    {
        for (int ix = Tile::GetIndexXBiasRight(cRect.left), ixEnd = Tile::GetIndexXBiasLeft(cRect.right);
        ix <= ixEnd; ix++)
        {
            if (!GetTile(ix, iy)->IsPassable())
            {
                list.push_back(Tile::GetCRect(ix, iy));
            }
        }
    }
}

// ######### //
// WARNING!!!//
// ######### //
//
// Still getting stuck in ceiling when jumping to the RIGHT!
// Despite hypothesis that looping in the opposite direction will fix the problem,
// it DOESN'T. Looping EITHER WAY still gets stuck in the ceiling! ReCheck later.

bool TileMap::GetCRectSingle(CollisionRectF& cRect, CollisionRectF& rectOut)
{
    // JUMPING TO THE RIGHT //

    if (cRect.vx > 0.0f) // CASE 1 ???
    {
        if (cRect.vy < 0.0f)
        {
            for (float iy = Tile::GetIndexYBiasTop(cRect.bottom), iyEnd = Tile::GetIndexYBiasBottom(cRect.top);
            iy >= iyEnd; iy--)
            {
                //for (int ix = Tile::GetIndexXBiasLeft(cRect.right), ixEnd = Tile::GetIndexXBiasRight(cRect.left);
                //ix >= ixEnd; ix--)
                for (float ix = Tile::GetIndexXBiasRight(cRect.left), ixEnd = Tile::GetIndexXBiasLeft(cRect.right);
                ix <= ixEnd; ix++)
                {
                    if (!GetTile(ix, iy)->IsPassable())
                    {
                        rectOut = Tile::GetCRect(ix, iy);
                        return true;
                    }
                }
            }
        }
        else // CASE 2 ???
        {
            for (float iy = Tile::GetIndexYBiasBottom(cRect.top), iyEnd = Tile::GetIndexYBiasTop(cRect.bottom);
            iy <= iyEnd; iy++)
            {
                for (float ix = Tile::GetIndexXBiasRight(cRect.left), ixEnd = Tile::GetIndexXBiasLeft(cRect.right);
                ix <= ixEnd; ix++)
                //for (int ix = Tile::GetIndexXBiasLeft(cRect.right), ixEnd = Tile::GetIndexXBiasRight(cRect.left);
                //ix >= ixEnd; ix--)
                {
                    if (!GetTile(ix, iy)->IsPassable())
                    {
                        rectOut = Tile::GetCRect(ix, iy);
                        return true;
                    }
                }
            }
        }
    }

    // JUMPING TO THE LEFT //

    else // CASE 3 = CORRECT
    {
        if (cRect.vy < 0.0f)
        {
            for (int iy = Tile::GetIndexYBiasTop(cRect.bottom), iyEnd = Tile::GetIndexYBiasBottom(cRect.top);
            iy >= iyEnd; iy--)
            {
                for (int ix = Tile::GetIndexXBiasLeft(cRect.right), ixEnd = Tile::GetIndexXBiasRight(cRect.left);
                ix >= ixEnd; ix--)
                {
                    if (!GetTile(ix, iy)->IsPassable())
                    {
                        rectOut = Tile::GetCRect(ix, iy);
                        return true;
                    }
                }
            }
        }
        else // CASE 4 = CORRECT (?)
        {
            for (int iy = Tile::GetIndexYBiasBottom(cRect.top), iyEnd = Tile::GetIndexYBiasTop(cRect.bottom);
            iy <= iyEnd; iy++)
            {
                for (int ix = Tile::GetIndexXBiasLeft(cRect.right), ixEnd = Tile::GetIndexXBiasRight(cRect.left);
                ix >= ixEnd; ix--)
                {
                    if (!GetTile(ix, iy)->IsPassable())
                    {
                        rectOut = Tile::GetCRect(ix, iy);
                        return true;
                    }
                }
            }
        }
    }
    return false;   // if found no rectangles        
}

void TileMap::DoCollision(Sprite& s)
{
    CollisionRectF rect;
    while (GetCRectSingle(s.GetCRect(), rect))
    {
        s.GetState().OnCollision(rect);
    }
}

void TileMap::DoSupport(Sprite & s)
{
    CollisionRectF cRect = s.GetCRect();
    int iy = Tile::GetIndexYBiasBottom(cRect.bottom); // get 1 below bottom rank

    // loop thru all rectangles below the sprite
    for (int ix = Tile::GetIndexXBiasRight(cRect.left), ixEnd = Tile::GetIndexXBiasLeft(cRect.right);
    ix <= ixEnd; ix++)
    {
        // if solid and standing directly ontop of it
        if (!GetTile(ix,iy)->IsPassable())        {
            return;
        }
    // if don't find at least ONE supporting tile, call event for freefall
        s.GetState().OnUnsupported();
    }
}
