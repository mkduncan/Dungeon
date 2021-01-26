#ifndef Level_H
#define Level_H

#include "Model.hpp"

class Level
{
private:
	std::vector<std::vector<uint8_t>> Map;
	Model Mesh;

	static std::pair<size_t, size_t> GetSize(const uint16_t);

public:
	Level();
	~Level();
	Level(const Level&);
	Level(Level&&) noexcept = default;
	Level& operator=(const Level&);
	Level& operator=(Level&&) noexcept = default;

	bool Create(const uint16_t);
	bool Render(const Shader&) const;
	bool Destroy();
};

#endif