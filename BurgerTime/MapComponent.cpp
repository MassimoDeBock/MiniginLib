#include "MapComponent.h"

#include <SpriteGroup.h>
#include "ImagePart.h"
#include <Texture2D.h>
#include <fstream>
#include <iostream>
#include "ResourceManager.h"
#pragma warning(push, 0)
#include <SDL.h>
#pragma warning (pop)
#include <GameObject.h>




MapComponent::MapComponent(const std::string& mapPath, const std::string& spriteSheetPath)
	: m_SpriteSheetPath(spriteSheetPath)
{
	ReadMap(mapPath);
	LoadSprites();
	CalculateDisplayTiles();
}

MapComponent::~MapComponent()
{
}


void MapComponent::OnAssign()
{

}

void MapComponent::Render() const
{
	glm::vec3 rpos = m_GameObjectRef->GetAbsoluteTransform().GetPosition();
	//m_SpriteGroup.get()->GetSprite(int(int(2) + 0))->Render(rpos.x, rpos.y);
	for (int y = 0; y < m_DisplayTile.size(); ++y) {
		for (int x = 0; x < m_DisplayTile.at(y).size(); ++x) {
			//m_SpriteGroup.get()->GetSprite(unsigned int(int(m_DisplayTile.at(y).at(x))))->Render(rpos.x+x* m_Dimensions.x, rpos.y + y * m_Dimensions.y);
			m_SpriteGroup.get()->GetSprite(unsigned int(m_DisplayTile.at(y).at(x)))->Render(rpos.x + x * m_Dimensions.x, rpos.y + y * m_Dimensions.y);
		}
	}
}

glm::vec2 MapComponent::GetTileCenter(const int colX, const int rowY) const
{
	glm::vec3 rpos = m_GameObjectRef->GetAbsoluteTransform().GetPosition();
	return glm::vec2(rpos.x + ((float(colX) + 0.5f) * m_Dimensions.x), rpos.y + ((float(rowY) + 0.5f) * m_Dimensions.y));
}

glm::vec3 MapComponent::GetActorLocation()
{
	return m_GameObjectRef->GetAbsoluteTransform().GetPosition();
}

int MapComponent::GetDisplayValue(int colX, int rowY)
{

	return m_DisplayTile.at(rowY).at(colX);
}

bool MapComponent::IsValidTile(int colX, int rowY)
{
	if (!(m_DisplayTile.size() > rowY)) return false;
	if (!(m_DisplayTile.at(rowY).size() > colX)) return false;
	return true;
}

void MapComponent::ReadMap(const std::string& path)
{
	std::ifstream levelFile;
	std::string tempString;
	levelFile.open(path, std::ios::in);
	if (levelFile.is_open()) {
		bool foundMap{ false };
		while (levelFile && !foundMap) {
			levelFile >> tempString;
			if (tempString[0] == '#') {
				if (tempString.find("#GridBoundaries") != std::string::npos) {
					foundMap = true;
					std::cout << "gridfound" << std::endl;
				}
			}
		}
		while (levelFile && foundMap) {
			levelFile >> tempString;
			if (tempString[0] != '}') {
				m_Tile.push_back(std::vector<int>());
				//std::vector<int> tempVec;
				for (int i = 0; i < tempString.size(); ++i) {
					m_Tile.rbegin()->push_back(int(tempString[i]) - 48);
				}
			}
			else {
				foundMap = false;
			}
		}

	}
	else {
		std::cout << "couldn't open" << std::endl;
	}
	levelFile.close();

	for (std::vector<int> i : m_Tile) {
		for (int j : i) {
			std::cout << int(j);
		}
		std::cout << std::endl;
	}
}


void MapComponent::CalculateDisplayTiles()
{
	for (int y = 0; y < m_Tile.size(); ++y) {
		m_DisplayTile.push_back(std::vector<int>());
		for (int x = 0; x < m_Tile.at(y).size(); ++x) {
			m_DisplayTile.at(y).push_back(CalcDisplayTile(x, y));
		}
	}

	for (std::vector<int> i : m_DisplayTile) {
		for (int j : i) {
			std::cout << int(j) << '|';
		}
		std::cout << std::endl;
		std::cout << "======================================================" << std::endl;
	}
}

int MapComponent::CalcDisplayTile(int x, int y)
{
	int currTile = m_Tile.at(int(y)).at(int(x));

	if (currTile == 0) {
		//	std::cout << "wall" << std::endl;
		return CalcDisplayTileWall(x, y);
	}
	if (currTile == 1) {
		//	std::cout << "road" << std::endl;
		return CalcDisplayTileRoad(x, y);
	}

	return int();
}

