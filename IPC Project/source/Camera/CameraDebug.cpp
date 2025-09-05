#include "CameraDebug.h"

CameraDebug::CameraDebug(int width, int height):
    Camera(width, height)
{
#ifdef DEBUG
   
    Worldlines.name = std::string("Worldlines");
    Worldlines.AddLine(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // X axis - Red
    Worldlines.AddLine(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Y axis - Green
    Worldlines.AddLine(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Z axis - Blue

    cameraOrientationLines.name = std::string("cameraOrientationLines");
    cameraOrientationLines.AddLine(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // X axis - Red
    cameraOrientationLines.AddLine(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Y axis - Green
    cameraOrientationLines.AddLine(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Z axis - Blue

    Worldlines.space = CAMERA_SPACE;
    cameraOrientationLines.space = CAMERA_SPACE;
#endif
}

std::ostream& operator<<(std::ostream& os, const glm::vec3& v) {
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

#ifdef DEBUG
void CameraDebug::Print(){
    /*
    std::cout << "xyOffSet (" << xOffset << ", " << yOffset << ")" << std::endl;
    std::cout << "RawMousePos: (" << mXPos << ", " << mYPos << ")" << std::endl;
    std::cout << "Yaw: " << yaw << ", Pitch: " << pitch << std::endl;
    std::cout << "cameraFront vector" << cameraFront << std::endl;
    std::cout << "cameraRight vector" << cameraRight << std::endl;
    std::cout << "cameraUp vector" << cameraUp << std::endl;
    std::cout << std::endl;
    */
}
#endif

void CameraDebug::DrawDebug()
{
    Worldlines.Draw();
}

void CameraDebug::DrawCameraOrientation()
{

#ifdef DEBUG
    glm::vec3 start = glm::vec3(0.75f, 0.75f, 0);
    cameraOrientationLines.lines[0].Position = start;
    cameraOrientationLines.lines[1].Position = start + cameraRight * 0.15f; // Short arrow;
    
    cameraOrientationLines.lines[2].Position = start;
    cameraOrientationLines.lines[3].Position = start + cameraUp * 0.15f; // Short arrow;
    
    cameraOrientationLines.lines[4].Position = start;
    cameraOrientationLines.lines[5].Position = start + cameraFront * 0.15f;
    
    cameraOrientationLines.UpdateBuffer();
    cameraOrientationLines.Draw();
    Print();
#endif
}

CameraDebug::~CameraDebug()
{
    std::cout << "Deleting CameraDebug" << std::endl;
}