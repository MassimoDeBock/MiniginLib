#pragma once
#include <Component.h>
#include <string>
#include <vector>
#include <memory>
#include "SDL_rect.h"
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

namespace dae {
	class SpriteGroup;
}
class MapComponent :
	public dae::Component
{
public:
	enum class TileTypeValues {
		Road = 0,
		Wall = 100
	};
	enum class DirectionValues {
		Right = 1,
		Down = 2,
		Left = 4,
		Up = 8,
	};
	enum class DiagonalDirectionValues {
		RightUp = 1,
		RightDown = 2,
		LeftDown = 4,
		LeftUp = 8,
	};

	MapComponent(const std::string& path, const std::string& spriteSheetPath);

	~MapComponent()override;

	void OnAssign()override;
	void Render()const override;
	glm::vec2 GetTileCenter(const int colX, const int rowY)const;
	glm::vec3 GetActorLocation();
	int GetDisplayValue(int colX, int rowY);
	int GetTileValue(int x, int y);

	bool IsValidTile(int colX, int rowY);

	const static int spriteDimension{ 32 };
private:



	void ReadMap(const std::string& path);

	glm::vec2 m_Dimensions{ spriteDimension,spriteDimension };

	void CalculateDisplayTiles();
	int CalcDisplayTile(int x, int y);
	int CalcDisplayTileRoad(int x, int y);
	int CalcDisplayTileWall(int x, int y);





	void LoadSprites();
	std::vector<std::vector<int>> m_Tile;
	std::vector<std::vector<int>> m_DisplayTile;	//[27][29];

	std::string m_SpriteSheetPath;
	std::shared_ptr<dae::SpriteGroup> m_SpriteGroup;

};
