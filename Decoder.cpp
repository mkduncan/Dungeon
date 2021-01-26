#include "Decoder.hpp"
#include "Tilesets.hpp"

#define STB_HERRINGBONE_WANG_TILE_IMPLEMENTATION
#define STB_HBWANG_ASSERT
#define STB_HBWANG_MAX_X 512
#define STB_HBWANG_MAX_Y 512

#include "Alloc.h"
#include "LzmaDec.h"
#include "stb_herringbone_wang_tile.h"

size_t Decoder::LastIndex = 0, Decoder::CurrentIndex = 0;

std::vector<std::vector<uint8_t>> Decoder::DecodeMap(const std::pair<size_t, size_t>& dimensions)
{
	std::vector<std::vector<uint8_t>> decodedMap;
	std::vector<uint8_t> decodedTileSet, linearMap;
	stbhw_tileset tileSet = { 0, 0, 0, 0, 0, 0, 0, 0, nullptr, nullptr, 0, 0, 0, 0 };
	ELzmaStatus status = LZMA_STATUS_NOT_SPECIFIED;
	SizeT encodedSize = 0, decodedSize = 0, index = 0;
	SRes result = 0;
	Decoder::LastIndex = Decoder::CurrentIndex;

	while (Decoder::CurrentIndex == Decoder::LastIndex)
	{
		Decoder::CurrentIndex = (NextRandomIndex() % Tilesets::Maps.size()) + 1;
	}

	--Decoder::CurrentIndex;
	encodedSize = Tilesets::Maps[Decoder::CurrentIndex].size() - LZMA_PROPS_SIZE;
	decodedSize = (Tilesets::Size[Decoder::CurrentIndex].first * Tilesets::Size[Decoder::CurrentIndex].second) << 2;
	decodedTileSet.resize(decodedSize);
	result = LzmaDecode(&decodedTileSet[0], &decodedSize, &Tilesets::Maps[Decoder::CurrentIndex][LZMA_PROPS_SIZE], &encodedSize, &Tilesets::Maps[Decoder::CurrentIndex][0], LZMA_PROPS_SIZE, LZMA_FINISH_ANY, &status, &g_Alloc);

	if (result != SZ_OK)
	{
		return decodedMap;
	}

	decodedTileSet.resize(decodedSize);
	result = static_cast<size_t>(stbhw_build_tileset_from_image(&tileSet, &decodedTileSet[0], static_cast<int32_t>(Tilesets::Size[Decoder::CurrentIndex].first * 3), static_cast<int32_t>(Tilesets::Size[Decoder::CurrentIndex].first), static_cast<int32_t>(Tilesets::Size[Decoder::CurrentIndex].second)));

	if (result == 0)
	{
		stbhw_free_tileset(&tileSet);
		return decodedMap;
	}

	linearMap.resize(dimensions.first * dimensions.second * 3);
	result = stbhw_generate_image(&tileSet, nullptr, &linearMap[0], static_cast<int32_t>(dimensions.first) * 3, static_cast<int32_t>(dimensions.first), static_cast<int32_t>(dimensions.second));

	if (result == 0)
	{
		stbhw_free_tileset(&tileSet);
		return decodedMap;
	}

	stbhw_free_tileset(&tileSet);
	decodedTileSet.clear();

	decodedMap = std::vector<std::vector<uint8_t>>(dimensions.second + 4, std::vector<uint8_t>(dimensions.first + 4, Tilesets::TILE_OPEN));
	decodedMap[0] = std::vector<uint8_t>(dimensions.first + 4, Tilesets::TILE_EMPTY);
	decodedMap[dimensions.first + 3] = decodedMap[0];

	for (size_t row = 1; row < dimensions.second + 3; ++row)
	{
		decodedMap[row][0] = Tilesets::TILE_EMPTY;
		decodedMap[row][dimensions.second + 3] = Tilesets::TILE_EMPTY;
	}

	for (size_t row = 0; row < dimensions.second; ++row)
	{
		for (size_t column = 0; column < dimensions.first; ++column)
		{
			if (linearMap[index] == 255 && linearMap[index + 1] == 255 && linearMap[index + 2] == 255)
			{
				decodedMap[row + 2][column + 2] = Tilesets::TILE_EMPTY;
			}

			else if (linearMap[index] != 255 || linearMap[index + 1] != 255 || linearMap[index + 2] != 255)
			{
				decodedMap[row + 2][column + 2] = Tilesets::TILE_OPEN;
			}

			index += 3;
		}
	}

	return decodedMap;
}

std::vector<uint8_t> Decoder::DecodeTexture(const std::vector<uint8_t> &encodedData, const std::pair<size_t, size_t> &dimensions)
{
	std::vector<uint8_t> decodedData = std::vector<uint8_t>((dimensions.first * dimensions.second) << 2, 0);
	ELzmaStatus status = LZMA_STATUS_NOT_SPECIFIED;
	SizeT encodedSize = encodedData.size() - LZMA_PROPS_SIZE, decodedSize = decodedData.size();
	SRes result = LzmaDecode(&decodedData[0], &decodedSize, &encodedData[LZMA_PROPS_SIZE], &encodedSize, &encodedData[0], LZMA_PROPS_SIZE, LZMA_FINISH_ANY, &status, &g_Alloc);

	if (result != SZ_OK)
	{
		decodedData.clear();
		return decodedData;
	}

	decodedData.resize(decodedSize);
	return decodedData;
}