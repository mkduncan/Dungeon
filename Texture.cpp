#include "Decoder.hpp"
#include "Texture.hpp"

Texture::Texture() : Id(0)
{
}

Texture::~Texture()
{
	if (this->Id != 0)
	{
		glDeleteTextures(1, &this->Id);
		this->Id = 0;
	}
}

Texture::Texture(const Texture &texture) : Id(texture.Id)
{
}

Texture& Texture::operator=(const Texture &texture)
{
	if (this->Id != 0)
	{
		glDeleteTextures(1, &this->Id);
	}

	this->Id = texture.Id;
	return *this;
}

bool Texture::Load(const std::vector<uint8_t> &data, const std::pair<size_t, size_t> &dimensions)
{
	std::vector<uint8_t> decodedData;
	size_t bytes = dimensions.first * dimensions.second * 3;

	if (this->Id != 0 || data.empty())
	{
		return false;
	}

	decodedData = Decoder::DecodeTexture(data, dimensions);

	if (decodedData.size() != bytes)
	{
		return false;
	}

	glGenTextures(1, &this->Id);
	glBindTexture(GL_TEXTURE_2D, this->Id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<GLsizei>(dimensions.first), static_cast<GLsizei>(dimensions.second), 0, GL_RGB, GL_UNSIGNED_BYTE, &decodedData[0]);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

bool Texture::Use() const
{
	if (this->Id == 0)
	{
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, this->Id);
	return true;
}

bool Texture::Destroy()
{
	if (this->Id == 0)
	{
		return false;
	}

	glDeleteTextures(1, &this->Id);
	this->Id = 0;

	return true;
}