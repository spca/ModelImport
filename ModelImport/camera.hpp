#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include <glm\gtc\matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.05f;
const GLfloat ZOOM = 45.0f;

class Camera {
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;

public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH):Front(glm::vec3(0.0f,0.0f,-1.0f)),Pitch(PITCH),Yaw(YAW),MovementSpeed(SPEED),MouseSensitivity(SENSITIVTY),Zoom(ZOOM) {
		this->Position = position;
		this->WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		this->updateCameraVectors();

	}

	glm::mat4 getViewMatrix() {
		return glm::lookAt(this->Position, this->Front+ this->Position,this->Up);
	}

	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Pitch += yoffset;
		this->Yaw += xoffset;

		if (constrainPitch) {
			if (this->Pitch > 89.0f)
				this->Pitch = 89.0;
			if (this->Pitch < -89.0f)
				this->Pitch = -89.0f;
		}
		this->updateCameraVectors();
	}

	void ProcessKeyboard(Camera_Movement direction, GLfloat delta) {
		GLfloat velocity = this->MovementSpeed * delta;
		if (direction == FORWARD)
			this->Position += this->Front * velocity;
		if (direction == BACKWARD)
			this->Position -= this->Front * velocity;
		if (direction == LEFT)
			this->Position -= this->Right * velocity;
		if (direction == RIGHT)
			this->Position += this->Right * velocity;

		this->Position.y = 0.0;
	}

	void ProcessMouseScroll(GLfloat yoffset) {
		if (this->Zoom >= 1.0f && this->Zoom <= 45.0f) {
			this->Zoom -= yoffset;
		}
		if (this->Zoom <= 1.0f)
			this->Zoom = 1.0f;
		if (this->Zoom >= 45.0f)
			this->Zoom = 45.0f;

	}
private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		front.y = sin(glm::radians(this->Pitch));
		front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		this->Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		this->Up = glm::normalize(glm::cross(this->Right, this->Front));
	}
	
};