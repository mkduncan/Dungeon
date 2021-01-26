#include "Shader.hpp"

Shader::Shader() : Id(0)
{
}

Shader::~Shader()
{
	if (this->Id != 0)
	{
		glDeleteProgram(this->Id);
		this->Id = 0;
	}
}

Shader::Shader(const Shader& shader) : Id(shader.Id)
{
}

Shader& Shader::operator=(const Shader &shader)
{
	if (this->Id != 0)
	{
		glDeleteProgram(this->Id);
	}

	this->Id = shader.Id;
	return *this;
}

bool Shader::Create(const std::string &vertexCode, const std::string &fragmentCode)
{
    const char* vertexSource = vertexCode.c_str(), * fragmentSource = fragmentCode.c_str();
    GLuint vertexId = 0, fragmentId = 0;
	GLint status = 0;

    if (this->Id != 0 || vertexCode.empty() || fragmentCode.empty())
    {
        return false;
    }

    vertexId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexId, 1, &vertexSource, nullptr);
    glCompileShader(vertexId);
	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		glDeleteShader(vertexId);
		return false;
	}

    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentId, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentId);
	glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);

		return false;
	}

	this->Id = glCreateProgram();
	glAttachShader(this->Id, vertexId);
	glAttachShader(this->Id, fragmentId);
	glLinkProgram(this->Id);
	glGetProgramiv(this->Id, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
		glDeleteProgram(this->Id);

		return false;
	}

	glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

	return true;
}

bool Shader::Use() const
{
	if (this->Id == 0)
	{
		glUseProgram(0);
		return false;
	}

	glUseProgram(this->Id);
	return true;
}

bool Shader::Destroy()
{
	if (this->Id == 0)
	{
		return false;
	}

	glDeleteProgram(this->Id);
	this->Id = 0;

	return true;
}

bool Shader::SetBoolean(const std::string &key, const bool value) const
{
	if (this->Id == 0)
	{
		return false;
	}

	glUniform1i(glGetUniformLocation(this->Id, key.c_str()), static_cast<GLint>(value));
	return true;
}

bool Shader::SetInteger(const std::string &key, const GLint value) const
{
	if (this->Id == 0)
	{
		return false;
	}

	glUniform1i(glGetUniformLocation(this->Id, key.c_str()), value);
	return true;
}

bool Shader::SetFloat(const std::string &key, const float value) const
{
	if (this->Id == 0)
	{
		return false;
	}

	glUniform1f(glGetUniformLocation(this->Id, key.c_str()), value);
	return true;
}

bool Shader::SetVector(const std::string &key, const glm::vec2 &value) const
{
	if (this->Id == 0)
	{
		return false;
	}

	glUniform2fv(glGetUniformLocation(this->Id, key.c_str()), 1, &value[0]);
	return true;
}

bool Shader::SetVector(const std::string &key, const glm::vec3 &value) const
{
	if (this->Id == 0)
	{
		return false;
	}

	glUniform3fv(glGetUniformLocation(this->Id, key.c_str()), 1, &value[0]);
	return true;
}

bool Shader::SetVector(const std::string &key, const glm::vec4 &value) const
{
	if (this->Id == 0)
	{
		return false;
	}

	glUniform4fv(glGetUniformLocation(this->Id, key.c_str()), 1, &value[0]);
	return true;
}

bool Shader::SetMatrix(const std::string &key, const glm::mat2 &value) const
{
	if (this->Id == 0)
	{
		return false;
	}

	glUniformMatrix2fv(glGetUniformLocation(this->Id, key.c_str()), 1, GL_FALSE, &value[0][0]);
	return true;
}

bool Shader::SetMatrix(const std::string &key, const glm::mat3 &value) const
{
	if (this->Id == 0)
	{
		return false;
	}

	glUniformMatrix3fv(glGetUniformLocation(this->Id, key.c_str()), 1, GL_FALSE, &value[0][0]);
	return true;
}

bool Shader::SetMatrix(const std::string &key, const glm::mat4 &value) const
{
	if (this->Id == 0)
	{
		return false;
	}

	glUniformMatrix4fv(glGetUniformLocation(this->Id, key.c_str()), 1, GL_FALSE, &value[0][0]);
	return true;
}