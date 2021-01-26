#ifndef Texture_H
#define Texture_H

#include <cstdint>
#include <utility>
#include <vector>

#include "glad.h"

class Texture
{
private:
	GLuint Id;

public:
	Texture();
	~Texture();
	Texture(const Texture&);
	Texture(Texture&&) noexcept = default;
	Texture& operator=(const Texture&);
	Texture& operator=(Texture&&) noexcept = default;

	bool Load(const std::vector<uint8_t>&, const std::pair<size_t, size_t>&);
	bool Use() const;
	bool Destroy();
};

#endif