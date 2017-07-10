/*************************************************************************
File name: level.cpp
Description: Handles the level data
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include "level.h"
#include "graphics.h"
#include <SDL.h>
#include "globals.h"
#include "tinyxml2.h"
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace tinyxml2;	//similar to scoping: (std::___); will give access to all the tinyxml2 functions

/*************************************************************************
Constructors and Deconstructors
**************************************************************************/
Level::Level() {}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
	_sMapName(mapName),
	_v2SpawnPoint(spawnPoint),
	_v2Size(Vector2::Zero())
{
	this->LoadMap(mapName, graphics);
}
Level::~Level() {

}
/*************************************************************************
Functions
**************************************************************************/
void Level::Update(int elapsedTime) {

}

void Level::Draw(Graphics &graphics) {
	//loop throguh all the loaded tiles and draw them
	for(int i = 0; i< this->_vTileList.size(); i++){ 
		this->_vTileList.at(i).Draw(graphics);
	}
}

/*void LoadMap
*Loads a map
*/
void Level::LoadMap(std::string mapName, Graphics &graphics) {
	//parse the .tmx file
	//note:tinyxml2 runs on C, so no strings, just chars
	XMLDocument doc;	//represents the .tmx document
	std::stringstream ss;	//to build a filepath string to the tmx doc

	ss << "Content/Maps/" << mapName << ".tmx";	//create the filepath
	//Ex: pass in "Map 1" mapName and we get Content/Maps/Map 1.tmx

	doc.LoadFile(ss.str().c_str());	//doc.LoadFile takes a const char* so we have to convert the stirng to a c string(char)

	//check the .tmx file for the element names
	//first element to grab is the "map"
	XMLElement* mapNode = doc.FirstChildElement("map");

	//in the map element in the .tmx file, it has a couple of attributes we're looking for

	//Now get the width and height of the whole map and store it
	//temp variables
	int width = 0;
	int height = 0; 

	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	this->_v2Size = Vector2(width, height);	//now we have the size of the map

	//Now get the width and height of the tiles and store it
	//temp variables
	int tileWidth = 0; 
	int tileHeight = 0;

	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	this->_v2TileSize = Vector2(tileWidth, tileHeight);	//now we have the size of the map

	//Loading the tilesets...

	//map(current node) -> tileset (child)
	XMLElement* pTileset = mapNode->FirstChildElement("tileset");	//get the first tileset

	if (pTileset != NULL) {
		while (pTileset) {
			//temp variables
			int firstgid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");
			char* path;

			//Get the path to the tileset source
			std::stringstream ss;
			ss << "Content/Tilesets/" << source;

			//Grab the first gid
			pTileset->QueryIntAttribute("firstgid", &firstgid);

			//Create the SDL texture of the tileset .png
			SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.GetRenderer(), graphics.LoadImage(ss.str()));

			//Add to vector of loaded tilesets
			this->_vTilesets.push_back(Tileset(tex, firstgid));

			pTileset = pTileset->NextSiblingElement("tileset"); //Attempt to retrieve additional tilesets if there are more
		}
	}
	//Done loading tilesets
	//Now loading layers...
	XMLElement* pLayer = mapNode->FirstChildElement("layer"); //map -> layer

	//using similar logic for the tilesets, grab each layer
	if (pLayer != NULL) {
		while (pLayer) {
			//loading the data element
			XMLElement* pData = pLayer->FirstChildElement("data"); //layer -> data

			//now use similar logic to grab each data
			if (pData != NULL) {
				while (pData) {
					//loading the tile element
					XMLElement* pTile = pData->FirstChildElement("tile");

					//finally, now use similar logic to grab each tile
					if (pTile != NULL) {
						int tileCounter = 0;
						while (pTile) {
							//build each individual tile here, gid of 0 = no tile so continue loop
							if (pTile->IntAttribute("gid") != 0) {
								//tile detected
								int gid = pTile->IntAttribute("gid");
								Tileset tls;

								//determine which tileset the tile comes from
								for (int i = 0; i < this->_vTilesets.size(); i++) {
									if (this->_vTilesets[i].FirstGid <= gid) {
										//this is the tileset we want
										tls = this->_vTilesets.at(i);
										break;
									}
								}

								//Check if the tileset exists for the gid
								if (tls.FirstGid != -1) {
									//successfully found tileset

									//Get the position of tile in the level
									int xx = 0;
									int yy = 0;
									xx = tileCounter % width; //modulus math
									xx *= tileWidth; //now to scale
									yy += tileHeight * (tileCounter / width);

									Vector2 finalTilePosition = { xx,yy }; //Got the tile's level position

									//Get the position of the tile in the tileset...
									int tilesetWidth, tilesetHeight;
									//Query the tileset tog et its width and height
									//SDL_QueryTexture will define the supplied w and h pointers
									SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);

									int tsxx = gid % (tilesetWidth / tileWidth) - 1; //calculating the correct tile based on gid
									tsxx *= tileWidth; //now scale the position back to size

									//now for the y position
									int tsyy = gid / (tilesetWidth / tileWidth);
									tsyy *= tileHeight; //now scaled back to size

									Vector2 finalTilesetPosition = { tsxx,tsyy };

									//Build the actual tile and add it to the level's tile list
									Tile tile = Tile(tls.Texture, _v2TileSize, finalTilesetPosition, finalTilePosition);
									_vTileList.push_back(tile);
								}
							}

							tileCounter++;
							pTile = pTile->NextSiblingElement("tile");	//to the next tile!
						}
					}

					pData = pData->NextSiblingElement("data"); //to the next data!
				}
			}

			pLayer = pLayer->NextSiblingElement("layer"); //to the next layer!
		}
	}
}