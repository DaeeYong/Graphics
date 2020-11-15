
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<vector>
#include "toys.h"


void render(GLFWwindow* window);
void init();

int main()
{
	glfwInit(); //glfw 초기화
	GLFWwindow* window = glfwCreateWindow(800, 600, "first", 0, 0); //윈도우 창 생성
	glfwMakeContextCurrent(window); //사용할 window 지정
	glewInit(); //glew 초기화

	init(); //윈도우 실행전에 초기화

	//glfwWindowShouldClose : window를 닫으면, true를 반환하는 함수
	while (!glfwWindowShouldClose(window)) {
		render(window);
		glfwPollEvents(); //입력을 처리
	}
	glfwDestroyWindow(window); // 생성한 window 해제
	glfwTerminate(); //할당한 모든 자원 해제
}

GLuint triBuffer = 0;
GLuint va = 0; //vertex array
GLuint vao = 0; //vetex array object
GLuint elementArray = 0;
Program program;

using namespace glm;
using namespace std;
void render(GLFWwindow* window)
{
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glClearColor(228/255.0,187/255.0,254/255.0,1); //생성한 window 지우는 색깔
	glClear(GL_COLOR_BUFFER_BIT); //??
	glUseProgram(program.programID);
	glBindVertexArray(va);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArray);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(window);
}

void init() {

	program.loadShaders("shader.vert", "shader.frag");

	std::vector<glm::vec3> trivertdata = { {0,1,0},{-0.7,-0.7,0},{0.7,-0.7,0} };
	std::vector<glm::u16vec3> tridata = { {0,1,2} };
	
	glGenBuffers(1, &triBuffer); //generate
	glBindBuffer(GL_ARRAY_BUFFER, triBuffer); //activate
	glBufferData(GL_ARRAY_BUFFER,trivertdata.size()*sizeof(vec3),trivertdata.data(),GL_STATIC_DRAW);

	glGenVertexArrays(1, &va);
	glBindVertexArray(va);
	glBindBuffer(GL_ARRAY_BUFFER, triBuffer); //activate
	glEnableVertexAttribArray(0);

	//0번 플러그,3개짜리 데이터, FLOAT타입,길이를 만들X(normalize x), 처음시작위치0번부터,NULL포인터
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glGenBuffers(1, &elementArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArray);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tridata.size() * sizeof(u16vec3), tridata.data(), GL_STATIC_DRAW);
}