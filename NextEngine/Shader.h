#pragma once

#include <string>
#include <GL\glew.h>
using namespace std;

/**
 * @class Shader
 * @brief Represents an OpenGL shader (vertex or fragment) and handles loading and compilation.
 *
 * This class encapsulates the creation and management of a GLSL shader. It supports loading source code
 * from a file, compiling it, and retrieving the shader ID used in OpenGL programs.
 */
class Shader
{
	GLuint shaderId;
	string fileName;
	GLenum shaderType; ///< Type of the shader (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER)

public:
	/**
	 * @brief Gets the OpenGL shader ID.
	 * @return Shader ID (GLuint).
	 */
	GLuint getShaderId();

	/**
	 * @brief Loads and compiles the shader from the file.
	 * @return True if successful, false on error.
	 */
	bool loadSource();

	/**
	 * @brief Prints the shader compilation log for debugging.
	 */
	void printShaderLog();

	/**
	 * @brief Constructs a Shader object.
	 * @param fileName Path to the shader source file.
	 * @param shaderType Type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
	 */
	Shader(string fileName, GLenum shaderType);

	/**
	 * @brief Destructor. Cleans up OpenGL shader resources.
	 */
	~Shader();
};