#include "renderer.hpp"

#include <ctime>
#include <fstream>
#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/matrix.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

Renderer::Renderer(std::shared_ptr<Scene> scene, int width, int height)
{
    this->width = width;
    this->height = height;
	this->scene = scene;
    
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);

	pointLight = {0, 0, 0};

	projectionMatrix = glm::perspective(glm::radians(60.f), (float) width / height, 0.1f, 1000.f);
	startupTime = std::clock();
}

void Renderer::update()
{
	viewMatrix = scene->shareCamera()->createViewMatrix();
	activeShader = scene->getActiveShader();
	models = scene->getSceneModels();
}

void Renderer::render()
{
	glClearColor(0.2, 0.2, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Shader Setup
	if (activeShader != 0)
		glUseProgram(activeShader);
		
	glUniformMatrix4fv(glGetUniformLocation(activeShader, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(activeShader, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniform1i(glGetUniformLocation(activeShader, "tex"), 0);
	float time = 1000 * float(std::clock() - startupTime) / CLOCKS_PER_SEC;
	glUniform1f(glGetUniformLocation(activeShader, "time"), time);
	glUniform3fv(glGetUniformLocation(activeShader, "pointLight"), 1, glm::value_ptr(pointLight));
	glUniform3fv(glGetUniformLocation(activeShader, "forward"), 1, glm::value_ptr(scene->shareCamera()->getForwardv()));
	
	// General Texture Setings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	Model model = scene->getActiveModel();
	model.loadTexture();
	model.render(activeShader);
}