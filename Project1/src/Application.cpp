#include <GL/glew.h> //always include this header before glfw3.h header- REASON: according to the docs.
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#define ASSERT(x) if (!(x)) __debugbreak(); //custom error debug macro for a detailed error message (compatible with older versions of opengl) 
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall())

static void GLClearError() //used to handle errors in openGL 
{
	while (glGetError != GL_NO_ERROR);
}

static bool GLLogCall()
{
	while (GLenum error = glGetError()) //the error is read as a hexadecimal value(as opengl defines its enums as hexadecimal values) while is written as a int value
	{
		std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
		return false;
	}
}

/*
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};
*/

/*
static ShaderProgramSource ParseShader(const std::string& filepath) 
{
	std::ifstream stream(filepath);
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];


	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				//set mode to vertex
				type = ShaderType::VERTEX;
			}

			else if (line.find("fragment") != std::string::npos)
			{
				//set mode to fragment
				type = ShaderType::FRAGMENT;
			}
		}

		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}
*/

/*
static unsigned int CompileShader(const unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str(); //return pointer to null-terminated immutable array.
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Handling Errors in OpenGL because we must...
	int result; 
	glGetShaderiv(id, GL_COMPILE_STATUS, &result); 

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		//char* message = new char[length];  //char array needs const value for intialising, so you can do so
											//by allocating the heap and deleting it later on....but for now

		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

	std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
	std::cout << message << std::endl;
	glDeleteShader(id);
	return 0;
	}

	return id;
}
*/


/*
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs); //basically freeing the shader object from the memory;

	return program;
} 
*/

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "OpenGL Renderer", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); //synchronizes the rendering with the system frame rate

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error in initializing the glew library" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	{ //start of scope
		float positions[] = {
			-0.5f, -0.5f, 0.0f, 0.0f,	//0
			 0.5f, -0.5f, 1.0f, 0.0f,	//1
			 0.5f, 0.5f, 1.0f, 1.0f,	//2
			-0.5f, 0.5f, 0.0f, 1.0f	//3

		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		unsigned int vao; //vao stands for 'Vertex Array Object'
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao); //vertex array has no target currently so we assign vao as its default.

		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		/*
		unsigned int buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);
		*/

		/*
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
		*/

		IndexBuffer ib(indices, 6);
		/*
		unsigned int ibo;  //ibo is short for Index Buffer Object
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indices, GL_STATIC_DRAW);
		*/

		Shader shader("resources/shaders/BasicShader.shader");
		shader.Bind();
		/*ShaderProgramSource source = ParseShader("resources/shaders/BasicShader.shader");
		unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
		glUseProgram(shader); */

		/*int location = glGetUniformLocation(shader, "u_Color");
		glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f); //uniforms are called per Draw function(glDrawElements)
														//attributes are called per vertex
														//Uniforms do not change from one shader invocation to another in a Rendering Call
													   //Each shader execution in a Rendering command is a "shader invocation"
													   */
		shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

		Texture texture("resources/textures/amogus.png");
		texture.Bind(2);
		shader.SetUniform1i("u_Texture", 2);

		/*glBindVertexArray(0);*/
		va.Unbind();

		/*glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); */
		va.Unbind();
		ib.Unbind();

		/*glUseProgram(0);*/
		shader.Unbind();

		Renderer renderer;

		float r = 0.0f;
		float increment = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			//glClear(GL_COLOR_BUFFER_BIT);
			renderer.Clear();



			//glDrawArrays(GL_TRIANGLES, 0, 6); //this is used for vertex buffers


			/*glUseProgram(shader); */ 
			shader.Bind();


			/*glUniform4f(location, r, 0.3f, 0.8f, 1.0f);*/  
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

			//glBindVertexArray(vao);
			//	va.Bind();
			//	ib.Bind();
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

			renderer.Draw(va, ib, shader);

			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); //this is used to render when we have index arrays
													//used most of the time

			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;

			r += increment;

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		/*glDeleteProgram(shader);*/
		shader.~Shader();

	} //end of scope
	glfwTerminate();
	return 0;
}