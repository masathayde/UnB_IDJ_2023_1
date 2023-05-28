#include "RenderQueue.h"
#include "Camera.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

RenderQueue::RenderQueue () {

}

RenderQueue::~RenderQueue () {

}

RenderQueue& RenderQueue::GetInstance () {
    static RenderQueue rq;
    return rq;
}

void RenderQueue::QueueJob (SDL_Texture* texture, float x, float y, float z, int xOffset, int yOffset, int width, int height, float angleDeg, Vec2 scale) {
    renderJob newJob;
    newJob.x = x;
    newJob.y = y;
    newJob.z = z;
    newJob.x_offset = xOffset;
    newJob.y_offset = yOffset;
    newJob.tileWidth = width;
    newJob.tileHeight = height;
    newJob.scale = scale;
    newJob.texture = texture;
    newJob.angleDeg = angleDeg;
    jobQueue.push_back(newJob);
}

void RenderQueue::RenderJobs () {
    // Ordenar por valor de z;
    timsort();

    SDL_Rect dstRect;
    SDL_Rect clipRect;
    Camera camera;
    for (auto it : jobQueue) {

        // it.sprite->SetClip(it.x_offset, it.y_offset, it.tileWidth, it.tileHeight);
        // it.sprite->Render(it.x, it.y, it.z);
        clipRect.x = it.x_offset;
        clipRect.y = it.y_offset;
        clipRect.w = it.tileWidth;
        clipRect.h = it.tileHeight;

        dstRect.x = round(it.x - camera.pos.x);
        dstRect.y = round(it.y - camera.pos.y);
        dstRect.w = clipRect.w * it.scale.x;
        dstRect.h = clipRect.h * it.scale.y;
        int status = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), it.texture, &clipRect, &dstRect, it.angleDeg, nullptr, SDL_FLIP_NONE);
        if (status != 0) {
            std::string errormsg(SDL_GetError());
            throw std::runtime_error("Error: SDL_RenderCopy failed with code " + std::to_string(status) + "\nError message from SDL_GetError(): " + errormsg);
        }
        // status = SDL_RenderDrawRect(Game::GetInstance().GetRenderer(), &dstRect);
    }
    jobQueue.clear();

    #ifdef DEBUG
    for (auto job : collisionBoxes) {
        RenderCollisionBox(job.box, job.angle);
    }
    collisionBoxes.clear();
    #endif
}

// Orderna baseado em valor Z
void RenderQueue::insertionSort(std::vector<renderJob>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        renderJob temp = arr[i];
        int j = i - 1;
        while (j >= left && temp.z < arr[j].z) {
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = temp;
    }
}

void RenderQueue::merge (std::vector<renderJob>& arr, int left, int mid, int right) {
    int len1 = mid - left + 1;
    int len2 = right - mid;
    std::vector<renderJob> leftArr, rightArr;
    for (int i = 0; i < len1; ++i) {
        leftArr.push_back(arr[left+i]);
    }
    for (int i = 0; i < len2; ++i) {
        rightArr.push_back(arr[mid + 1 + i]);
    }

    int i {0};
    int j {0};

    for (int k = left; k <= right; ++k) {
        if (i < len1 && (j >= len2 || leftArr[i].z <= rightArr[j].z)) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
    }
}

void RenderQueue::timsort () {

    const int runS = 32;

    for (int i = 0; i < (int) jobQueue.size(); i+=runS) {
        insertionSort (jobQueue, i, std::min(i + runS - 1, (int) jobQueue.size() - 1));
    }

    for (int n = runS; n < (int) jobQueue.size(); n = 2 * n) {

        for (int sIdx = 0; sIdx < (int) jobQueue.size(); sIdx = sIdx + 2*n) {
            int mid = sIdx + n - 1;
            int endIdx = std::min(sIdx + 2*n - 1, (int) jobQueue.size() -1);
            if (mid < endIdx) {
                merge(jobQueue, sIdx, mid, endIdx);
            }
        }
    }
}

void RenderQueue::RenderCollisionBox (Rect box, float angle) {
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).GetRotated( angle)
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).GetRotated( angle )
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated( angle )
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).GetRotated( angle )
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
}

void RenderQueue::QueueCollisionBoxRender (Rect box, float angle) {
    CollisionBoxJob job;
    job.box = box;
    job.angle = angle;
    collisionBoxes.push_back(job);
}