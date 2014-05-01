#include "stdafx.h"

#include "Camera.h"

namespace RenderFramework
{
	TargetCamera::TargetCamera()
		: Camera()
	{
	}
	

	TargetCamera::~TargetCamera()
	{
	}

	void TargetCamera::update(float deltaTime)
	{
		glm::vec3 forward = target - position;
		glm::vec3 side = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward);
		up = glm::cross(forward, side);
		up = glm::normalize(up);
		view = glm::lookAt(position, target, up);
	}
}