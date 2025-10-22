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
inline Vector2 startPosition;
inline Vector2 startSize;
inline int windowWidth;
inline int windowHeight;
inline Player player;
inline Color backgroundColor;
inline int level;
inline int turnTracker;
inline EntityList* entityManager;
inline Texture2D apple;
inline float topLeftCornerXPos;
inline float topLeftCornerYpos;
namespace fs = std::filesystem;
inline std::string enemyFolderPath;
inline std::string doorFolderPath;
inline std::string playerFolderPath;
inline std::string playerAttackFolderPath;
inline std::string menuFolderPath;
inline std::vector<Texture2D> enemyTextures;
inline std::vector<Texture2D> doorTextures;
inline std::vector<Texture2D> playerTextures;
inline std::vector<Texture2D> playerAttackTextures;
inline int walkLeftRightWallCount;
inline int walkUpDownWallCount;
inline std::vector<Texture2D> menuTextures;
inline double attackStartTime = 0.0;
inline std::vector<std::vector<Location*>> gridMap;
inline std::vector<std::vector<Location*>> visibleGridLocations;
inline double startTime;
inline double frameTime;
inline double previousFrameTime;
inline int attackTracker;
inline Menu mainMenu;
#endif //MAIN_H
