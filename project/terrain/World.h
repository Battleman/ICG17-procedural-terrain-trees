#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>
#include <glm/gtx/hash.hpp>
#include "Chunk.h"
#include "NoiseGen/NoiseGen.h"
#include <list>
#include <functional>

typedef std::unordered_map<glm::i32vec2,Chunk> Chunks;
typedef std::unordered_map<int,Terrain> Terrains;

class World
{
public:
    World(float chunkSize);
    void init();
    void setViewDistance(int chunks);
    void update(float dt,const glm::vec2& worldPos);
    void draw(float time,const glm::mat4& view, const glm::mat4& projection);
private:
    Terrains mTerrains;
    std::list<std::function<void()>> mToDo;
    Chunks mChunks;
    NoiseGen mNoise;
    glm::i32vec2 mPreviousCenter;
    float mChunkSize;
    int mViewDistance;
    long mFrameID;
    int mMaxRes = 1024;
};

#endif // WORLD_H