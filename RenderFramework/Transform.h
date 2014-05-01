#pragma once

#include "stdafx.h"

namespace RenderFramework
{
	struct Transform
	{
		// Scale of the Transform
		glm::vec3 scale;
		// Orientation of the Transform
		glm::quat orientation;
		// Position of the Transform
		glm::vec3 position;

		Transform();
		~Transform();

		// Translates the Transform by a given vector
		void translate(const glm::vec3& value);
		// Rotates the Transform by a given vector
		void rotate(const glm::vec3& value);
		// Rotates the Transform by a given quaternion
		void rotate(const glm::quat& value);

		// Returns the 4x4 transform matrix for the Transform
		glm::mat4 getTransformMatrix();
		// Returns the 3x3 normal matrix for the Transform
		glm::mat3 getNormalMatrix();
	};
}