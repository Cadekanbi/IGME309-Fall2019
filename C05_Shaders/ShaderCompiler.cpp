#include "ShaderCompiler.h"

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
#pragma region Read Vertex Shader File
	// Read the Vertex Shader code from the file
	std::string vertexShaderSource; //String that contains the source
	std::ifstream vertexShaderStream(vertex_file_path, std::ios::in); //Create a stream from the file
	if (vertexShaderStream.is_open()) //able to find the file
	{
		std::string Line = "";
		while (getline(vertexShaderStream, Line))
			vertexShaderSource += "\n" + Line;
		vertexShaderStream.close();
	}
	else //not able to find the file
	{
		printf("Impossible to open %s. Are you in the right directory?\n", vertex_file_path);
		getchar();
		return 0;
	}
	char const* vertexSource = vertexShaderSource.c_str(); //translate the string to a char const*
#pragma endregion
#pragma region Read Fragment Shader File
	// Read the Fragment Shader code from the file
	std::string fragmentShaderSource; //String that contains the source
	std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in); //Create a stream from the file
	if (fragmentShaderStream.is_open()) //able to find the file
	{
		std::string Line = "";
		while (getline(fragmentShaderStream, Line))
			fragmentShaderSource += "\n" + Line;
		fragmentShaderStream.close();
	}
	else //not able to find the file
	{
		printf("Impossible to open %s. Are you in the right directory?\n", vertex_file_path);
		getchar();
		return 0;
	}
	char const* fragmentSource = fragmentShaderSource.c_str(); //translate the string to a char const*
#pragma endregion
#pragma region Compile Vertex and Fragment shaders
	// Create and compile the vertex shader
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
	glCompileShader(vertexShaderID);

	// Create and compile the fragment shader
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShaderID);
#pragma endregion
#pragma region Complementary Vertex and Fragment shaders
	/*const GLchar* pszVertexShader = R"glsl(
		#version 330
		in vec3 ptPosition;
		void Main() {
			gl_Position = vec4(ptPosition, 1);
		}
	)glsl";
	const GLchar* pszPixelShader = R"glsl(
		#version 330
		out vec4 fragment;
		void Main() {
			fragmentt = vec4(1.0f, 0.0f, 0.0f, 1.0f);
		}
	)glsl";*/
#pragma endregion
#pragma region Compile Shader Program
	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
	glLinkProgram(shaderProgramID);
#pragma endregion
#pragma region Check errors on shader program
	//Check the program
	GLint result = GL_FALSE;
	GLint log = GL_FALSE;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &log);
	if (log > 0)
	{
		std::vector<char> ProgramErrorMessage(log + 1);
		glGetProgramInfoLog(shaderProgramID, log, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
		glDeleteShader(shaderProgramID);
	}
#pragma endregion
#pragma region Cleanup
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
#pragma endregion
	return shaderProgramID;
}