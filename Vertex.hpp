#ifndef Vertex_H
#define Vertex_H

#include "glm.hpp"

class Vertex
{
private:
	glm::vec3 Position, Normal;
	glm::vec2 Texture;

	friend class Model;

public:
	Vertex();
	~Vertex();
	Vertex(const Vertex&);
	Vertex(Vertex&&) noexcept = default;
	Vertex(const glm::vec3&, const glm::vec3&, const glm::vec2&);
	Vertex& operator=(const Vertex&);
	Vertex& operator=(Vertex&&) noexcept = default;

	bool Normalize();
};

#endif