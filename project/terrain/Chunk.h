#ifndef CHUNK_H
#define CHUNK_H

#include <glm/vec2.hpp>
#include "Grid/Grid.h"
#include "ScalarFrameBuffer.h"

#include "NoiseGen/NoiseGen.h"
class Chunk
{
public:
    Chunk(const glm::vec2& offset, const glm::vec2& size);
    int update(int res, const NoiseGen &noise, const Grid& terrain, const Grid& water);
    void drawTerrain(float time, const glm::mat4 &view, const glm::mat4 &projection);
    void drawWater(float time, const glm::mat4 &view, const glm::mat4 &projection);
    void setFrameID(long id);
    long frameID() { return mFrameId;}
    const glm::vec2& pos() const {return mOffset;}
    ~Chunk();
private:
    bool mReady;
    GLuint mHmap;
    ScalarFrameBuffer mNoiseBuffer;
    const Grid* mTerrain;
    const Grid* mWater;
    long mFrameId;
    int mRes;
    glm::vec2 mOffset;
    glm::vec2 mSize;
};

#endif // CHUNK_H
