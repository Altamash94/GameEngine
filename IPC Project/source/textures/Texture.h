#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"


class Texture
{
public:
	Texture(const char* path, const char* name);
	~Texture();
	const char* name;
	void Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
private:
	unsigned int textureID;
	int width, height, nrChannels;
	unsigned char* data;
};
#endif // !TEXTURE_H