#pragma once

#include <glm/glm.hpp>

class Rotation
{
public:
	Rotation() = delete;
	static inline const glm::vec3 BaseRotation3d = glm::vec3(1, 0, 0);
	static inline const glm::vec3 BaseRotation4d = glm::vec4(1, 0, 0, 0);

	static const glm::mat4 GetRotationMatrix(glm::vec4, glm::vec4);
	static const glm::mat3 GetRotationMatrix(glm::vec3, glm::vec3);
};
