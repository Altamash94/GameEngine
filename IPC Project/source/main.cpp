#include "header.h"

int main(int argc, char* argv[])
{
	{
		if (initializeGLFW() == 0){
			std::cout << "Failed to initialize OpenGL\n";
			return -1;
		}
		camera = new CameraDebug(WIDTH, HEIGHT);
		Cube cube;
		
		Shader shader(SHADER_DIR"vertexShader.glsl", SHADER_DIR"fragmentShader.glsl");
		shader.use();
		
		Texture container("source/textures/textures/container.jpg", "container");
		Texture face("source/textures/textures/awesomeface.png", "face");
		shader.SetInt("container", 0);
		shader.SetInt("face", 1);
		shader.SetMat4("projection", camera->GetProjectionMatrix());
		glm::mat4 model;
		cube.SetShader(&shader);
		cube.AddTexture(&container);
		cube.AddTexture(&face);

		
		/**/
		
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
			shader.use();
			shader.SetMat4("view", camera->GetViewMatrix());

			for (unsigned int i = 0; i < 10; i++)
			{
				float angle = 20.0f * i;
				glm::mat4 model = glm::mat4(1.0f);
				cube.SetModel(glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f), cubePositions[i], glm::vec3(1.0f));
				shader.SetMat4("model", cube.model);
				cube.Draw();
			}
			glBindVertexArray(0);
			
			camera->DrawCameraOrientation();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}
	delete camera;
	glfwTerminate();
	return 0;
}

int initializeGLFW() 
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

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

	// Check if we actually have a context
	if (glGetString(GL_VERSION) == nullptr) {
		std::cerr << "No valid OpenGL context!" << std::endl;
	} else {
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL Version: "   << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << "Renderer: "       << glGetString(GL_RENDERER) << std::endl;
		std::cout << "Vendor: "         << glGetString(GL_VENDOR) << std::endl;
	}
	if(!glCreateShader){
		std::cerr << "ERROR: glCreateShader is NULL (GLAD failed)" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return 1;
}

void CursorPositionCallback(GLFWwindow* window, double  x, double y)
{
	camera->CursorMovement(x, y, deltaTime);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    if(width !=0 && height != 0)
		glViewport(0, 0, width, height);
}

