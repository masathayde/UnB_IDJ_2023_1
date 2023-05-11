#include "RenderQueue.h"

RenderQueue::RenderQueue () {

}

RenderQueue::~RenderQueue () {

}

RenderQueue& RenderQueue::GetInstance () {
    static RenderQueue rq;
    return rq;
}

void RenderQueue::QueueJob (Sprite* ptr, float x, float y, float z, int xOffset, int yOffset, int width, int height) {
    renderJob newJob;
    newJob.x = x;
    newJob.y = y;
    newJob.z = z;
    newJob.x_offset = xOffset;
    newJob.y_offset = yOffset;
    newJob.tileWidth = width;
    newJob.tileHeight = height;
    newJob.sprite = ptr;
    jobQueue.push_back(newJob);
}

void RenderQueue::RenderJobs () {
    // Ordenar por valor de z;
    timsort();

    for (auto it : jobQueue) {
        // printf("%f ", it.z);
        it.sprite->SetClip(it.x_offset, it.y_offset, it.tileWidth, it.tileHeight);
        it.sprite->Render(it.x, it.y, it.z);
    }
    // printf("\n\n");
    jobQueue.clear();
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