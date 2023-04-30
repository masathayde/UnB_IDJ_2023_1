#include "TileMap.h"
#include <iostream>
#include <fstream>

TileMap::TileMap (GameObject& gameObject, std::string file, TileSet* iTileSet) : Component (gameObject) {
    Load(file);
    tileSet = iTileSet;
}

void TileMap::Load (std::string file) {
    std::ifstream mapFile;
    mapFile.open(file);
    if (!mapFile.is_open()) {
         throw std::runtime_error("Error: Couldn't open file: " + file);
    }
    char comma;
    mapFile >> mapWidth >> comma >> mapHeight >> comma >> mapDepth >> comma;
    int totalTiles = mapWidth * mapHeight * mapDepth;

    for (int i = 0; i < totalTiles; ++i) {
        int tileIdx;
        mapFile >> tileIdx >> comma;
        /* Note que, para o arquivo que usamos na disciplina, tiles vazios são 
        representados por 0, que é o padrão do editor de tilemaps open source TileD. 
        Para o nosso código, é mais conveniente que eles sejam representados por -
        1, e o primeiro tile do tileset por 0. Portanto, subtraia um de cada índice lido 
        do arquivo. */
        tileIdx--;
        tileMatrix.push_back(tileIdx);
    }
    mapFile.close();
}

void TileMap::SetTileSet (TileSet* iTileSet) {
    tileSet = iTileSet;
}

int& TileMap::At (int x, int y, int z) {
    int depthOffset = z * mapWidth * mapHeight;
    int widthOffest = y * mapWidth;
    int position = depthOffset + widthOffest + x;
    return tileMatrix[position];
}

void TileMap::RenderLayer (int layer, int cameraX, int cameraY) {
    for (int y = 0; y < mapHeight; ++y) {
        float tileYpos = (float) y * tileSet->GetTileHeight();
        for (int x = 0; x < mapWidth; ++x) {
            int tileIndex = At(x, y, layer);
            if (tileIndex > -1) {
                float tileXpos = (float) x * tileSet->GetTileWidth();
                tileSet->RenderTile((unsigned) tileIndex, tileXpos, tileYpos);
            }
        }
    }
}

void TileMap::Render () {
    for (int i = 0; i < mapDepth; ++i) {
        RenderLayer(i);
    }
}

void TileMap::Update (float dt) {

}

int TileMap::GetWidth () {
    return mapWidth;
}

int TileMap::GetHeight () {
    return mapHeight;
}

int TileMap::GetDepth () {
    return mapDepth;
}

bool TileMap::Is (std::string type) {
    return type == "TileMap";
}