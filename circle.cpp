/*
	name : Elwlrma
*/

#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "toys.h"
#include <glm/glm.hpp>
#include<vector>
#include<math.h>

void render(GLFWwindow* window);
void init();

int main(int argc, const char* argv[]) {
	
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 800, "Circle", 0, 0);
	glfwMakeContextCurrent(window);
	glewInit();

	init();
	while (!glfwWindowShouldClose(window)) {
		render(window);
		glfwPollEvents();
	}
	return 0;
}

GLuint triBuffer = 0;
// GLuint vao = 0;
GLuint va = 0;
GLuint elementArray = 0;

Program program;

using namespace glm;
using namespace std;
std::vector<vec3> triVertData;
std::vector<uvec3> triData;
void init() {
	program.loadShaders("shader.vert", "shader.frag");
	double rad = 1; //radius : 1
//	std::vector<vec3> triVertData;
//	std::vector<uvec3> triData;

	triVertData.push_back(vec3(0, 0, 0));
	for (int i = 0; i < 360; i++) {
		double angle = i * 3.141592 / 180;
		double x = rad * cos(angle);
		double y = rad * sin(angle);
		triVertData.push_back(vec3(x, y, 0));
	}
	for (int i = 0; i < 360; i++) {
		triData.push_back(u16vec3(0,i,i+1));
	}
	triData.push_back(u16vec3(0, 359, 1));




	/*
	triVertData.push_back(vec3(-0.7,0,0));
	triVertData.push_back(vec3(0.7,0,0));
	triVertData.push_back(vec3(0, 1, 0));
	triVertData.push_back(vec3(0, -1, 0));


	triData.push_back(u16vec3(0, 1, 2));
	triData.push_back(u16vec3(0, 3, 1));
	*/
	//create buffer(vertex data buffer)
	glGenBuffers(1, &triBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, triBuffer); //active
	glBufferData(GL_ARRAY_BUFFER,triVertData.size()*sizeof(vec3),triVertData.data(),GL_STATIC_DRAW);

	glGenVertexArrays(1, &va);
	glBindVertexArray(va);
	glEnableVertexAttribArray(0); //????
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);//????

	glGenBuffers(1, &elementArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArray);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triData.size() * sizeof(uvec3), triData.data(),GL_STATIC_DRAW);

;
}
void render(GLFWwindow* window) {
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glClearColor(0,1,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program.programID);

	glBindVertexArray(va);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArray);
	glDrawElements(GL_TRIANGLES,1083,GL_UNSIGNED_INT,0); //vetex number for link dots
	glfwSwapBuffers(window);
}
