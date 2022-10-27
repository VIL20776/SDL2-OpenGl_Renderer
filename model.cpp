#include "model.hpp"

#include <SOIL/SOIL.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/matrix.hpp>

Model::Model (std::vector<GLfloat> data)
{
    this->data = data;
        
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    
    position = {0, 0, 0};
    rotation = {0, 0, 0};
    scale = {1, 1, 1};
    
    
    makeModelMatrix();
}
    
Model::Model (std::vector<float> data, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->data = data;
        
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    
    makeModelMatrix();
}
    
Model::Model(Obj object, const char* texture_path, ModelProps props)
{
    createVertexBuffer(object);
    
    position = props.position;
    rotation = props.rotation;
    scale = props.scale;
    
    textureData = SOIL_load_image(texture_path, &t_width, &t_height, 0, SOIL_LOAD_RGB);
    glGenTextures(1, &texture);
    
    makeModelMatrix();
}
    
void Model::createVertexBuffer(Obj &object)
{
	std::vector<GLfloat> buffer {};
	polyCount = 0;
	for (auto &face : object.getFaces()) {
		polyCount += 1;
		bool extraPoly = false;
		for (char i = 0; i < face.size(); i++) {
			if (i == 3 && !extraPoly) {
				extraPoly = true;
				polyCount += 1;
				i = 0;
			}
			
			if (i == 1 && extraPoly)
				continue;
			
			std::vector<float> pos = object.getVertexes()[face[i][0] - 1];
			buffer.push_back(pos.at(0));
			buffer.push_back(pos.at(1));
			buffer.push_back(pos.at(2));
			
			std::vector<float> uvs = object.getTextCoords()[face[i][1] - 1];
			buffer.push_back(uvs.at(0));
			buffer.push_back(uvs.at(1));
			
			std::vector<float> norm = object.getNormals()[face[i][2] - 1];
			buffer.push_back(norm.at(0));
			buffer.push_back(norm.at(1));
			buffer.push_back(norm.at(2));
		}
	}
	
	data = buffer;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
}
    
void Model::makeModelMatrix()
{
	using glm::mat4;
	
	mat4 identity = glm::mat4(1);
	mat4 translateMat = glm::translate(identity, position);
	
	mat4 pitch = glm::rotate(identity, glm::radians(rotation.x), {1, 0, 0});
	mat4 yaw = glm::rotate(identity, glm::radians(rotation.y), {0, 1, 0});
	mat4 roll = glm::rotate(identity, glm::radians(rotation.z), {0, 0, 1});
	
	mat4 rotationMat = pitch * yaw * roll;
	
	mat4 scaleMat = glm::scale(identity, scale);	

	modelMatrix = translateMat * rotationMat * scaleMat;
}
    
void Model::render(const GLuint &shaderID)
{
	if (shaderID != 0)
		glUniformMatrix4fv(glGetUniformLocation(shaderID, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    
    glBindVertexArray(vao);    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * data.size()), data.data(), GL_STATIC_DRAW);
        
    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
        
    // Texture Coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
         
    // Normals
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (5 * sizeof(float)));
    glEnableVertexAttribArray(2);       
    
    // Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glDrawArrays(GL_TRIANGLES, 0, polyCount * 3);
        
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}