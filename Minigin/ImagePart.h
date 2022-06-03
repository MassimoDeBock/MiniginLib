#pragma once


namespace dae {
	class Texture2D;
	class ImagePart
	{
	public:

		ImagePart(const std::string& filename, const SDL_Rect& snipRect);
		ImagePart(const std::string& filename, const glm::vec4& snipRect);
		ImagePart(const std::string& filename, float x, float y,	float w,	float h);
		ImagePart(const std::string& filename, int x,	int y,		int w,		int h);

		void SetTexture(const std::string& filename);
		void SetRect(const SDL_Rect& snipRect);
		void SetRect(const glm::vec4& snipRect);
		void SetRect(float x, float y, float w, float h);
		void SetRect(int x, int y, int w, int h);
		void Render(float x, float y) const;
	private:
		void Update();
		std::shared_ptr<Texture2D> m_Texture{};
		std::unique_ptr<Texture2D> m_TexturePart{};
		SDL_Rect m_SnipRect{};
	};

}