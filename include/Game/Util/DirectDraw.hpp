#pragma once

#include <JSystem/JGeometry/TMatrix.hpp>
#include <revolution/gx.h>

class JUTTexture;

namespace TDDraw {
    void setViewMtx(MtxPtr);   // TODO: confirm
    void loadViewMtx(MtxPtr);  // TODO: confirm
    void setModelMtx(MtxPtr);  // TODO: confirm
    void resetViewMtx();       // TODO: confirm
    void close();
    void setup(u32, u32, u8);
    void sendPoint(const TVec3f&, u32) NO_INLINE;                                       // TODO: confirm
    void sendPoint(const TVec3f&) NO_INLINE;                                            // TODO: confirm
    void drawLine(const TVec3f&, const TVec3f&, u32);                                   // TODO: confirm
    void drawCircle(const TVec3f&, const TVec3f&, f32, u32, u32);                       // TODO: confirm
    void drawCircle(const TVec3f&, const TVec3f&, const TVec3f&, f32, u32, u32);        // TODO: confirm
    void drawFillCircle(const TVec3f&, f32, u32, u32, u32);                             // TODO: confirm
    void drawFillCircle(const TVec3f&, const TVec3f&, f32, u32, u32);                   // TODO: confirm
    void drawFillFan(const TVec3f&, const TVec3f&, const TVec3f&, u32, f32, f32, u32);  // TODO: confirm
    void drawCylinder(const TVec3f&, const TVec3f&, f32, u32, u32, u32);                // TODO: confirm
    void drawSpherePart(const TPos3f&, f32, f32, f32, f32, f32, u32, u32, u32);         // TODO: confirm
    void drawSphere(const TVec3f&, f32, u32, u32);                                      // TODO: confirm
    void drawSphere3D(TVec3f, f32, u32, u32);                                           // TODO: confirm
    void drawTexture(const TVec2f&, JUTTexture*, const TVec2f&);                        // TODO: confirm
    void drawTexture3D(const TVec3f&, const TVec3f&, const TVec3f&, f32, f32, JUTTexture*, bool, bool);
    void drawFillBox(const TVec3f&, const TVec3f&, u32);                                  // TODO: confirm
    void drawFillBox(const TVec2f&, const TVec2f&, u32);                                  // TODO: confirm
    void drawFillBox3D(const TVec3f&, const TVec3f&, const TVec3f&, const TVec3f&, u32);  // TODO: confirm
    void cameraInit3D();                                                                  // TODO: confirm
    void cameraInit2D();                                                                  // TODO: confirm
    void mixFogColor(TVec3f, f32, u32);                                                   // TODO: confirm
    void tileConversion8(u8*, u32, u32);                                                  // TODO: confirm
    void tileConversion16(u16*, u32, u32);                                                // TODO: confirm
    u32 getTexel32(const JUTTexture*, u32, u32);                                          // TODO: confirm
    u32 getTexel32(const u8*, u32, u32, u32);                                             // TODO: confirm
    void setTexel32(JUTTexture*, u32, u32, u32);                                          // TODO: confirm
    void setTexel32(u8*, u32, u32, u32, u32);                                             // TODO: confirm
    void invProject(TVec3f*, const TVec3f&, MtxPtr, const f32*, const f32*, bool);        // TODO: confirm
    void project2D(TVec3f*, const TVec3f&);                                               // TODO: confirm
    void project2D(TVec2f*, const TVec3f&);                                               // TODO: confirm
    void fix2Dpos(TVec3f*);                                                               // TODO: confirm

    inline void setGXColor(u32 color, GXColor* pColor) NO_INLINE {  // TODO: confirm
        pColor->r = (color >> 24) & 0xFF;
        pColor->g = (color >> 16) & 0xFF;
        pColor->b = (color >> 8) & 0xFF;
        pColor->a = color & 0xFF;
    }
};  // namespace TDDraw
