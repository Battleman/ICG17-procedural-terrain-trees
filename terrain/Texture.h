#ifndef TEXTURE_H
#define TEXTURE_H

#include <icg_helper.h>
#include <memory>
#include <cmath>
#include <iostream>

/**
 * @brief The Texture class destroy automatically the texture
 */
class GCTexture {
public:
    GCTexture(GLuint tex, int w, int h) : mID(tex), mW(w),mH(h) {
        mVals.resize(w*h,0);
    }
    GCTexture(const GCTexture& other) = delete;
    GCTexture& operator=(const GCTexture& other) = delete;
    GLuint id() const {return mID;}
    float* data() {return mVals.data();}
    float valAt(float x, float y) {
        int ix = x;
        int iy = y;
        float tx = fract(x);
        float ty = fract(y);
        float xv = val(ix,iy)*(1-tx)+val(ix+1,iy)*tx;
        float xv2 = val(ix,iy+1)*(1-tx)+val(ix+1,iy+1)*tx;
        float h = xv*(1-ty)+xv2*ty;
        return h;
    }
    int res() { return mW;}
    float val(int x, int y) {
        using std::min;
        using std::max;
        x = max(0,min(mW-1,x));
        y = max(0,min(mH-1,y));
        return mVals.at(y*mW+x); //TODO check if this correspond to GL
    }

    ~GCTexture() {
        glDeleteTextures(1,&mID);
    }
private:
    std::vector<float> mVals;
    int mW;
    int mH;
private:
    GLuint mID;
};


class SharedTexture : public shared_ptr<GCTexture> {
public:
    SharedTexture(GLuint tex, size_t w, size_t h) : shared_ptr(new GCTexture(tex,w,h)) {}
    SharedTexture(GCTexture* tex = nullptr) : shared_ptr(tex) {}
    operator GLuint() {return this->get()->id();}
};

#endif // TEXTURE_H
