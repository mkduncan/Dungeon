#include "Header.hpp"

int main(int argc, char** argv)
{
	Shader shader;
	Texture texture;

	if (!Window::Open())
	{
		return 1;
	}

	else if (!shader.Create(Assets::Shaders[0], Assets::Shaders[1]))
	{
		Window::Close();
		return 2;
	}

	else if (!texture.Load(Assets::Textures[0], std::pair<size_t, size_t>(128, 256)))
	{
		shader.Destroy();
		Window::Close();

		return 3;
	}

	Level level;
	
	if (!level.Create(0))
	{
		Window::Close();
		shader.Destroy();
		texture.Destroy();

		return 3;
	}

	while (Window::Update())
	{
		Camera::Update();
		Camera::SetWorld(shader);
		texture.Use();
		level.Render(shader);
	}

	Window::Close();
	shader.Destroy();
	texture.Destroy();
	level.Destroy();

	return 0;
}
