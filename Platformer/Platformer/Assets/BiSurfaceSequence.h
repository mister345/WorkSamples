#pragma once

#include "SurfaceSequence.h"
#include "BiDirection.h"
#include "Camera.h"

class BiSurfaceSequence
{
public:
    // color key here determines which background color will be read as transparent by image loader:
    BiSurfaceSequence(std::wstring basename, unsigned int nSurfaces, unsigned int nHoldFrames,
        int basex, int basey, D3DCOLOR key = D3DCOLOR_XRGB(255, 255, 255))
        :
        rightSeq(new SurfaceSequence(basename, nSurfaces, nHoldFrames, basex, basey, key)),
        leftSeq(rightSeq->CloneMirrored())
    {}
    ~BiSurfaceSequence()
    {
        delete rightSeq;
        delete leftSeq;
    }

    void Draw(int x, int y, BiDirection d, Camera& cam) const
    {
        if (d.IsRight())
        {
            rightSeq->Draw(x, y, cam);
        }
        else if (d.IsLeft())
        {
            leftSeq->Draw(x, y, cam);
        }
    }

    void Advance(BiDirection d)
    {
        if (d.IsRight())
        {
            rightSeq->Advance();
        }
        else if (d.IsLeft())
        {
            leftSeq->Advance();
        }
    }

protected:
    SurfaceSequence* rightSeq;
    SurfaceSequence* leftSeq;
};