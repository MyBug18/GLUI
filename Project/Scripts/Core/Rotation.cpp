#include <glm/glm.hpp>
#include "Rotation.h"

const glm::mat4 MultiplyToMatrix(glm::vec4 u, glm::vec4 v)
{
	return glm::transpose(glm::mat4(u.x * v, u.y * v, u.z * v, u.w * v));
}

const glm::mat3 MultiplyToMatrix(glm::vec3 u, glm::vec3 v)
{
	return glm::transpose(glm::mat3(u.x * v, u.y * v, u.z * v));
}

const glm::mat4 Rotation::GetRotationMatrix(glm::vec4 from, glm::vec4 to)
{
	const auto& i = glm::mat4(1.0f);

	const auto& uplusv = glm::mat4(1.0f / (1.0f + glm::dot(from, to))) * MultiplyToMatrix(from + to, from + to);

	const auto& uv = glm::mat4(2.0f) * MultiplyToMatrix(to, from);

	return i - uplusv + uv;
}

const glm::mat3 Rotation::GetRotationMatrix(glm::vec3 from, glm::vec3 to)
{
	const auto& i = glm::mat3(1.0f);

	const auto& uplusv = glm::mat3(1.0f / (1.0f + glm::dot(from, to))) * MultiplyToMatrix(from + to, from + to);

	const auto& uv = glm::mat3(2.0f) * MultiplyToMatrix(to, from);

	return i - uplusv + uv;
}
