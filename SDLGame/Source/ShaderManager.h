#pragma once
#include "SDL.h"

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"

class ShaderManager
{
public:
	static ShaderManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new ShaderManager();
		}
		return instance;
	}

	void Init();

	void Startup();

	void LoadShaders();

	void Render();

	void Shutdown();

	void JiggleWiggle(float (&array)[6]);

	void LoadShaderFromFile(const char * shaderfile, GLenum type);

private:
	ShaderManager();
	~ShaderManager();

	float m_Max = 1.0f;
	float m_Min = -1.0f;
	GLfloat m_xVal = 0;
	GLfloat m_yVal = 0;

	void ProcessShaderFile(GLuint shader, char *shaderData, GLenum type);
	void LoadVertices();
	void LoadTextures();
	void LoadUVs();

	GLuint programObj;
	GLuint vao;

	GLuint verticesHandle;
	
	GLuint Texture0;
	GLuint Texture1;

	GLuint UVHandle;
	GLint  TextureUniformHandle;
	GLint  TextureUniformHandle1;

	static ShaderManager* instance;
};

