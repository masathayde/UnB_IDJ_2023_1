#ifndef TILEMAP_H_
#define TILEMAP_H_
#include "Component.h"
#include "TileSet.h"

class TileMap : public Component {
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth {0};
    int mapHeight {0};
    int mapDepth {0};

 public:
    TileMap (GameObject& associated, std::string file, TileSet* tileSet);
    void Load (std::string file);
    void SetTileSet (TileSet* tileSet);
    int& At (int x, int y, int z = 0);
    void RenderLayer (int layer, int cameraX = 0, int cameraY = 0);
    int GetWidth ();
    int GetHeight ();
    int GetDepth ();
    void Render ();
    void Update (float dt);
    bool Is (std::string type);
};

#endif