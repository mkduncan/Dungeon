#include "Model.hpp"

Model::Model() : Vertices(std::vector<Vertex>()), Array(0), Buffer(0), Index(0)
{
}

Model::~Model()
{
	this->Vertices.clear();

	if (this->Array != 0 || this->Buffer != 0 || this->Index != 0)
	{
		glDeleteVertexArrays(1, &this->Array);
		glDeleteBuffers(1, &this->Buffer);
		glDeleteBuffers(1, &this->Index);

		this->Array = 0;
		this->Buffer = 0;
		this->Index = 0;
	}
}

Model::Model(const Model &model) : Vertices(model.Vertices), Array(model.Array), Buffer(model.Buffer), Index(model.Index)
{
}

Model& Model::operator=(const Model &model)
{
	if (this->Array != 0 || this->Buffer != 0 || this->Index != 0)
	{
		glDeleteVertexArrays(1, &this->Array);
		glDeleteBuffers(1, &this->Buffer);
		glDeleteBuffers(1, &this->Index);
	}

	this->Vertices = model.Vertices;
	this->Array = model.Array;
	this->Buffer = model.Buffer;
	this->Index = model.Index;

	return *this;
}

bool Model::AddVertex(const Vertex &vertex)
{
	if (this->Array != 0 || this->Buffer != 0 || this->Index != 0)
	{
		return false;
	}

	this->Vertices.push_back(vertex);

	if (!this->Vertices.back().Normalize())
	{
		return false;
	}

	return true;
}

bool Model::Create()
{
	std::vector<GLuint> indices;

	if (this->Vertices.empty() || this->Array != 0 || this->Buffer != 0 || this->Index != 0)
	{
		return false;
	}

	indices.resize(this->Vertices.size());

	for (size_t index = 0; index < this->Vertices.size(); ++index)
	{
		indices[index] = static_cast<GLuint>(index);
	}

	glGenVertexArrays(1, &this->Array);
	glGenBuffers(1, &this->Buffer);
	glGenBuffers(1, &this->Index);
	glBindVertexArray(this->Array);
	glBindBuffer(GL_ARRAY_BUFFER, this->Buffer);
	glBufferData(GL_ARRAY_BUFFER, this->Vertices.size() * sizeof(Vertex), &this->Vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->Index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Texture));
	glBindVertexArray(0);

	return true;
}

bool Model::Render(const Shader &shader) const
{
	if (this->Array == 0 || this->Buffer == 0 || this->Index == 0 || !shader.Use())
	{
		return false;
	}

	glBindVertexArray(this->Array);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->Vertices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	return true;
}

bool Model::Destroy()
{
	Vertices.clear();

	if (this->Array != 0 || this->Buffer != 0 || this->Index != 0)
	{
		glDeleteVertexArrays(1, &this->Array);
		glDeleteBuffers(1, &this->Buffer);
		glDeleteBuffers(1, &this->Index);

		this->Array = 0;
		this->Buffer = 0;
		this->Index = 0;
	}

	return true;
}