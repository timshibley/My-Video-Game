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
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.


int main() {
    const long long seed = time(nullptr);
    rprand_set_seed(seed);
    setupGrid();
    setupWindow();
    setupTrackers();
    entityManager = new EntityList();
    if(LoadAllTextures() == -1) {
        return -1;
    }
    walkLeftRightWallCount = 0;
    walkUpDownWallCount = 0;
    mainMenu = Menu(menuTextures[0], {200, 200});
    //This generates 5 enemies in random spots.
    for (int i = 0; i <5; i++){
        int index = rprand_get_value(0, enemyTextures.size() - 1);
        int xGrid = rprand_get_value(0, gridMap[0].size() - 1);
        int yGrid = rprand_get_value(0, gridMap.size() - 1);
        auto* temp = new Enemy(static_cast<float>(xGrid * 100), static_cast<float> (yGrid * 100), 50, 50, MONSTER_ID, VISIBLE, GREEN, enemyTextures[index], index, xGrid, yGrid, 10);
        entityManager->insertNewEntity(temp);
        gridMap[yGrid][xGrid]->entity = entityManager->findAtUltimateXY(xGrid, yGrid);
    }
    //Used to ensure that entities change frames starting at the correct time.
    previousFrameTime = GetTime();
    entityManager->insertNewEntity(600,0, 100, 100, DOOR_ID, VISIBLE, GREEN, doorTextures[0], 0, 6, 0);
    gridMap[6][0]-> entity = entityManager->findAtUltimateXY(6, 0);
    setupPlayer();
    //The program crashes if you don't wait a little because of IsMouseButtonPressed in checkKeys()
    while (GetTime() - previousFrameTime < .0001) {}

    while (!WindowShouldClose()) {
        BeginDrawing();
        upkeepEntitiesOnVisibleGrid();
        if (turnTracker == PLAYERTURN) {
            checkKeys();
        }
        else if (turnTracker == OPPONENTTURN) {
            checkBotAI();
        }
        checkCollisions();
        changeFrames();
        checkDrawing();
        EndDrawing();
    }
    UnloadAllTextures();
    entityManager->deleteAllNodes();
    CloseWindow();
    return 0;
}



// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.