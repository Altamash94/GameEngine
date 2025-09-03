#ifndef DEBUGLINE_H
#define DEBUGLINE_H
#include "./../Object.h"
#include <iostream>
#include <vector>

struct vertex {
    glm::vec3 Position1;
    glm::vec3 Color1 = glm::vec3(1.0f);
    glm::vec3 Position2;
    glm::vec3 Color2 = glm::vec3(1.0f);
};
class DebugLine : public Object
{
public:
    std::vector<vertex> lines;
    DebugLine();
    ~DebugLine();
    void AddLine(glm::vec3 start, glm::vec3 end, glm::vec3 color = glm::vec3(1.0f));
    void Draw() const;
    void UpdateBuffer();
private:
    void InitializeBuffers(float* vertices, int size);
};
#endif // !DEBUGLINE_H