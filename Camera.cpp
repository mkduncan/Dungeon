#include "Camera.hpp"
#include "Window.hpp"

#include <gtc/matrix_transform.hpp>

#define MOVEMENT_SPEED 2.0f
#define LOOK_SPEED 360.0f

glm::mat4 Camera::Projection(glm::perspective(glm::radians(90.0f), 1.0f, 0.2f, 200.0f)), Camera::View(glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f))), Camera::Model = glm::mat4(1.0f);
glm::vec3 Camera::Position(0.0f, 0.0f, 0.0f), Camera::Right(1.0f, 0.0f, 0.0f), Camera::Up(0.0f, 1.0f, 0.0f), Camera::Front(0.0f, 0.0f, -1.0f);
double Camera::Mouse[2] = { -1.0, -1.0 };
float Camera::Pitch = 0.0f, Camera::Yaw = -90.0f;
bool Camera::Click[2] = { false, false };

bool Camera::Update()
{
	double newMouse[2] = { Camera::Mouse[0], Camera::Mouse[1] };

	if (Window::Interface == nullptr)
	{
		return false;
	}

	if (Camera::Mouse[0] < 0.0 && Camera::Mouse[1] < 0.0)
	{
		glfwGetCursorPos(Window::Interface, &Camera::Mouse[0], &Camera::Mouse[1]);

		if (glfwGetMouseButton(Window::Interface, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			Camera::Click[0] = true;
		}

		else
		{
			Camera::Click[0] = false;
		}

		return true;
	}

	Camera::Click[1] = Camera::Click[0];
	glfwGetCursorPos(Window::Interface, &Camera::Mouse[0], &Camera::Mouse[1]);

	if (glfwGetMouseButton(Window::Interface, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		Camera::Click[0] = true;
	}

	else
	{
		Camera::Click[0] = false;
	}

	if (glfwGetKey(Window::Interface, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(Window::Interface, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		Camera::Position -= Camera::Right * Window::DeltaTime(MOVEMENT_SPEED);
	}

	if (glfwGetKey(Window::Interface, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(Window::Interface, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		Camera::Position += Camera::Right * Window::DeltaTime(MOVEMENT_SPEED);
	}

	if (glfwGetKey(Window::Interface, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(Window::Interface, GLFW_KEY_UP) == GLFW_PRESS)
	{
		Camera::Position += Camera::Front * Window::DeltaTime(MOVEMENT_SPEED);
	}

	if (glfwGetKey(Window::Interface, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(Window::Interface, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		Camera::Position -= Camera::Front * Window::DeltaTime(MOVEMENT_SPEED);
	}

	if (Camera::Click[0] && Camera::Click[1])
	{
		Camera::Yaw -= static_cast<float>(newMouse[0] - Camera::Mouse[0])* Window::DeltaTime(LOOK_SPEED);
		Camera::Pitch += static_cast<float>(newMouse[1] - Camera::Mouse[1])* Window::DeltaTime(LOOK_SPEED);

		if (Camera::Pitch > 89.0f)
		{
			Camera::Pitch = 89.0f;
		}

		if (Camera::Pitch < -89.0f)
		{
			Camera::Pitch = -89.0f;
		}
	}

	Camera::Front = glm::normalize(glm::vec3(glm::cos(glm::radians(Camera::Yaw)) * glm::cos(glm::radians(Camera::Pitch)), glm::sin(glm::radians(Camera::Pitch)), glm::sin(glm::radians(Camera::Yaw)) * glm::cos(glm::radians(Camera::Pitch))));
	Camera::Right = glm::normalize(glm::cross(Camera::Front, glm::vec3(0.0f, 1.0f, 0.0f)));
	Camera::Up = glm::normalize(glm::cross(Camera::Right, Camera::Front));
	Camera::View = glm::lookAt(Camera::Position, Camera::Position + Camera::Front, Camera::Up);

	return true;
}

bool Camera::SetWorld(const Shader& shader)
{
	if (!shader.SetMatrix(std::string("projection"), Camera::Projection) || !shader.SetMatrix(std::string("view"), Camera::View) || !shader.SetMatrix(std::string("model"), Camera::Model))
	{
		return false;
	}

	return true;
}