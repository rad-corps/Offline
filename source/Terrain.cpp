#include "Terrain.h"
#include <iostream> //cout
#include <cstdlib> //abs
#include <algorithm>
#include "CONSTS.h"

using namespace std;

Terrain::Terrain(int w_, int h_)
{
	//init the textures
	textureGrass = CreateSprite("./resources/images/terrain_grass.png", TILE_SIZE, TILE_SIZE);
	textureWall = CreateSprite("./resources/images/terrain_wall.png", TILE_SIZE, TILE_SIZE);
	textureFloor = CreateSprite("./resources/images/terrain_floor.png", TILE_SIZE, TILE_SIZE);
	textureTrees = CreateSprite("./resources/images/terrain_tree.png", TILE_SIZE, TILE_SIZE);
	textureWater = CreateSprite("./resources/images/terrain_water.png", TILE_SIZE, TILE_SIZE);
	textureDoor = CreateSprite("./resources/images/terrain_door.png", TILE_SIZE, TILE_SIZE);


	for (int row = 0; row < h_; ++row)
	{
		vector<TerrainTile*> v;
		tileArray.push_back(v);

		for (int col = 0; col < w_; ++col)
		{
			tileArray[row].push_back(new TerrainTile(col, row, GRASS));
		}
	}

	drawType = TREE;
}

Terrain::~Terrain()
{
}


void Terrain::KeyStroke(SDL_Keycode key_) 
{
	if (key_ == SDLK_0)
		SetTileDrawType(GRASS);
	if (key_ == SDLK_1)
		SetTileDrawType(TREE);
	if (key_ == SDLK_2)
		SetTileDrawType(BUILDING_WALL);
	if (key_ == SDLK_3)
		SetTileDrawType(BUILDING_FLOOR);
	if (key_ == SDLK_4)
		SetTileDrawType(DOOR);
	if (key_ == SDLK_5)
		SetTileDrawType(WATER);
}

void Terrain::MouseClick(int mouseButton_)
{

}

void Terrain::MouseDown(int mouseButton_)
{
	if (mouseButton_ == 1)
	{
		//where is the mouse?
		int mouseX, mouseY;
		GetMouseLocation(mouseX, mouseY);

		//convert that to row/col coordinates
		TileAtMouseCoords(mouseX, mouseY)->type = drawType;
	}
}


void Terrain::SetTileDrawType(TERRAIN_TILE_TYPE type_)
{
	drawType = type_;
}

void Terrain::Draw(TERRAIN_TILE_TYPE type_, int row_, int col_)
{
	SDL_Texture* tempPtr = nullptr;

	switch (type_)
	{
		case GRASS:				tempPtr = textureGrass; break;
		case TREE:				tempPtr = textureTrees;	break;
		case BUILDING_WALL:		tempPtr = textureWall;	break;
		case BUILDING_FLOOR:	tempPtr = textureFloor;	break;
		case DOOR:				tempPtr = textureDoor;	break;
		case WATER:				tempPtr = textureWater;	break;
	}

	if (tempPtr == nullptr)
	{
		cout << "Unknown TERRAIN_TILE_TYPE in Terrain::Draw(TERRAIN_TILE_TYPE type_, int row_, int col_)" << endl;
		return;
	}

	MoveSprite(tempPtr, col_ * TILE_SIZE, row_ * TILE_SIZE);
	DrawSprite(tempPtr);
}

void Terrain::Update(float delta_)
{

}

void Terrain::Draw()
{
	for (int row = 0; row < tileArray.size(); ++row)
	{
		for (int col = 0; col < tileArray[0].size(); ++col)
		{
			//get the type
			Draw(tileArray[row][col]->type, row, col);
		}
	}
}

TerrainTile* Terrain::TileAt(int row_, int col_)
{
	//TODO bounds checking. 
	return tileArray[row_][col_];
}

