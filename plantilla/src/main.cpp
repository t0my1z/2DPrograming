
#define LITE_GFX_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>

using namespace std;
#include "vector2d.h"

int main() 
{
	
	if (!glfwInit())
	{
		//Error
		glfwTerminate();
	}

	double elapsedTime = glfwGetTime();

	vec2 screenMiddlePoint = vec2(320, 240);

	GLFWwindow* window = glfwCreateWindow(640, 480, "GameWindow", NULL, NULL);
	
	glfwMakeContextCurrent(window);

	lgfx_setup2d(640, 480);

	while (!glfwWindowShouldClose(window))
	{
		double mouseXPos;
		double mouseYPos;
		glfwGetCursorPos(window, &mouseXPos, &mouseYPos);

		vec2 mousePos = vec2(static_cast<float>(mouseXPos), static_cast<float>(mouseYPos));

		lgfx_clearcolorbuffer(0, 0, 0);

		lgfx_setcolor(1, 0, 1, 1);

		lgfx_drawrect(screenMiddlePoint.x - 25, screenMiddlePoint.y -25, 50, 50);

		lgfx_drawrect(mousePos.x - 25, mousePos.y - 25, 50, 50);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

    return 0;
}
