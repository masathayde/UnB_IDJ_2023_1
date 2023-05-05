#include "TileSet.h"
#include "RenderQueue.h"

TileSet::TileSet (int inTileWidth, int inTileHeight, std::string ifile) : tileSet(dummyGO, ifile) {
    tileWidth = inTileWidth;
    tileHeight = inTileHeight;
    file = ifile;
    rows = tileSet.GetHeight() / tileHeight;
    columns = tileSet.GetWidth() / tileWidth;
}

void TileSet::RenderTile (unsigned index, float x, float y, float z) {
    unsigned numOfTiles = tileHeight * tileWidth;
    // Checa se o índice é válido.
    if (index >= numOfTiles) {
        throw std::runtime_error("Error: Invalid tileset index: " + std::to_string(index) + "\nTileset at: " + file);
    }
    int x_offset = (index % columns) * tileWidth;
    int y_offset = (index / columns) * tileHeight;
    // tileSet.SetClip(x_offset, y_offset, tileWidth, tileHeight);
    // tileSet.Render(x, y);
    RenderQueue& rq = RenderQueue::GetInstance();
    rq.QueueJob(&tileSet, x, y, z, x_offset, y_offset, tileWidth, tileHeight);
}

int TileSet::GetTileHeight () {
    return tileHeight;
}

int TileSet::GetTileWidth () {
    return tileWidth;
}