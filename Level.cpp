#include "Decoder.hpp"
#include "Level.hpp"
#include "Tilesets.hpp"

std::pair<size_t, size_t> Level::GetSize(const uint16_t level)
{
	return std::pair<size_t, size_t>(128, 128);
}

Level::Level() : Map(std::vector<std::vector<uint8_t>>()), Mesh(Model())
{
}

Level::~Level()
{
	this->Map.clear();
	this->Mesh.Destroy();
}

Level::Level(const Level& level) : Map(level.Map), Mesh(level.Mesh)
{
}

Level& Level::operator=(const Level &level)
{
	this->Map = level.Map;
	this->Mesh = level.Mesh;

	return *this;
}

bool Level::Create(const uint16_t level)
{
	const float scale = 1.33333333f, height = 0.5f;
	float xAlpha = 0.0f, xBeta = 0.0f, zAlpha = 0.0f, zBeta = 0.0f;

	if (!this->Map.empty())
	{
		this->Map.clear();

		if (!this->Mesh.Destroy())
		{
			return false;
		}
	}

	this->Map = Decoder::DecodeMap(Level::GetSize(level));

	for (size_t row = 0; row < this->Map.size(); ++row)
	{
		xAlpha = static_cast<float>(row) * scale;
		xBeta = xAlpha + scale;

		for (size_t column = 0; column < this->Map[row].size(); ++column)
		{
			if (this->Map[row][column] == Tilesets::TILE_OPEN)
			{
				zAlpha = static_cast<float>(column) * scale;
				zBeta = zAlpha + scale;

				if (!this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, -height, zAlpha), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)))
					|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, -height, zAlpha), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)))
					|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, -height, zBeta), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.5f)))
					|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, -height, zAlpha), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)))
					|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, -height, zBeta), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.5f)))
					|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, -height, zBeta), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.5f)))
					|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, height, zAlpha), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)))
					|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, height, zAlpha), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)))
					|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, height, zBeta), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.5f)))
					|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, height, zAlpha), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)))
					|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, height, zBeta), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.5f)))
					|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, height, zBeta), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.5f))))
				{
					this->Map.clear();
					this->Mesh.Destroy();

					return false;
				}

				if (this->Map[row - 1][column] == Tilesets::TILE_EMPTY)
				{
					if (!this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, -height, zAlpha), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.5f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, -height, zBeta), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.5f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, height, zBeta), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, height, zBeta), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, height, zAlpha), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, -height, zAlpha), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.5f))))
					{
						this->Map.clear();
						this->Mesh.Destroy();

						return false;
					}
				}

				if (this->Map[row][column - 1] == Tilesets::TILE_EMPTY)
				{
					if (!this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, -height, zAlpha), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, height, zAlpha), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.5f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, -height, zAlpha), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, -height, zAlpha), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, height, zAlpha), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.5f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, height, zAlpha), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.5f))))
					{
						this->Map.clear();
						this->Mesh.Destroy();

						return false;
					}
				}

				if (this->Map[row + 1][column] == Tilesets::TILE_EMPTY)
				{
					if (!this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, -height, zAlpha), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.5f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, -height, zBeta), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.5f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, height, zBeta), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, height, zBeta), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, height, zAlpha), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, -height, zAlpha), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.5f))))
					{
						this->Map.clear();
						this->Mesh.Destroy();

						return false;
					}
				}

				if (this->Map[row][column + 1] == Tilesets::TILE_EMPTY)
				{
					if (!this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, -height, zBeta), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, height, zBeta), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.5f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, -height, zBeta), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, -height, zBeta), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xBeta, height, zBeta), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.5f)))
						|| !this->Mesh.AddVertex(Vertex(glm::vec3(xAlpha, height, zBeta), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.5f))))
					{
						this->Map.clear();
						this->Mesh.Destroy();

						return false;
					}
				}
			}
		}
	}

	if (!this->Mesh.Create())
	{
		this->Map.clear();
		this->Mesh.Destroy();

		return false;
	}

	return true;
}

bool Level::Render(const Shader &shader) const
{
	if (!this->Mesh.Render(shader))
	{
		return false;
	}

	return true;
}

bool Level::Destroy()
{
	this->Map.clear();

	if (!this->Mesh.Destroy())
	{
		return false;
	}

	return true;
}