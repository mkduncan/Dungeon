#ifndef Decoder_H
#define Decoder_H

#include <cstdint>
#include <utility>
#include <vector>

class Decoder
{
private:
	Decoder() = delete;
	~Decoder() = delete;
	Decoder(const Decoder&) = delete;
	Decoder(Decoder&&) = delete;
	Decoder& operator=(const Decoder&) = delete;
	Decoder& operator=(Decoder&&) = delete;

	static size_t LastIndex, CurrentIndex;

public:
	static std::vector<std::vector<uint8_t>> DecodeMap(const std::pair<size_t, size_t>&);
	static std::vector<uint8_t> DecodeTexture(const std::vector<uint8_t>&, const std::pair<size_t, size_t>&);
};

#endif