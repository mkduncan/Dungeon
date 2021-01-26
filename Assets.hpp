#ifndef Assets_H
#define Assets_H

#include <cstdint>
#include <string>
#include <vector>

class Assets
{
private:
	Assets() = delete;
	~Assets() = delete;
	Assets(const Assets&) = delete;
	Assets(Assets&&) = delete;
	Assets& operator=(const Assets&) = delete;
	Assets& operator=(Assets&&) = delete;

public:
	static std::vector<std::string> Shaders;
	static std::vector<std::vector<uint8_t>> Textures;
};

#endif