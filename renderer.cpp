#include "renderer.hpp"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/matrix.hpp>
#include <sstream>
#include <string>

Renderer::Renderer(int width, int height)
{
    this->width = width;
    this->height = height;
    
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    
    activeShader = 0;
    scene = {};
    
    camPosition = {0, 0, 0};
    camRotation = {0, 0, 0};
    
    makeViewMatrix();
    projectionMatrix = glm::perspective(glm::radians(60.f), (float) width / height, 0.1f, 1000.f);
}

void Renderer::update()
{
	makeViewMatrix();
	
}

void Renderer::makeViewMatrix()
{
	using glm::mat4;
	
	mat4 identity = glm::mat4(1);
	mat4 translateMat = glm::translate(identity, camPosition);
	
	mat4 pitch = glm::rotate(identity, glm::radians(camRotation.x), {1, 0, 0});
	mat4 yaw = glm::rotate(identity, glm::radians(camRotation.y), {0, 1, 0});
	mat4 roll = glm::rotate(identity, glm::radians(camRotation.z), {0, 0, 1});
	
	mat4 rotationMat = pitch * yaw * roll;
	
	mat4 camMatrix = translateMat * rotationMat;
	
	viewMatrix = glm::inverse(camMatrix);
}

int Renderer::loadShaders(const char *vertex_shader_path, const char *fragment_shader_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream (vertex_shader_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_shader_path);
		getchar();
		return 1;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_shader_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_shader_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_shader_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	this->activeShader = ProgramID;
	return 0;
}

void Renderer::addModel(Model obj)
{
	scene.push_back(obj);
}

void Renderer::render()
{
	glClearColor(0.2, 0.2, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (activeShader != 0)
		glUseProgram(activeShader);
		
	glUniformMatrix4fv(glGetUniformLocation(activeShader, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	
	glUniformMatrix4fv(glGetUniformLocation(activeShader, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
	glUniform1i(glGetUniformLocation(activeShader, "tex"), 0);

	glUniform3fv(glGetUniformLocation(activeShader, "pointLight"), 1, glm::value_ptr(pointLight));
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	for (auto &obj : scene)
		obj.render(activeShader);
}
