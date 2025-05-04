#include "header.h"
#include "shader/Shader.h"
#include "textures/Texture.h"
#include "object/cube/Cube.h"

int main(int argc, char* argv[])
{
	if (initializeGLFW() == 0)
	{
		std::cout << "Failed to initialize OpenGL\n";
		return -1;
	}
	//initializeVertexBuffers();

	Shader shader("shader\\shader\\vertexShader.shader", "shader\\shader\\fragmentShader.shader");
	shader.use();
	Texture container(".\\textures\\textures\\container.jpg", "container");
	shader.SetInt("container", 0);
	Texture face(".\\textures\\textures\\awesomeface.png", "face");
	shader.SetInt("face", 1);
	glm::mat4 model, view, projection;
	projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	shader.SetMat4("projection", projection);

	camera = Camera();

	Cube cube;
	cube.SetShader(&shader);
	shader.use();
	cube.AddTexture(&container);
	cube.AddTexture(&face);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	
	while (!glfwWindowShouldClose(window))
	{
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		model = glm::mat4(1.0f);
		view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		projection = glm::mat4(1.0f);
		shader.SetMat4("model", model);
		shader.SetMat4("view", view);

		for (unsigned int i = 0; i < 10; i++)
		{
			float angle = 20.0f * i;
			glm::mat4 model = glm::mat4(1.0f);
			cube.SetModel(glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f), cubePositions[i], glm::vec3(1.0f));
			shader.SetMat4("model", cube.model);
			cube.Draw();
		}
		
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
		std::cout << "FPS: " << 1.0f / deltaTime << std::endl;
	}


	glfwTerminate();
	return 0;
}

int initializeGLFW() 
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW\n";
		return 0;
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return 0;
	}

	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return 1;
}

void CursorPositionCallback(GLFWwindow* window, double  x, double y)
{
	camera.CursorMovement(x, y);
}