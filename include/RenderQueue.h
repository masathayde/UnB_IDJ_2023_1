#ifndef RENDERQUEUE_H_
#define RENDERQUEUE_H_
#include <vector>
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Vec2.h"
#include "Rect.h"

// Meyers Singleton
class RenderQueue {

    RenderQueue ();
    ~RenderQueue ();

    typedef struct {
        SDL_Texture* texture;
        float x;
        float y;
        float z;
        // For SetClip
        int x_offset;
        int y_offset;
        int tileWidth;
        int tileHeight;
        Vec2 scale;
        float angleDeg;
    } renderJob;

    typedef struct {
        Rect box;
        float angle;
    } CollisionBoxJob;

    std::vector<renderJob> jobQueue;
    void insertionSort (std::vector<renderJob>& arr, int left, int right);
    void merge (std::vector<renderJob>& arr, int left, int mid, int right);
    void timsort ();

    std::vector<CollisionBoxJob> collisionBoxes;
    void RenderCollisionBox (Rect box, float angle);

 public:
    static RenderQueue& GetInstance ();
    void QueueJob (SDL_Texture* sprtPtr, float x, float y, float z, int xO, int yO, int w, int h, float angleDeg = 0, Vec2 scale = Vec2(1,1));
    void RenderJobs ();
    void QueueCollisionBoxRender (Rect box, float angle);
};

#endif