int MapComponent::CalcDisplayTileRoad(int x, int y)
{

	int value{ 0 };
	const int desiredValue{ 1 };

	//std::cout << int(GetTileValue((int(x) + 0), (int(y) + 1))) << std::endl;
	//std::cout << m_Tile.at(y + 1).at(x) << std::endl;
	if (int(GetTileValue(x - 1, y + 0)) == desiredValue)  value += int(DirectionValues::Left);
	if (int(GetTileValue(x + 0, y + 1)) == desiredValue)  value += int(DirectionValues::Down);
	if (int(GetTileValue(x + 1, y + 0)) == desiredValue)  value += int(DirectionValues::Right);
	if (int(GetTileValue(x + 0, y - 1)) == desiredValue)  value += int(DirectionValues::Up);


	return value;
}

int MapComponent::CalcDisplayTileWall(int x, int y)
{
	int value{ 100 };
	const int desiredValue{ 0 };

	if (int(GetTileValue(x + 1, y - 1)) == desiredValue)  value += int(DiagonalDirectionValues::RightUp);
	if (int(GetTileValue(x + 1, y + 1)) == desiredValue)  value += int(DiagonalDirectionValues::RightDown);
	if (int(GetTileValue(x - 1, y + 1)) == desiredValue)  value += int(DiagonalDirectionValues::LeftDown);
	if (int(GetTileValue(x - 1, y - 1)) == desiredValue)  value += int(DiagonalDirectionValues::LeftUp);

	if (value == 107) { //empty topleft
		if (int(GetTileValue(x + 0, y - 1)) != desiredValue) value = 106; //top
		if (int(GetTileValue(x - 1, y + 0)) != desiredValue) value = 103; //left
	}
	else if (value == 111) { //empty botleft
		if (int(GetTileValue(x + 0, y + 1)) != desiredValue) value = 109; //bot
		if (int(GetTileValue(x - 1, y + 0)) != desiredValue) value = 103; //left
	}
	else if (value == 113) { //empty botright
		if (int(GetTileValue(x + 0, y + 1)) != desiredValue) value = 109; //bot
		if (int(GetTileValue(x + 1, y + 0)) != desiredValue) value = 112; //right
	}
	else if (value == 114) { //empty topright
		if (int(GetTileValue(x + 0, y - 1)) != desiredValue) value = 106; //top
		if (int(GetTileValue(x + 1, y + 0)) != desiredValue) value = 112; //right
	}
	else if (value == 115) {
		if (int(GetTileValue(x + 0, y - 1)) != desiredValue) value = 106; //top
		if (int(GetTileValue(x + 1, y + 0)) != desiredValue) value = 112; //right
		if (int(GetTileValue(x + 0, y + 1)) != desiredValue) value = 109; //bot
		if (int(GetTileValue(x - 1, y + 0)) != desiredValue) value = 103; //left
	}


	//std::cout << int(std::byte(value)) << std::endl;
	return value;
}

int MapComponent::GetTileValue(int x, int y)
{
	if (y < 0 || y >= m_Tile.size()) return 0;
	if (x < 0 || x >= m_Tile.at(int(y)).size()) return 0;
	//checking if below byte(0) is most likely redundant


	return m_Tile.at(y).at(x);
}



void MapComponent::LoadSprites()
{
	std::string newSpriteGroupName{ "TronSpriteSheet" };

	if (dae::ResourceManager::GetInstance().IsSpriteGroupLoaded(newSpriteGroupName)) {

		m_SpriteGroup = dae::ResourceManager::GetInstance().LoadSpriteGroup(newSpriteGroupName);
		return;
	}
	m_SpriteGroup = dae::ResourceManager::GetInstance().LoadSpriteGroup(newSpriteGroupName);
	for (int i = 0; i < 16; ++i) {
		m_SpriteGroup->InsertSprite(i, m_SpriteSheetPath, SDL_Rect(int(m_Dimensions.x) * i, int(m_Dimensions.y) * 0, int(m_Dimensions.x), int(m_Dimensions.y)));
	}
	for (int i = 100; i < 116; ++i) {
		m_SpriteGroup->InsertSprite(i, m_SpriteSheetPath, SDL_Rect(int(m_Dimensions.x) * (i - 100), int(m_Dimensions.y) * 1, int(m_Dimensions.x), int(m_Dimensions.y)));
	}


}
