#include "header.h"
int main(int argc, char* argv[])
{
	{
		if (initializeGLFW() == 0){
			std::cout << "Failed to initialize OpenGL\n";
			return -1;
		}
		camera = std::make_shared<CameraDebug>(WIDTH, HEIGHT);
		
		Cube cube(SHADER_DIR"vertexShader.glsl", SHADER_DIR"fragmentShader.glsl");
		cube.AddTexture("source/textures/textures/container.jpg", "container", 0);
		cube.AddTexture("source/textures/textures/awesomeface.png", "face", 1);
		cube.SetCamera(camera);
		
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (!glfwWindowShouldClose(window))
		{
			double currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			processInput(window);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (unsigned int i = 0; i < 10; i++)
			{
				float angle = 20.0f * i;
				cube.SetModel(glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f), cubePositions[i], glm::vec3(1.0f));
				cube.Draw();
			}
			glBindVertexArray(0);
			
			camera->DrawCameraOrientation();
			//camera->DrawDebug();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}
	camera.reset(); 
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

	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
    	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
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

void processInput(GLFWwindow* window)
{
    double cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->Move(Camera::MoveDirection::FRONT, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->Move(Camera::MoveDirection::BACK, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->Move(Camera::MoveDirection::LEFT, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->Move(Camera::MoveDirection::RIGHT, cameraSpeed);
}