#ifndef TILESET_H_
#define TILESET_H_
#include <string>
#include "Sprite.h"
#include "GameObject.h"

class TileSet {

    Sprite tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;
    GameObject dummyGO;
    std::string file;

 public:
    TileSet (int tileWidth, int tileHeight, std::string file);
    void RenderTile (unsigned index, float x, float y);
    int GetTileWidth ();
    int GetTileHeight ();
};

#endif