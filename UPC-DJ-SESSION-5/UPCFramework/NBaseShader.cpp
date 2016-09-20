#include "NBaseShader.h"
#include "FatalError.h"

#include <fstream>
#include <vector>

NBaseShader::NBaseShader() :
	mProgramShader_ID(0),
	mVertexShader_ID(0),
	mFragmentShader_ID(0),
	mNumAttributes(0)
{
}

NBaseShader::~NBaseShader()
{
}

void NBaseShader::Initialize() {
	CreateAttributes();
}

void NBaseShader::Use() {
	glUseProgram(mProgramShader_ID);

	for (int i = 0; i < mNumAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void NBaseShader::Unuse() {
	glUseProgram(0);

	for (int i = 0; i < mNumAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

GLint NBaseShader::GetUniformLocation(const std::string & uniformName)
{
	GLint location = glGetUniformLocation(mProgramShader_ID, uniformName.c_str());

	if (location == GL_INVALID_INDEX) {
		FatalError("Uniform: " + uniformName + " no se encontro en el Shader.");
	}

	return location;
}

void NBaseShader::AddAttribute(const std::string & attributeName)
{
	glBindAttribLocation(mProgramShader_ID, mNumAttributes++, attributeName.c_str());
}

void NBaseShader::LoadAndCompile(const std::string& vertexShaderPath,
	const std::string& fragmentShaderPath) {
	
	// Crear programa de Shader
	mProgramShader_ID = glCreateProgram();

	mVertexShader_ID = glCreateShader(GL_VERTEX_SHADER);
	if (mVertexShader_ID == 0) {
		FatalError("Vertex Shader fallo en crearse.");
	}

	mFragmentShader_ID = glCreateShader(GL_FRAGMENT_SHADER);
	if (mFragmentShader_ID == 0) {
		FatalError("Fragment Shader fallo en crearse.");
	}

	CompileShader(vertexShaderPath, mVertexShader_ID);
	CompileShader(fragmentShaderPath, mFragmentShader_ID);
}

void NBaseShader::CompileShader(const std::string& filePath, GLuint shader_ID) {
	std::ifstream shaderFile(filePath);

	if (shaderFile.fail()) {
		perror(filePath.c_str());
		FatalError("Fallo abrir el archivo: " + filePath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(shaderFile, line)) {
		fileContents += line + "\n";
	}

	shaderFile.close();

	// Necesario porque OpenGL lee char* 
	const char* contentPtr = fileContents.c_str();
	// Darle el codigo fuente al Shader
	glShaderSource(shader_ID, 1, &contentPtr, nullptr);
	// Compilar el Shader
	glCompileShader(shader_ID);

	GLint wasSuccess = 0;
	glGetShaderiv(shader_ID, GL_COMPILE_STATUS, &wasSuccess);

	if (wasSuccess == GL_FALSE) {
		// Sacar el tamanio del texto del stack trace de compilacion
		GLint maxLength = 0;
		glGetShaderiv(shader_ID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(shader_ID, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(shader_ID);

		std::printf("%s\n", &(errorLog[0]));
		FatalError("Shader: '" + filePath + "' fallo la compilacion.");
	}
}

void NBaseShader::LinkShaders() {
	glAttachShader(mProgramShader_ID, mVertexShader_ID);
	glAttachShader(mProgramShader_ID, mFragmentShader_ID);

	glLinkProgram(mProgramShader_ID);

	GLint isLinked = 0;
	glGetProgramiv(mProgramShader_ID, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(mProgramShader_ID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(mProgramShader_ID, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(mProgramShader_ID);
		glDeleteShader(mVertexShader_ID);
		glDeleteShader(mFragmentShader_ID);

		std::printf("%s\n", &(errorLog[0]));
		FatalError("Shader: fallo la union(link).");
	}

	glDetachShader(mProgramShader_ID, mVertexShader_ID);
	glDetachShader(mProgramShader_ID, mFragmentShader_ID);
	glDeleteShader(mVertexShader_ID);
	glDeleteShader(mFragmentShader_ID);
}