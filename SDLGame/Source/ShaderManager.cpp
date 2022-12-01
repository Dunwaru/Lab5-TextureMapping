#include "ShaderManager.h"
#include <cstdio>
#include <iostream>
#include "Utils.h"

using namespace std;

ShaderManager* ShaderManager::instance = nullptr;

#define LOG_COMPILE_SHADERS 1

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::Init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glewExperimental = GL_TRUE;
}

// function to call post Init
void ShaderManager::Startup()
{
	programObj = glCreateProgram();
}

void ShaderManager::LoadVertices()
{
	static const GLfloat CubeVB[] = 
	{
		0.0f,-0.0f, 0.9f, // LEFT
		-0.5f,-0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,

		0.0f,-0.0f, 0.9f, // LEFT
		-0.5f, 0.5f, 0.5f,
		0.0f, 1.0f, 0.9f,

		0.5f,-0.5f, 0.5f, // BOTTOM
		0.0f, 0.0f, 0.9f,
		1.0f, 0.0f, 0.9f,

		0.5f, -0.5f, 0.5f, // BOTTOM
		-0.5f,-0.5f, 0.5f,
		0.0f, 0.0f, 0.9f,

		0.5f, 0.5f, 0.5f, // RIGHT
		1.0f,-0.0f, 0.9f,
		1.0f, 1.0f, 0.9f,

		1.0f,-0.0f, 0.9f, //RIGHT
		0.5f, 0.5f, 0.5f,
		0.5f,-0.5f, 0.5f,

		0.5f, 0.5f, 0.5f, // TOP
		1.0f, 1.0f, 0.9f,
		-0.0f, 1.0f,-0.9f,

		0.5f, 0.5f, 0.5f, // TOP
		-0.0f, 1.0f, 0.9f,
		-0.5f, 0.5f, 0.5f,

		0.5f, 0.5f, 0.5f, //FRONT
		-0.5f, 0.5f, 0.5f,
		0.5f,-0.5f, 0.5f,

		-0.5f, 0.5f, 0.5f, // FRONT
		-0.5f,-0.5f, 0.5f,
		0.5f,-0.5f, 0.5f,

		1.0f, 1.0f, 0.9f, // BACK
		-0.0f,-0.0f, 0.9f,
		-0.0f, 1.0f, 0.9f,

		1.0f, 1.0f, 0.9, // BACK
		1.0f,-0.0f, 0.9,
		-0.00f,-0.0f, 0.9,
	};

	glGenBuffers(1, &verticesHandle);
	glBindBuffer(GL_ARRAY_BUFFER, verticesHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVB), CubeVB, GL_STATIC_DRAW);
}

void ShaderManager::LoadUVs()
{
	static const GLfloat uvVB[] = {
		0.00f, 1.0f, // LEFT
		0.00f, 0.66f,
		0.33f, 0.66f,

		0.00f, 1.0f, // LEFT
		0.33f, 0.6f,
		0.33f, 1.0f,

		0.66f, 0.66f, // BOTTOM
		0.33f, 0.33f,
		0.66f, 0.33f,

		0.66f, 0.66f, // BOTTOM
		0.33f, 0.66f,
		0.33f, 0.33f,
		
		0.33f, 0.66f, // RIGHT
		0.66f, 1.0f,
		0.33f, 1.0f,

		0.66f, 1.0f, // RIGHT
		0.33f, 0.66f,
		0.66f, 0.66f,

		0.00f, 0.66f, // TOP
		0.00f, 0.33f,
		0.33f, 0.33f,
		
		0.00f, 0.66f, // TOP
		0.33f, 0.33f,
		0.33f, 0.66f,

		0.67f, 0.33f, // FRONT
		1.00f, 0.33f,
		0.67f, 0.67f,

		1.00f, 0.33f, // FRONT 
		1.0f, 0.67f,
		0.67f, 0.67f,		
		
		1.00f, 1.0f, // BACK
		0.66f, 0.66f,
		1.0f, 0.66f,
		
		1.00f, 1.0f,  // BACK
		0.66f, 1.0f,
		0.66f, 0.66f,
	};

	glGenBuffers(1, &UVHandle);
	glBindBuffer(GL_ARRAY_BUFFER, UVHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvVB), uvVB, GL_STATIC_DRAW);
}

void ShaderManager::LoadTextures()
{
	// create a handle for the texture so openGL has an area allocated to manage all our binary image data.
	glGenTextures(1, &Texture0);

	// now tell OpenGL this is the texture we are currently using for all subsequent texture calls.
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Texture0);

	unsigned int width, height;
	unsigned char* imgData = Utils::loadBMP("Data\\Art\\monke.bmp", width, height);

	// load our texture data up here
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imgData);

	// configure mipmapping levels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	TextureUniformHandle = glGetUniformLocation(programObj, "texture0");


	//////////////////////////////////////////////////////////////////////

	// create a handle for the texture so openGL has an area allocated to manage all our binary image data.
	glGenTextures(1, &Texture1);

	// now tell OpenGL this is the texture we are currently using for all subsequent texture calls.
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, Texture1);
	unsigned char* imgData2 = Utils::loadBMP("Data\\Art\\example.bmp", width, height);

	// load our texture data up here
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imgData2);

	// configure mipmapping levels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	TextureUniformHandle1 = glGetUniformLocation(programObj, "texture1");
}

void ShaderManager::LoadShaderFromFile(const char * shaderfile, GLenum type)
{
	GLuint shaderObj = 0;
	FILE * filePtr;
	
#ifdef LOG_COMPILE_SHADERS
	string newStr = "Source\\Shaders\\glslangValidator.exe ";
	newStr.append(shaderfile);
	cout << newStr.c_str();
	system(newStr.c_str());
#endif

	if (fopen_s(&filePtr, shaderfile, "rb"))
	{
		cout << "error opening shader file: " << shaderfile << endl;
		return;
	}

	fseek(filePtr, 0, SEEK_END);
	int size = ftell(filePtr);
	fseek(filePtr, 0, SEEK_SET);

	char *data = new char[size + 1];

	if (!data)
	{
		cout << "No Data inside shader file: " << shaderfile << endl;
		return;
	}

	fread(data, 1, size, filePtr);
	data[size] = 0;
	fclose(filePtr);

	ProcessShaderFile(shaderObj, data, type);

	delete[] data;
}

void ShaderManager::ProcessShaderFile(GLuint shader, char *shaderData, GLenum type)
{

	shader = glCreateShader(type);

	if (!shader)
	{
		cout << "error creating shader: " << shader << endl;
		return;
	}

	glShaderSource(shader, 1, &shaderData, NULL);
	glCompileShader(shader);
	glAttachShader(programObj, shader);
	glDeleteShader(shader);
}

void ShaderManager::LoadShaders()
{
	LoadShaderFromFile("Source\\Shaders\\Vert.vert" , GL_VERTEX_SHADER);
	LoadShaderFromFile("Source\\Shaders\\Frag.frag" , GL_FRAGMENT_SHADER);

	glLinkProgram(programObj);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	LoadVertices();
	LoadUVs();
	LoadTextures();
}

void ShaderManager::Render()
{
	glUseProgram(programObj);

	//pass in the vertices for our cube
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, verticesHandle);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, UVHandle);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// pass our data to openGL to store for the shaders use.
	glUniform1i(TextureUniformHandle, Texture0);
	glUniform1i(TextureUniformHandle1, Texture1);

	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void ShaderManager::Shutdown()
{
	glDeleteProgram(programObj);
	glDeleteVertexArrays(1, &vao);
}