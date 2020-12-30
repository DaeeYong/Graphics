#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
void render(GLFWwindow* window);

int main()
{
	glfwInit(); //glfw 초기화
	GLFWwindow* window = glfwCreateWindow(600, 600, "first", 0, 0); //윈도우 창 생성
	glfwMakeContextCurrent(window); //사용할 window 지정

	//glfwWindowShouldClose : window를 닫으면, true를 반환하는 함수
	while (!glfwWindowShouldClose(window)) {
		render(window);
		glfwPollEvents(); //입력을 처리
	}
	glfwDestroyWindow(window); // 생성한 window 해제
	glfwTerminate(); //할당한 모든 자원 해제
}

void render(GLFWwindow* window)
{
	glClearColor(1,1,240/255,1); //생성한 window 지우는 색깔
	glClear(GL_COLOR_BUFFER_BIT); //??
	glfwSwapBuffers(window);
}
