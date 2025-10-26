#include <iostream>
#include "raylib.h"
#include "functions.h"
#include "main.h"
#include <ctime>
#include <external/rprand.h>
#include "Macros.h"
#include <filesystem>

#include "DrawingFunctions.h"
#include "Enemy.h"
#include "Menu.h"
#include "SetupAndCleanUp.h"


int main() {
    const long long seed = time(nullptr);
    standardWidth = 100;
    standardHeight = 100;
    rprand_set_seed(seed);
    //Call setup functions. Plan to condense all of these into one function.
    setupWindow();
    setupGrid();
    setupTrackers();
    entityManager = new EntityList();
    if(LoadAllTextures() == -1) {
        return -1;
    }
    //I should make a function to initialize all global variables.
    walkLeftRightWallCount = 0;
    walkUpDownWallCount = 0;
    //Eventually need to make a setupMenu function once it becomes more full fledged
    mainMenu = Menu(menuTextures[0], {200, 200});


    //This generates 5 enemies in random spots.
    for (int i = 0; i <5; i++){
        int index = rprand_get_value(0, enemyTextures.size() - 1);
        int xGrid = rprand_get_value(0, gridMap[0].size() - 1);
        int yGrid = rprand_get_value(0, gridMap.size() - 1);
        auto* temp = new Enemy(static_cast<float>(xGrid * static_cast<float>( standardWidth * visualScalingFactor)), static_cast<float> (yGrid * static_cast<float>( standardHeight * visualScalingFactor)), static_cast<float>( standardWidth * visualScalingFactor), static_cast<float>( standardHeight * visualScalingFactor), MONSTER_ID, VISIBLE, GREEN, enemyTextures[index], index, xGrid, yGrid, 10);
        entityManager->insertNewEntity(temp);
        gridMap[yGrid][xGrid]->entity = entityManager->findAtUltimateXY(xGrid, yGrid);
    }

    //Used to ensure that entities change frames starting at the correct time.
    previousFrameTime = GetTime();


    entityManager->insertNewEntity(600,0, static_cast<float>( standardWidth * visualScalingFactor), static_cast<float>( standardHeight * visualScalingFactor), DOOR_ID, VISIBLE, GREEN, doorTextures[0], 0, 6, 0);
    gridMap[6][0]-> entity = entityManager->findAtUltimateXY(6, 0);
    setupPlayer();
    //The program crashes if you don't wait a little because of IsMouseButtonPressed in checkKeys()
    while (GetTime() - previousFrameTime < .0001) {}

    //This loop is the cycle that the actual game takes place in.
    while (!WindowShouldClose()) {
        BeginDrawing();

        //Updates the entities that are seen
        upkeepEntitiesOnVisibleGrid();
        if (turnTracker == PLAYERTURN) {
            checkKeys();
        }
        else if (turnTracker == OPPONENTTURN) {
            checkBotAI();
        }
        checkCollisions();
        changeFrames();
        char xVis = player.getXVisibleCoordinate()+'0';
        char yVis = player.getYVisibleCoordinate()+'0';
        DrawText(&xVis,  100,  100,  8,  BLUE);
        DrawText(&yVis,  100,  200,  8,  BLUE);
        checkDrawing();
        EndDrawing();
    }

    //Cleans up memory
    UnloadAllTextures();
    entityManager->deleteAllNodes();
    CloseWindow();
    return 0;
}