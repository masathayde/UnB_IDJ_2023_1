#ifndef RENDERQUEUE_H_
#define RENDERQUEUE_H_
#include "Sprite.h"
#include <vector>

// Meyers Singleton
class RenderQueue {

    RenderQueue ();
    ~RenderQueue ();

    typedef struct {
        Sprite* sprite;
        float x;
        float y;
        float z;
        // For SetClip
        int x_offset;
        int y_offset;
        int tileWidth;
        int tileHeight;
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
    void QueueJob (Sprite* sprtPtr, float x, float y, float z, int xO, int yO, int w, int h);
    void RenderJobs ();
    void QueueCollisionBoxRender (Rect box, float angle);
};

#endif