#ifndef CUBE_H

#include "./../Object.h"
#include <iostream>
class Cube : public Object
{
public:
    Cube();
    ~Cube();
    void InitializeBuffers(float* vertices, int size);
    void Draw() const;
};

#define CUBE_H
#endif // !CUBE_H