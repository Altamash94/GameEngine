#ifndef CAMERADEBUG_H
#define CAMERADEBUG_H

#include "Camera.h"
#include "../object/DebugLines/DebugLine.h"

class CameraDebug: public Camera{
private:
    glm::mat4 projection;
    DebugLine Worldlines, cameraOrientationLines;
public:
    int width, height;
    GLuint yawVBO, pitchVBO, yawVAO, pitchVAO;
    CameraDebug(int width, int height);
    void DrawDebug();
    void DrawCameraOrientation();
    void Print();
    
};
#endif // !CAMERADEBUG_H