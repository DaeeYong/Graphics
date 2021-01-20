#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<glm/glm.hpp>
#include<vector>
#include"toys.h"
void init();
void render(GLFWwindow* window);

int main() {

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(640, 480,
		"Triangle",0,0);

	glfwMakeContextCurrent(window);
	glewInit();

	init();

	while (!glfwWindowShouldClose(window)) {
		render(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;

}
GLuint tribuffer = 0;
GLuint va = 0;
GLuint elementarray = 0;
Program program;
using namespace std;
using namespace glm;
void init() {

	program.loadShaders("shader.vert", "shader.frag");
	vector<vec3> trivertdata = { {-0.7,0.7,0},{-0.5,0.9,0},{0.5,0.9,0},{0.7,0.7,0} };
	GLuint tridata[] = { 0,1,2,3,4 };
	glGenBuffers(1, &tribuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tribuffer);
	glBufferData(GL_ARRAY_BUFFER, trivertdata.size() * sizeof(vec3), trivertdata.data(),
		GL_STATIC_DRAW);

	glGenVertexArrays(1, &va);
	glBindVertexArray(va);
	glBindBuffer(GL_ARRAY_BUFFER, tribuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glGenBuffers(1, &elementarray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementarray);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 5 * sizeof(GLuint)
		, tridata,GL_STATIC_DRAW);
}

void render(GLFWwindow* window) {
	
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glClearColor(102 / 255, 102 / 255, 1.f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program.programID);
	
	glBindVertexArray(va);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementarray);
	glDrawElements(GL_TRIANGLE_FAN,5, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(window);
}