#include <GLAD\include\glad\glad.h>
#include <glfw-3.2.1\include\GLFW\glfw3.h>
#include <stdio.h>
#include <vector>
#include "Shader.h"

class Render
{
private:

	GLuint VBO, VAO, EBO;
	int IDz;

	void GenerateBuffers(int num, unsigned int *Object){ glGenBuffers(num, Object); } //Generates buffers 

	void GenerateVertex(int num, unsigned int *Object){ glGenVertexArrays(num, Object); }

	void BindVertex(unsigned int Object){ glBindVertexArray(Object); } //Binds vertex

	void BindBuffers(unsigned int Object, bool type){
		if (type == FALSE)
			glBindBuffer(GL_ARRAY_BUFFER, Object);
		if (type == TRUE)
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Object);
	} // Binds buffers

	void BufferData(const GLfloat *vertices, int size, bool type, GLenum usage = GL_STATIC_DRAW){

		if (type == FALSE)
			glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
		if (type == TRUE)
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (GLuint*)vertices, usage);
	} //Specifies buffer data

	void VertexAttributes(GLint Attrib, GLint size){
		glVertexAttribPointer(Attrib, size, GL_FLOAT, GL_FALSE, size*sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(Attrib);
	}

	GLint *GetAttributeData(GLuint s, GLint attribute){
		GLint ALS[2];

		GLint size; // size of the variable
		GLenum type; // type of the variable (float, vec3 or mat4, etc)

		const GLsizei bufSize = 16; // maximum name length
		GLchar name[bufSize]; // variable name in GLSL
		GLsizei length; // name length

		glGetActiveAttrib(s, (GLuint)attribute, bufSize, &length, &size, &type, name);

		printf("Attribute #%d Type: %u Name: %s\n", attribute, type, name);

		if (type == GL_FLOAT_VEC2)
			ALS[1] = 2;
		else if (type == GL_FLOAT_VEC3)
			ALS[1] = 3;
		else
		{
			printf("Error attribute is not a valid type or not yet implemented TYPE: %u", type);
			exit;
		}
		ALS[0] = attribute;
		printf("%u", ALS[1]);
		return ALS;
	}


public:


	Render::Render(GLuint  s, const GLfloat *vertices, int size, const GLuint *indices, int sizeE, int ID = 0, GLenum usage = GL_STATIC_DRAW){ //main renderer 
		GenerateVertex(ID, &VAO);
		GenerateBuffers(ID, &VBO);
		GenerateBuffers(ID, &EBO);
		//glGenBuffers(1, &EBO);

		BindVertex(VAO);

		BindBuffers(VBO, 0);
		BufferData(vertices, size, 0);
		BindBuffers(EBO, 1);
		BufferData((GLfloat*)indices, sizeE, 1);

		GLint *temparray = GetAttributeData(s, 0);

		VertexAttributes(temparray[0], temparray[1]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		IDz = ID;
	}

	void Loop(int vertices){
		BindVertex(VAO);
		glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, vertices);
		glBindVertexArray(0);
	}

	Render::~Render(){
		glDeleteVertexArrays(IDz, &VAO);
		glDeleteBuffers(IDz, &VBO);
		glDeleteBuffers(IDz, &EBO);
	}

};
