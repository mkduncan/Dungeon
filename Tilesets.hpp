#ifndef Tilesets_H
#define Tilesets_H

#include <cstdint>
#include <utility>
#include <vector>

class Tilesets
{
private:
	Tilesets() = delete;
	~Tilesets() = delete;
	Tilesets(const Tilesets&) = delete;
	Tilesets(Tilesets&&) = delete;
	Tilesets& operator=(const Tilesets&) = delete;
	Tilesets& operator=(Tilesets&&) = delete;

	static std::vector<std::vector<uint8_t>> Maps;
	static std::vector<std::pair<size_t, size_t>> Size;

	friend class Decoder;

public:
	typedef enum
	{
		TILE_EMPTY = '.',
		TILE_OPEN = '#'

	} TileType;
};

#endif