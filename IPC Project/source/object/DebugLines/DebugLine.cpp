#include "DebugLine.h"

DebugLine::DebugLine(): Object(SHADER_DIR"lineVertex.glsl", SHADER_DIR"lineFragment.glsl")
{
    InitializeBuffers(nullptr, 0);
}

void DebugLine::AddLine(glm::vec3 start, glm::vec3 end, glm::vec3 color)
{
    vertex line;
    line.Position = start;
    line.Color = color;
    lines.push_back(line);
    line.Position = end;
    line.Color = color;
    lines.push_back(line);
    UpdateBuffer();
}

void DebugLine::UpdateBuffer(){
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(vertex), lines.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DebugLine::InitializeBuffers(float*, int)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(vertex), lines.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Line color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void DebugLine::Draw() const
{
    if(lines.size() == 0)
        return;
    shader->use();
    switch(space){
        case WORLD_SPACE:
            //shader->SetMat4("view", camera->GetViewMatrix());
            //shader->SetMat4("projection", camera->GetProjectionMatrix());
            break;
        case VIEW_SPACE:
            //shader->SetMat4("view", camera->GetViewMatrix());
            //shader->SetMat4("projection", camera->GetProjectionMatrix());
            break;
        case CAMERA_SPACE:
            shader->SetMat4("view", glm::mat4(1.0f));
            shader->SetMat4("projection", glm::mat4(1.0f));
            break;
    }
    shader->SetMat4("model", glm::mat4(1.0f));
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, lines.size());
    glBindVertexArray(0);
}

DebugLine::~DebugLine()
{
    std::cout << "Deleting object debugLine " << name << std::endl;
}