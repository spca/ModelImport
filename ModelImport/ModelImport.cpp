// ModelImport.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<glm\glm.hpp>
#include"shader.hpp"
#include<GLFW\glfw3.h>
#include"camera.hpp"
#include"model.hpp"
#define STB_IMAGE_IMPLEMENTATION
// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 450;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool firstMouse = true;
// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
void processInput(GLFWwindow *window);
void cursorpos_callback(GLFWwindow* window, double xoffset, double yoffset);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	auto window = glfwCreateWindow(600, 450, "x", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();
	glViewport(0, 0, 600, 450);

	glfwSetCursorPosCallback(window, cursorpos_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	Shader shader("vertex.vs", "fragment.fs");
	Model* model = new Model("resource/nanosuit/nanosuit.obj");


	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 model;
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);
		
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void cursorpos_callback(GLFWwindow * window, double xpos, double ypos)
{

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}