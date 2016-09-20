#pragma once

#include <string>
#include <GL/glew.h>

class NBaseShader
{
public:
	NBaseShader();
	~NBaseShader();

	GLint GetUniformLocation(const std::string& uniformName);

	virtual void Initialize();
	void LinkShaders();
	void LoadAndCompile(const std::string& vertexShaderPath,
		const std::string& fragmentShaderPath);

	void Use();
	void Unuse();
private:
	void CompileShader(const std::string& filePath, GLuint shader_ID);

protected:
	GLuint mVertexShader_ID;
	GLuint mFragmentShader_ID;
	GLuint mProgramShader_ID;

	int mNumAttributes;

	void AddAttribute(const std::string& attributeName);
	virtual void CreateAttributes() {}
};

