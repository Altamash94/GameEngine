#include "CameraDebug.h"
#ifndef SHADER_DIR
#define SHADER_DIR "/home/altamash/Documents/CMakeTest/build/install/bin/shader/"
#endif
CameraDebug::CameraDebug(int width, int height):
    width(width), 
    height(height)
    {
    
    float aspect = (float)width / (float)height;
    float fovy = glm::radians(45.0f);
    projection = glm::perspective(fovy, aspect, 0.1f, 100.0f);

    glGenVertexArrays(1, &yawVAO);
    glGenBuffers(1, &yawVBO);

    glBindVertexArray(yawVAO);
    glBindBuffer(GL_ARRAY_BUFFER, yawVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, nullptr, GL_DYNAMIC_DRAW); // 2 vec3s

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // --- Pitch Line ---
    glGenVertexArrays(1, &pitchVAO);
    glGenBuffers(1, &pitchVBO);

    glBindVertexArray(pitchVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pitchVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, nullptr, GL_DYNAMIC_DRAW); // 2 vec3s

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void CameraDebug::Print(){
    GLint boundVAO = -1;
    GLint boundVBO = -1;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundVAO);
    std::cout << "Currently bound VAO: " << boundVAO << std::endl;

    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &boundVBO);
    std::cout << "Currently bound VBO: " << boundVBO << std::endl;

    
}

void CameraDebug::DrawDebug(){
    /*
    glm::mat4 view = GetViewMatrix();
    glm::vec3 start = position;

    // Normalize cameraFront for safety
    glm::vec3 forward = glm::normalize(cameraFront);

    // Yaw Vector: project cameraFront onto XZ plane
    glm::vec3 yawDir = glm::normalize(glm::vec3(forward.x, 0.0f, forward.z));
    glm::vec3 yawEnd = start + yawDir * 15.0f;

    // Pitch Vector: pitch direction (Y axis only for simplicity)
    glm::vec3 pitchDir = glm::normalize(glm::vec3(0.0f, forward.y, 0.0f));
    glm::vec3 pitchEnd = start + pitchDir * 15.0f;

    // Line 1: Yaw (Red)
    float yawLineVertices[] = {
        0,0,0,0,0,-2.0f
        //start.x, start.y, start.z,
        //yawEnd.x, yawEnd.y, yawEnd.z
    };

    // Line 2: Pitch (Green)
    float pitchLineVertices[] = {
        0,0,0,0,0,-2.0f
        //start.x, start.y, start.z,
        //pitchEnd.x, pitchEnd.y, pitchEnd.z
    };

    // Upload yaw line
    glBindBuffer(GL_ARRAY_BUFFER, yawVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(yawLineVertices), yawLineVertices);

    // Upload pitch line
    glBindBuffer(GL_ARRAY_BUFFER, pitchVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pitchLineVertices), pitchLineVertices);

    debugShader.use();
    // Set shader and matrices
    debugShader.SetMat4("view", view);
    debugShader.SetMat4("projection", projection);
    // Draw Yaw Line (Red)
    debugShader.SetVec3("mcolor", glm::vec3(1.0f, 0.0f, 0.0f)); // Red
    glBindVertexArray(yawVAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);

    // Draw Pitch Line (Green)
    debugShader.SetVec3("mcolor", glm::vec3(0.0f, 1.0f, 0.0f)); // Green
    glBindVertexArray(pitchVAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
    */
    // Simple identity view matrix
    glm::mat4 view = glm::mat4(1.0f);

    // Optional: orthographic projection for debugging (or stick with your current one)
    //glm::mat4 projection = 
    //glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.1f, 100.0f);

    // Line vertices: from (0, 0, 0) to (0, 0, -1)
    float yx = sin(glm::radians(yaw));
    float yy = cos(glm::radians(yaw));
    float px = sin(glm::radians(pitch));
    float py = cos(glm::radians(pitch));
    std::cout << yx << " " << yy << std::endl; 
    std::cout << px << " " << py << std::endl; 
    float lineVertices[] = {
        0, 0, 1.0f,
        yx * yy, px * py, 1.0f
    };

    // Upload line data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, yawVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(lineVertices), lineVertices);

    // Use shader
    debugShader.use();
    debugShader.SetMat4("view", glm::mat4(1.0f));
    debugShader.SetMat4("projection", glm::mat4(1.0f));
    debugShader.SetVec3("mcolor", glm::vec3(1.0f)); // Red

    // Draw line
    glBindVertexArray(yawVAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}

void APIENTRY openglCallbackFunction(GLenum source,
                                     GLenum type,
                                     GLuint id,
                                     GLenum severity,
                                     GLsizei length,
                                     const GLchar* message,
                                     const void* userParam) {
    std::cerr << "----- OpenGL Debug Message -----" << std::endl;
    std::cerr << "Message: " << message << std::endl;

    std::cerr << "Source: ";
    switch (source) {
        case GL_DEBUG_SOURCE_API:             std::cerr << "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cerr << "Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cerr << "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cerr << "Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cerr << "Other"; break;
    }
    std::cerr << std::endl;

    std::cerr << "Type: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:               std::cerr << "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cerr << "Deprecated Behavior"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cerr << "Undefined Behavior"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cerr << "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cerr << "Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cerr << "Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cerr << "Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cerr << "Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cerr << "Other"; break;
    }
    std::cerr << std::endl;

    std::cerr << "Severity: ";
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         std::cerr << "High"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cerr << "Medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cerr << "Low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cerr << "Notification"; break;
    }
    std::cerr << std::endl;
    std::cerr << "-------------------------------" << std::endl;
}


void CameraDebug::EnableDebug(){
	int flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(openglCallbackFunction, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE,
							0, nullptr, GL_TRUE);
	}
	const char* msg = "Sanity check message!";
	glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, 
						GL_DEBUG_TYPE_MARKER,
						42, // Arbitrary ID
						GL_DEBUG_SEVERITY_HIGH,
						(GLsizei)strlen(msg),
						msg);

    if (glDebugMessageCallback == nullptr) {
		std::cerr << "glDebugMessageCallback is nullptr — glad did not load it." << std::endl;
	} else {
		std::cout << "glDebugMessageCallback loaded successfully!" << std::endl;
	}

}