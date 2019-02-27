#include <stdio.h>
#include <GLAD\include\glad\glad.h>
#include <glfw-3.2.1\include\GLFW\glfw3.h>
#include <vector>
#include "Shader.h"
#include "Render.h"
//#include "Object.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height); //Function for resizing window
void Input(GLFWwindow* window); // Function for polling keyboard events 

GLfloat vertices[] = {
	0.5f, 0.5f,   // top right
	0.5f, -0.5f,   // bottom right
	-0.5f, -0.5f,   // bottom left
	-0.5f, 0.5f   // top left 
};
GLuint indices[] = {
	0,1,3,
	1,2,3
};


int main(int argc,char **argv){
	glfwInit(); //intitialise graphical library framework

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //set opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL); //Create window
	if (window == NULL){ // Check if window was successfully created 
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //Make the newly created window the current one
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //Function for changing size of window on userinput (PLEASE PUT INTO INPUT CLASS)

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){ //Initialise and check if GLAD is working
		printf("Failed to initialise GLAD");
		return -1;
	}
	glEnable(GL_DEBUG_OUTPUT);

	Shader TriangleShader("C:/Users/Home/Documents/Visual Studio 2013/Projects/GL/GL/Shader_Vs.vs", "C:/Users/Home/Documents/Visual Studio 2013/Projects/GL/GL/Shader_Fg.fs");	
	Render Triangle(TriangleShader.ID, vertices, sizeof(vertices), indices, sizeof(indices), 1, GL_STATIC_DRAW);
	float a[3] = { 0.5f, 0.2f, 0.3f };
	TriangleShader.use();
	TriangleShader.setVec3("vertexColor", a);

	const int TICKS_PER_SECOND = 1000;
	const int SKIP_TICKS = 1000/TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;
	unsigned int t = glfwGetTime();
	int loops = 0;

	while (!glfwWindowShouldClose(window)) //Main Loop
	{
		glfwSwapBuffers(window);
		loops = 0;
		while (glfwGetTime() > t && loops < MAX_FRAMESKIP) {
			Input(window);
			TriangleShader.use();

			a[0] = 0.2*sin(glfwGetTime() / 2 * 3.14);
			a[1] = cos(0.3*glfwGetTime());
			a[2] = sin(0.2*glfwGetTime());
			TriangleShader.setVec3("vertexColor", a);
			t += SKIP_TICKS;
			loops++;
		}
		t = 0;
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Triangle.Loop(6);

		glfwPollEvents();
	}
	Triangle.~Render();
	glfwTerminate();
	return 0;
}


void Input(GLFWwindow* window){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}