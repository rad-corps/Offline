#include "Terrain.h"
#include <iostream> //cout
#include <cstdlib> //abs
#include <algorithm>

//std::map<TERRAIN_TILE_TYPE, SDL_Texture*> Terrain::textureMap;
using namespace std;

Terrain::Terrain()
{
	//init the textures
	textureGrass = CreateSprite("./resources/images/terrain_grass.png", 16, 16);
	textureWall = CreateSprite("./resources/images/terrain_wall.png", 16, 16);
	textureFloor = CreateSprite("./resources/images/terrain_floor.png", 16, 16);
	textureTrees = CreateSprite("./resources/images/terrain_tree.png", 16, 16);
	textureWater = CreateSprite("./resources/images/terrain_water.png", 16, 16);
	textureDoor = CreateSprite("./resources/images/terrain_door.png", 16, 16);


	for (int row = 0; row < 32; ++row)
	{
		vector<TerrainTile*> v;
		tileArray.push_back(v);

		for (int col = 0; col < 32; ++col)
		{
			tileArray[row].push_back(new TerrainTile(col, row, GRASS));
		}
	}

	tileArray[1][1]->type = BUILDING_WALL;
}

Terrain::~Terrain()
{
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

	MoveSprite(tempPtr, col_ * 16, row_ * 16);
	DrawSprite(tempPtr);
}

void Terrain::Update(float delta_)
{
	//where is the mouse?
	int mouseX, mouseY;
	GetMouseLocation(mouseX, mouseY);

	//check for mouse left click (src)
	if (GetMouseButtonDown(0))
	{
		cout << "LMB Clicked" << endl;

		//convert that to row/col coordinates
		TileAtMouseCoords(mouseX, mouseY)->type = DOOR;
	}

	//check for mouse right click (dst)
	if (GetMouseButtonDown(1))
	{
		cout << "RMB Clicked" << endl;

		//convert that to row/col coordinates
		TileAtMouseCoords(mouseX, mouseY)->type = WATER;
	}

	if (IsKeyDown(SDLK_SPACE))
	{
		//find the tile with the water and door terrains. (insert hax here)
		TerrainTile* src = nullptr;
		TerrainTile* dst = nullptr;
		for (auto & row : tileArray)
		{
			for (auto & cell : row)
			{
				if (cell->type == DOOR)
					src = cell;
				if (cell->type == WATER)
					dst = cell;
			}
		}

		//run aStar on it. 
		if (src != nullptr && dst != nullptr)
		{
			SetTerrain(ShortestPath(src, dst), TREE);		
		}
	}
}

void Terrain::Draw()
{
	for (int row = 0; row < 32; ++row)
	{
		for (int col = 0; col < 32; ++col)
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
	x_ /= 16;
	y_ /= 16;
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
				int tentativeF = currentNode->g + edge->cost + Heuristic(edge, dest_);

				//if the tentative f cost is less than the edge node's current f cost, update its data
				if (tentativeF < edge->f)
				{
					//update scores since we have found a new lower f cost for this node
					edge->parent = currentNode;
					edge->g = currentNode->g + edge->cost;
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