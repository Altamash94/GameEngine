#ifndef CAMERADEBUG_H
#define CAMERADEBUG_H

#include "Camera.h"
#include "../object/DebugLines/DebugLine.h"

class CameraDebug: public Camera{
private:
    DebugLine Worldlines, cameraOrientationLines;
public:
    int width, height;
    GLuint yawVBO, pitchVBO, yawVAO, pitchVAO;
    CameraDebug(int width, int height);
    virtual ~CameraDebug();
    void DrawDebug();
    void DrawCameraOrientation();
#ifdef DEBUG
    void Print();
#endif
};
#endif // !CAMERADEBUG_H