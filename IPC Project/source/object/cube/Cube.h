#ifndef CUBE_H
#define CUBE_H
#include "./../Object.h"
#include <iostream>
class Cube : public Object
{
public:
    Cube();
    Cube(const char* vertexShader, const char* fragmentShader);
    virtual ~Cube();
    void InitializeBuffers(float* vertices, int size);
    void Draw() const;
};
#endif // !CUBE_H