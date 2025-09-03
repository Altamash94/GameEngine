#include "CameraDebug.h"

CameraDebug::CameraDebug(int width, int height):
    Camera(width, height)
{
    Worldlines.AddLine(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // X axis - Red
    Worldlines.AddLine(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Y axis - Green
    Worldlines.AddLine(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Z axis - Blue
    Worldlines.SetCamera(this);

    cameraOrientationLines.AddLine(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // X axis - Red
    cameraOrientationLines.AddLine(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Y axis - Green
    cameraOrientationLines.AddLine(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Z axis - Blue
    cameraOrientationLines.SetCamera(this);
    cameraOrientationLines.space = CAMERA_SPACE;
}


void CameraDebug::Print(){
    GLint boundVAO = -1;
    GLint boundVBO = -1;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundVAO);
    std::cout << "Currently bound VAO: " << boundVAO << std::endl;

    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &boundVBO);
    std::cout << "Currently bound VBO: " << boundVBO << std::endl;
}

void CameraDebug::DrawDebug()
{
    Worldlines.Draw();
}

void CameraDebug::DrawCameraOrientation()
{
    //Worldlines.Draw();
    glm::vec3 start = glm::vec3(0.75f, 0.75f, 0);
    cameraOrientationLines.lines[0].Position1 = start;
    cameraOrientationLines.lines[0].Position2 = start + cameraRight * 0.15f; // Short arrow;
    
    cameraOrientationLines.lines[1].Position1 = start;
    cameraOrientationLines.lines[1].Position2 = start + cameraUp * 0.15f; // Short arrow;
    
    cameraOrientationLines.lines[2].Position1 = start;
    cameraOrientationLines.lines[2].Position2 = start + cameraFront * 0.15f;
    
    cameraOrientationLines.UpdateBuffer();
    cameraOrientationLines.Draw();
}