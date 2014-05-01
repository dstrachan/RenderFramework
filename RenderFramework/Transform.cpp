#include "stdafx.h"

#include "Transform.h"

namespace RenderFramework
{
	Transform::Transform()
		: scale(glm::vec3(1.0f))
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::translate(const glm::vec3& value)
	{
		position += value;
	}

	void Transform::rotate(const glm::vec3& value)
	{
		glm::quat rotation(value);
		orientation *= rotation;
		orientation = glm::normalize(orientation);
	}

	void Transform::rotate(const glm::quat& value)
	{
		orientation *= value;
		orientation = glm::normalize(orientation);
	}

	glm::mat4 Transform::getTransformMatrix()
	{
		auto S = glm::scale(glm::mat4(1.0f), scale);
		auto R = glm::mat4_cast(orientation);
		auto T = glm::translate(glm::mat4(1.0f), position);
		return T * R * S;
	}

	glm::mat3 Transform::getNormalMatrix()
	{
		return glm::mat3_cast(orientation);
	}
}