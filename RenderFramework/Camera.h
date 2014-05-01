#pragma once

#include "stdafx.h"

namespace RenderFramework
{
	class Camera
	{
	protected:
		// Position of the Camera
		glm::vec3 position;
		// Target of the Camera
		glm::vec3 target;
		// Orientation of the Camera
		glm::vec3 up;
		// View matrix defined for the Camera
		glm::mat4 view;
		// Projection matrix defined for the Camera
		glm::mat4 projection;

		Camera();
		virtual ~Camera();
	public:
		// Updates the Camera
		virtual void update(float deltaTime) = 0;

		glm::vec3 getPosition() const;
		void setPosition(const glm::vec3& value);
		glm::vec3 getTarget() const;
		void setTarget(const glm::vec3& value);
		glm::vec3 getUp() const;
		void setUp(const glm::vec3& value);
		glm::mat4 getView() const;
		void setView(const glm::mat4& value);
		glm::mat4 getProjection() const;
		void setProjection(float fov, float aspect, float near, float far);
	};

	class TargetCamera : public Camera
	{
	public:
		TargetCamera();
		~TargetCamera();

		// Updates the TargetCamera
		void update(float deltaTime);
	};
}