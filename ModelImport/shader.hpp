#include <iostream>
#define GLEW_STATIC
#include <GL\glew.h>
#include<fstream>
#include <sstream>
#include <glm/glm.hpp>
class Shader {

public:
	GLuint program;
	Shader(const std::string& vsh,const std::string& fsh) {
		std::ifstream vstream;
		std::ifstream fstream;
		std::string	 vcode,fcode;
		vstream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fstream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
		vstream.open(vsh);
		fstream.open(fsh);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vstream.rdbuf();
		fShaderStream << fstream.rdbuf();
		vstream.close();
		fstream.close();

		vcode = vShaderStream.str();
		fcode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "error : failed read file" << std::endl;
		}
		const GLchar* vscode = vcode.c_str();
		const GLchar* fscode = fcode.c_str();

		GLuint vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vscode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment,1,&fscode,NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		program = glCreateProgram();
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(program);
		checkCompileErrors(program, "PROGRAM");
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void use() {
		glUseProgram(program);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(program, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(program, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string &name, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string &name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string &name, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string &name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string &name, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string &name, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};