TerrainTile* Terrain::TileAtMouseCoords(int x_, int y_)
{
	x_ /= TILE_SIZE;
	y_ /= TILE_SIZE;
	return TileAt(y_, x_);
}

void Terrain::SetTerrain(std::vector<TerrainTile*> tiles_, TERRAIN_TILE_TYPE type_)
{
	for (auto& tile : tiles_)
	{
		tile->type = type_;
	}
}

//SHORTEST PATH / ASTAR SPECIFIC CODE //
////////////////////////////////////////

//manhattan distance
int Terrain::Heuristic(TerrainTile* origin_, TerrainTile* dest_)
{
	int rowDif = abs(origin_->row - dest_->row);
	int colDif = abs(origin_->col - dest_->col);
	return rowDif + colDif;
}

std::vector<TerrainTile*> Terrain::Edges(TerrainTile* tile_)
{
	//temp vars for readability
	int row_ = tile_->row;
	int col_ = tile_->col;

	//the return value
	std::vector<TerrainTile*> ret;

	//add edge above
	if (row_ < tileArray.size() - 1)
	{
		ret.push_back(tileArray[row_ + 1][col_]);
	}
	//add edge below
	if (row_ > 0)
	{
		ret.push_back(tileArray[row_ - 1][col_]);
	}
	//add edge left
	if (col_ > 0)
	{
		ret.push_back(tileArray[row_][col_ - 1]);
	}
	//add edge right
	if (col_ < tileArray[row_].size() - 1)
	{
		ret.push_back(tileArray[row_][col_ + 1]);
	}

	return ret;
}

std::vector<TerrainTile*> Terrain::ShortestPath(TerrainTile* origin_, TerrainTile* dest_)
{
	std::vector<TerrainTile*> ret;	
	std::vector<TerrainTile*> closedList;
	std::vector<TerrainTile*> openList;
	TerrainTile* currentNode;
	
	origin_->g = 0;
	origin_->f = Heuristic(origin_, dest_);
	openList.push_back(origin_);


	while (!openList.empty())
	{
		//lowest f score node to go to front (use lambda as we dont want to compare Node pointer addresses) 
		std::sort(openList.begin(), openList.end(), [](TerrainTile* a, TerrainTile* b){return a->f < b->f; });

		//get the lowest f score node TODO: are we getting the lowest or highest here? test
		currentNode = openList[0];

		//remove the node from the open list
		openList.erase(openList.begin());

		//add it to the closed (traversed list) 
		closedList.push_back(currentNode);

			//if we have found the end node. 
		if (currentNode == dest_)
		{
			//success: bail from loop and create the return list
			break;
		}

		//loop through edges
		for (TerrainTile* edge : Edges(currentNode))
		{
			//if end node is not traversed (does not appear in closed list) 
			if (std::find(closedList.begin(), closedList.end(), edge) == closedList.end())
			{
				//calculate a tentative f cost of the edge's end node
				int tentativeF = currentNode->g + edge->Cost() + Heuristic(edge, dest_);

				//if the tentative f cost is less than the edge node's current f cost, update its data
				if (tentativeF < edge->f)
				{
					//update scores since we have found a new lower f cost for this node
					edge->parent = currentNode;
					edge->g = currentNode->g + edge->Cost();
					edge->f = tentativeF;

					//add it to the open list if it is not there already
					if (std::find(openList.begin(), openList.end(), edge) == openList.end())
					{
						openList.push_back(edge);
					}
				}
			}
		}
	}

	//could not find and we have searched the entire graph
	if (currentNode != dest_)
	{
		//RETURN FAILURE
		cout << "Could not find destination node" << endl;
		return ret; //empty
	}
	
	//reconstruct the path	
	do
	{
		ret.push_back(currentNode);
		currentNode = currentNode->parent;
	} while (currentNode != nullptr);

	//clean up 
	for (auto& row : tileArray)
	{
		for (auto& cell : row)
		{
			cell->Reset();
		}
	}

	return ret;
}

//END ASTAR SPECIFIC CODE