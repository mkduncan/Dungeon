#ifndef Model_H
#define Model_H

#include <vector>

#include "glad.h"
#include "Shader.hpp"
#include "Vertex.hpp"

class Model
{
private:
	std::vector<Vertex> Vertices;
	GLuint Array, Buffer, Index;

public:
	Model();
	~Model();
	Model(const Model&);
	Model(Model&&) noexcept = default;
	Model& operator=(const Model&);
	Model& operator=(Model&&) noexcept = default;

	bool AddVertex(const Vertex&);
	bool Create();
	bool Render(const Shader&) const;
	bool Destroy();
};

#endif