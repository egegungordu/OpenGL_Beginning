#pragma once
#include "Renderer.h"
#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1f(const std::string& name, float vx);
	void SetUniform3f(const std::string& name, float vx, float vy, float vz);
	void SetUniform2i(const std::string& name, int vx, int vy);
	void SetUniform4f(const std::string& name, float vx, float vy, float vz, float vw);
	void SetUniformMatrix4f(const std::string& name, int num, GLboolean transposed, const GLfloat* value);
private:
	ShaderProgramSource ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
};
