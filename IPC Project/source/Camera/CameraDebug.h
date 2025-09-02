#ifndef CAMERADEBUG_H
#define CAMERADEBUG_H

#include "Camera.h"


class CameraDebug: public Camera{
private:
    glm::mat4 projection;
    void EnableDebug();
public:
    int width, height;
    GLuint yawVBO, pitchVBO, yawVAO, pitchVAO;
    CameraDebug(int width, int height);
    void DrawDebug();
    void Print();
    
};
#define GL_MARKER(msg) \
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0, \
                         GL_DEBUG_SEVERITY_NOTIFICATION, \
                         (GLsizei)std::string(msg).size(), \
                         msg)

#define GL_MARKER_LOCATION() \
    do { \
        std::ostringstream oss; \
        oss << __FILE__ << ":" << __LINE__; \
        std::string locMsg = oss.str(); \
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0, \
                             GL_DEBUG_SEVERITY_NOTIFICATION, \
                             (GLsizei)locMsg.length(), locMsg.c_str()); \
    } while (0)
#endif // !CAMERADEBUG_H