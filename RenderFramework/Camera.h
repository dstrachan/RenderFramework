#pragma once

#include "stdafx.h"

namespace RenderFramework
{
	class Camera
	{
	protected:
		glm::vec3 position;
		glm::vec3 target;
		glm::vec3 up;
		glm::mat4 view;
		glm::mat4 projection;

		Camera();
		~Camera();
	public:
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

		void update(float deltaTime);
	};
}