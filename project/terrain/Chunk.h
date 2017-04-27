#ifndef CHUNK_H
#define CHUNK_H

#include <glm/vec2.hpp>
#include "Grid/Grid.h"
#include "ScalarFrameBuffer.h"

#include "ScreenQuad/ScreenQuad.h"
#include "TexGenerator.h"

class Chunk
{
public:
    Chunk(const glm::vec2& offset, const glm::vec2& size);
    void update(float delta_s);
    int updateRes(int res, TexGenerator &texGen, const Grid& terrain, const Grid& water, const Grid& grass);
    void drawTerrain(float time, const glm::mat4 &view, const glm::mat4 &projection);
    void drawGrass(float time, const glm::mat4 &view, const glm::mat4 &projection);
    void drawWater(float time, const glm::mat4 &view, const glm::mat4 &projection);
    void setFrameID(long id);
    long frameID() { return mFrameId;}
    const glm::vec2& pos() const {return mOffset;}
    ~Chunk();
private:
    float mAlpha;
    bool mReady;
    GLuint mHmap;
    GLuint mNextHmap;
    float mTTime;
    ScalarFrameBuffer mNoiseBuffer;
    const Grid* mTerrain;
    const Grid* mWater;
    const Grid* mGrass;
    long mFrameId;
    int mRes;
    glm::vec2 mOffset;
    glm::vec2 mSize;

    TexGenerator::Job* mTexJob;
    TexFuture mTexFuture;
    int mNextRes;
    const Grid* mNextTerrain;
    const Grid* mNextWater;
    const Grid* mNextGrass;

};

#endif // CHUNK_H
