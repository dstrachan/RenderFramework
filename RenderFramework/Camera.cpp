#include "stdafx.h"

#include "Camera.h"

namespace RenderFramework
{
	Camera::Camera()
		: position(glm::vec3(0.0f, 0.0f, -10.0f)), target(glm::vec3(0.0f, 0.0f, 0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f))
	{
	}

	Camera::~Camera()
	{
	}

	glm::vec3 Camera::getPosition() const
	{
		return position;
	}

	void Camera::setPosition(const glm::vec3& value)
	{
		position = value;
	}
	
	glm::vec3 Camera::getTarget() const
	{
		return target;
	}
	
	void Camera::setTarget(const glm::vec3& value)
	{
		target = value;
	}
	
	glm::vec3 Camera::getUp() const
	{
		return up;
	}
	
	void Camera::setUp(const glm::vec3& value)
	{
		up = value;
	}
	
	glm::mat4 Camera::getView() const
	{
		return view;
	}
	
	void Camera::setView(const glm::mat4& value)
	{
		view = value;
	}
	
	glm::mat4 Camera::getProjection() const
	{
		return projection;
	}
	
	void Camera::setProjection(float fov, float aspect, float near, float far)
	{
		projection = glm::perspective(glm::degrees(fov), aspect, near, far);
	}
}