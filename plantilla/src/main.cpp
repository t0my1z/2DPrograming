
#define LITE_GFX_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>

using namespace std;

#include "vector2d.h"
#include <cmath> // Include for trigonometric functions
#include <string>
#include <sstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


template <typename T>
std::string stringFromNumber(T val)
{
	std::ostringstream stream; 
	stream << std::fixed << val;
	return stream.str(); 
}

float CalculateAngle(vec2 offsetedPos, vec2 mousePos)
{

	vec2 vecFromMouseToOffset = offsetedPos - mousePos;
	vecFromMouseToOffset = vnorm(vecFromMouseToOffset);
	// Calculate the angle between the vectors using the dot product
	float angle = atan2(vecFromMouseToOffset.y, vecFromMouseToOffset.x);
	angle = angle * 180 / M_PI;
	return angle;
}

int main() 
{

	double rotationSpeed = 20.0; // Degrees per second
	double currentAngle = 0.0; // Initial angle

	
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
		//Calculate mousePos and save it on a vec2
		double mouseXPos;
		double mouseYPos;
		glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
		vec2 mousePos = vec2(static_cast<float>(mouseXPos), static_cast<float>(mouseYPos));

		// Calculate position offset from mousePos
		double offsetX = 100 * cos(currentAngle * M_PI / 180); // 50 is the distance from mousePos
		double offsetY = 100 * sin(currentAngle * M_PI / 180);

		// Update angle based on time
		double deltaTime = glfwGetTime() - elapsedTime;
		elapsedTime = glfwGetTime();
		currentAngle += rotationSpeed * deltaTime;

		//Calculate Dist and Angle To Print them
		vec2 dirToVec = screenMiddlePoint - mousePos;
		float distTo = vlen(dirToVec);
		vec2 offsetedCirclePos = vec2(mousePos.x + offsetX, mousePos.y + offsetY);
		//float angle = vang(offsetedCirclePos, mousePos);
		float angle = CalculateAngle(offsetedCirclePos, mousePos);

		std::string name = "DistOfCursor: " + stringFromNumber(distTo) + " -- " + "AngleFromMiddle: " + stringFromNumber(angle);
		glfwSetWindowTitle(window, name.c_str());

		lgfx_clearcolorbuffer(0, 0, 0);

		lgfx_setcolor(0, 1, 1, 1);

		//Draw rect with an angle and offset from mouse
		lgfx_drawoval(offsetedCirclePos.x -25, offsetedCirclePos.y - 25, 25, 25);

		lgfx_setcolor(1, 0, 1, 1);

		lgfx_drawrect(screenMiddlePoint.x - 25, screenMiddlePoint.y -25, 50, 50);

		lgfx_drawrect(mousePos.x - 25, mousePos.y - 25, 50, 50);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

    return 0;
}
