#pragma once

#include "stdafx.h"

namespace RenderFramework
{
	class Transform
	{
	private:
		glm::vec3 scale;
		glm::quat orientation;
		glm::vec3 position;
	public:
		Transform();
		~Transform();

		void translate(const glm::vec3& value);
		void rotate(const glm::vec3& value);
		void rotate(const glm::quat& value);

		glm::mat4 getTransformMatrix();
		glm::mat3 getNormalMatrix();

		glm::vec3 getScale() const;
		void setScale(const glm::vec3& value);
		glm::quat getOrientation() const;
		void setOrientation(const glm::quat& value);
		glm::vec3 getPosition() const;
		void setPosition(const glm::vec3& value);
	};
}