/*************************************************************************
File name: level.cpp
Description: Handles the level data
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include "level.h"
#include "graphics.h"
#include "globals.h"
#include "utils.h"

#include "tinyxml2.h"

#include <SDL.h>
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
	for (int i = 0; i < _vAnimatedTiles.size(); i++) {
		_vAnimatedTiles.at(i).Update(elapsedTime);
	}
}

void Level::Draw(Graphics &graphics) {
	//loop throguh all the loaded tiles and draw them
	for (int i = 0; i < this->_vTileList.size(); i++) {
		this->_vTileList.at(i).Draw(graphics);
	}

	for (int i = 0; i < _vAnimatedTiles.size(); i++) {
		_vAnimatedTiles.at(i).Draw(graphics);
	}
}

//Vector2 GetTilesetPosition
//calculates tile's position on the tileset texture
Vector2 Level::GetTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight) {
	int tilesetWidth, tilesetHeight;
	//Query the tileset to get its width and height
	//SDL_QueryTexture will define the supplied w and h pointers
	SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);

	int tsxx = (gid - 1) % (tilesetWidth / tileWidth); //calculating the correct tile based on gid
	tsxx *= tileWidth; //now scale the position back to size

	//now for the y position
	int tsyy = (gid - tls.FirstGid) / (tilesetWidth / tileWidth);
	tsyy *= tileHeight; //now scaled back to size

	return Vector2{ tsxx,tsyy };
}

//Checks if <other> object collided with a tile
std::vector<Rectangle> Level::CheckTileCollisions(const Rectangle &other) {
	std::vector<Rectangle> others;	//placeholder for colldied objects

	//Check if the rectangle collides with any collidable objects
	for (int i = 0; i < this->_vCollisionRects.size(); i++) {
		if (this->_vCollisionRects.at(i).CollidesWidth(other)) {
			others.push_back(this->_vCollisionRects.at(i));
		}
	}

	return others;
}

//Checks if <other> object collided with a slope
std::vector<Slope> Level::CheckSlopeCollisions(const Rectangle &other) {
	std::vector<Slope> others;
	for (int i = 0; i < this->_vSlopes.size(); i++) {
		if (this->_vSlopes.at(i).CollidesWith(other)) {
			others.push_back(this->_vSlopes.at(i));
		}
	}

	return others;
}

/*void LoadMap
*Loads a map
*/
void Level::LoadMap(std::string mapName, Graphics &graphics) {
	//parse the .tmx file
	//note:tinyxml2 runs on C, so no strings, just chars
	XMLDocument doc;	//represents the .tmx document
	std::stringstream ssPath;	//to build a filepath string to the tmx doc

	ssPath << "Content/Maps/" << mapName << ".tmx";	//create the filepath
	//Ex: pass in "Map 1" mapName and we get Content/Maps/Map 1.tmx

	doc.LoadFile(ssPath.str().c_str());	//doc.LoadFile takes a const char* so we have to convert the stirng to a c string(char)

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

			//Get the path to the tileset source
			std::stringstream ssSource;
			ssSource << "Content/Tilesets/" << source;

			//Grab the first gid
			pTileset->QueryIntAttribute("firstgid", &firstgid);

			//Create the SDL texture of the tileset .png
			SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.GetRenderer(), graphics.LoadImage(ssSource.str()));

			//Add to vector of loaded tilesets
			this->_vTilesets.push_back(Tileset(tex, firstgid));

			//check if the set has animations
			XMLElement* pTileAni = pTileset->FirstChildElement("tile");	//tileset ->tile
			while (pTileAni) {
				AnimatedTileInfo ati;
				ati.StartTileID = pTileAni->IntAttribute("id") + firstgid;
				ati.TilesetsFirstGid = firstgid;

				//keep moving till we get to frame
				XMLElement* pAnimation = pTileAni->FirstChildElement("animation");	//tileset -> tile -> animation
				if (pAnimation != NULL) {
					while (pAnimation) {
						XMLElement* pFrame = pAnimation->FirstChildElement("frame");//tileset -> tile -> animation ->frame
						while (pFrame) {
							ati.TileIds.push_back(pFrame->IntAttribute("tileid") + firstgid);
							ati.Duration = pFrame->IntAttribute("duration");

							pFrame = pFrame->NextSiblingElement("frame");	//check for more frames
						}

						pAnimation = pAnimation->NextSiblingElement("animation"); //check for more animations
					}
				}

				this->_vAnimatedTileInfos.push_back(ati);
				pTileAni = pTileAni->NextSiblingElement("tile"); //check if other tiles have animations
			}

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
								int closestGID = 0;
								//determine which tileset the tile comes from
								for (int i = 0; i < this->_vTilesets.size(); i++) {
									if (this->_vTilesets[i].FirstGid <= gid &&		//check if the FirstGID is within the tile's GID
										this->_vTilesets[i].FirstGid > closestGID)	//now compare this tileset's FirstGid "closeness" to the closest tileset's FirstGid
									{
										closestGID = this->_vTilesets[i].FirstGid;
										tls = this->_vTilesets.at(i);
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
									Vector2 finalTilesetPosition = this->GetTilesetPosition(tls, gid, tileWidth, tileHeight);

									//Check to see if tile is an animated tile
									bool isAnimatedTile = false;	//flag for tile being an animated tile
									AnimatedTileInfo ati;			//temporary placeholder

									//loop through all the stored atis and check their ID to this current tile's ID
									for (int i = 0; i < this->_vAnimatedTileInfos.size(); i++) {
										if (this->_vAnimatedTileInfos.at(i).StartTileID == gid) {
											isAnimatedTile = true;
											ati = this->_vAnimatedTileInfos.at(i);
											break;
										}
									}

									//Build the actual tile and add it to the level's tile list
									if (isAnimatedTile) {
										//Animated tile...
										std::vector<Vector2> tilesetPositions;
										for (int i = 0; i < ati.TileIds.size(); i++) {
											tilesetPositions.push_back(GetTilesetPosition(tls,ati.TileIds.at(i),tileWidth,tileHeight));
										}

										AnimatedTile animatedTile = AnimatedTile(tilesetPositions, ati.Duration, tls.Texture, Vector2(tileWidth, tileHeight), finalTilePosition);
										_vAnimatedTiles.push_back(animatedTile);
									}
									else {
										//Regular tile...
										Tile tile = Tile(tls.Texture, _v2TileSize, finalTilesetPosition, finalTilePosition);
										_vTileList.push_back(tile);
									}
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

	//Parse out the collisions
	//tinyxml2 stores them in "objectgroups"
	XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
	if (pObjectGroup != NULL) {
		while (pObjectGroup) {
			//check if the name of the objectgroup
			const char* name = pObjectGroup->Attribute("name");
			std::stringstream ssCollisions;
			ssCollisions << name;
			if (ssCollisions.str() == "collisions") {
				//found the level collision objects
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						//now parse the collision object into collision rectangles
						float x, y, width, height;
						x = pObject->FloatAttribute("x");
						y = pObject->FloatAttribute("y");
						width = pObject->FloatAttribute("width");
						height = pObject->FloatAttribute("height");
						this->_vCollisionRects.push_back(Rectangle(
							std::ceil(x) * globals::SPRITE_SCALE,
							std::ceil(y) * globals::SPRITE_SCALE,
							std::ceil(width) * globals::SPRITE_SCALE,
							std::ceil(height) * globals::SPRITE_SCALE
						));


						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			//Other objectgroups go here with an else if(ssCollisions.str()=="thing"){}
			//parse ground slopes
			else if (ssCollisions.str() == "ground slopes") {	//object group "slopes"
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						XMLElement* pPolyline = pObject->FirstChildElement("polyline");
						std::vector<Vector2> vPoints;	//holds all the points in the object

						//Grab the first point in the slope
						Vector2 p1;
						p1 = Vector2(std::ceil(pObject->FloatAttribute("x")), std::ceil(pObject->FloatAttribute("y")));

						//Now to get the other point(s)
						//Polyline values in the .tmx indicate the offset added to the initial (x,y) attributes to get the next set of points
						if (pPolyline != NULL) {
							std::vector<std::string> pairs;
							const char* pointString = pPolyline->Attribute("points");
							std::stringstream ssPoints;
							ssPoints << pointString;

							Utils::Split(ssPoints.str(), pairs, ' ');
							//Now <pairs> has been populated with the offset pairs of values
							//Loop through the pairs and add them to the initial (x,y) to get the point coordinates
							//Now split them into Vector2s and then store them in our points vector
							for (int i = 0; i < pairs.size(); i++) {
								std::vector<std::string> pointOffset;
								Utils::Split(pairs.at(i), pointOffset, ',');
								//ps[0] will now have x offset. ps[1] with y offset
								vPoints.push_back(Vector2(
									std::stoi(pointOffset.at(0)) + p1.x,
									std::stoi(pointOffset.at(1)) + p1.y));
							}
						}

						//now to scale points to game size and create the slopes
						for (int i = 0; vPoints.size() != 0 && i < vPoints.size() - 1; i++) {
							Vector2 p1 = Vector2(vPoints.at(i).x * globals::SPRITE_SCALE, vPoints.at(i).y * globals::SPRITE_SCALE);
							Vector2 p2 = Vector2(vPoints.at(i + 1).x * globals::SPRITE_SCALE, vPoints.at(i + 1).y * globals::SPRITE_SCALE);
							_vSlopes.push_back(Slope(p1, p2, Slope::SlopeType::Ground));
						}

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			//Other objectgroups go here with an else if(ssCollisions.str()=="thing"){}
			//parse ceiling slopes
			else if (ssCollisions.str() == "ceiling slopes") {	//object group "slopes"
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						XMLElement* pPolyline = pObject->FirstChildElement("polyline");
						std::vector<Vector2> vPoints;	//holds all the points in the object

														//Grab the first point in the slope
						Vector2 p1;
						p1 = Vector2(std::ceil(pObject->FloatAttribute("x")), std::ceil(pObject->FloatAttribute("y")));

						//Now to get the other point(s)
						//Polyline values in the .tmx indicate the offset added to the initial (x,y) attributes to get the next set of points
						if (pPolyline != NULL) {
							std::vector<std::string> pairs;
							const char* pointString = pPolyline->Attribute("points");
							std::stringstream ssPoints;
							ssPoints << pointString;

							Utils::Split(ssPoints.str(), pairs, ' ');
							//Now <pairs> has been populated with the offset pairs of values
							//Loop through the pairs and add them to the initial (x,y) to get the point coordinates
							//Now split them into Vector2s and then store them in our points vector
							for (int i = 0; i < pairs.size(); i++) {
								std::vector<std::string> pointOffset;
								Utils::Split(pairs.at(i), pointOffset, ',');
								//ps[0] will now have x offset. ps[1] with y offset
								vPoints.push_back(Vector2(
									std::stoi(pointOffset.at(0)) + p1.x,
									std::stoi(pointOffset.at(1)) + p1.y));
							}
						}

						//now to scale points to game size and create the slopes
						for (int i = 0; vPoints.size() != 0 && i < vPoints.size() - 1; i++) {
							Vector2 p1 = Vector2(vPoints.at(i).x * globals::SPRITE_SCALE, vPoints.at(i).y * globals::SPRITE_SCALE);
							Vector2 p2 = Vector2(vPoints.at(i + 1).x * globals::SPRITE_SCALE, vPoints.at(i + 1).y * globals::SPRITE_SCALE);
							_vSlopes.push_back(Slope(p1, p2, Slope::SlopeType::Ceiling));
						}

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			//parse spawn points
			else if (ssCollisions.str() == "spawn points") {	//object group "spawn points"
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						const char* name = pObject->Attribute("name");
						std::stringstream ssPlayer;
						ssPlayer << name;
						if (ssPlayer.str() == "player") {
							this->_v2SpawnPoint = Vector2(std::ceil(x)*globals::SPRITE_SCALE,
								std::ceil(y)*globals::SPRITE_SCALE);
						}


						pObject = pObject->NextSiblingElement("object");
					}
				}
			}

			pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
		}
	}
}

//const Vector2 GetPlayerSpawnPoint
//Retrieves the location of player spawn
const Vector2 Level::GetPlayerSpawnPoint() const {
	return this->_v2SpawnPoint;
}