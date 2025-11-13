//
// Created by shibl on 1/13/2025.
//

#ifndef MAIN_H
#define MAIN_H
#include "Player.h"
#include "EntityList.h"
#include <filesystem>
#include <vector>

#include "Location.h"
#include "Menu.h"
#include "Room.h"

//This file contains all of my global variables.
inline Vector2 startPosition;
inline Vector2 startSize;
inline int windowWidth;
inline int windowHeight;
inline Player player;
inline Color backgroundColor;
inline int level;
inline int standardHeight;
inline int standardWidth;
inline double visualScalingFactor;
inline int turnTracker;
inline EntityList* entityManager;
inline float topLeftCornerXPos;
inline float topLeftCornerYpos;
namespace fs = std::filesystem;
inline std::string enemyFolderPath;
inline std::string doorFolderPath;
inline std::string playerFolderPath;
inline std::string playerAttackFolderPath;
inline std::string tileFolderPath;
inline std::string menuFolderPath;
inline std::vector<Texture2D> enemyTextures;
inline std::vector<Texture2D> doorTextures;
inline std::vector<Texture2D> playerTextures;
inline std::vector<Texture2D> playerAttackTextures;
inline std::vector<Texture2D> tileTextures;
inline int walkLeftRightWallCount;
inline int walkUpDownWallCount;
inline std::vector<Texture2D> menuTextures;
inline double attackStartTime = 0.0;
//inline std::vector<std::vector<Location*>> gridMap;
//inline std::vector<std::vector<Location*>> visibleGridLocations;
inline double startTime;
inline double frameTime;
inline double previousFrameTime;
inline int attackTracker;
inline Menu mainMenu;
inline Room mainRoom;
inline std::vector<std::vector<Tile*>> visibleTiles;
#endif //MAIN_H
