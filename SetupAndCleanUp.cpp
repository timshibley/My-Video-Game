//
// Created by shibl on 1/28/2025.
//

#include "SetupAndCleanUp.h"

#include "Macros.h"
#include "main.h"

int LoadAllTextures() {
    enemyFolderPath = "ImagesforGame/Enemies";
    doorFolderPath = "ImagesforGame/Doors";
    playerFolderPath = "ImagesforGame/Player";
    playerAttackFolderPath = "ImagesforGame/Player Attacks";
    menuFolderPath = "ImagesforGame/Menus";
    tileFolderPath = "ImagesforGame/Tiles";
    standardWidth = static_cast<int>(100 * visualScalingFactor);
    standardHeight = static_cast<int>(100 * visualScalingFactor);
    double entityScaler = 0.9;
    for (const auto& entry : fs::directory_iterator(enemyFolderPath)) {
        if (entry.path().extension() == ".png") {
            Image img = LoadImage(entry.path().string().c_str());
            ImageResize(&img, (int)(standardWidth*visualScalingFactor*entityScaler), (int)(standardHeight*visualScalingFactor*entityScaler));
            enemyTextures.push_back(LoadTextureFromImage(img));
            UnloadImage(img);
            if (enemyTextures.back().id == 0) {
                return -1;
            }
        }
    }
    for (const auto& entry : fs::directory_iterator(doorFolderPath)) {
        if (entry.path().extension() == ".jpg" || entry.path().extension() == ".jpeg") {
            Image img = LoadImage(entry.path().string().c_str());
            ImageResize(&img, (int)(standardWidth*visualScalingFactor*entityScaler), (int)(standardHeight*visualScalingFactor*entityScaler));
            doorTextures.push_back(LoadTextureFromImage(img));
            UnloadImage(img);
            if (doorTextures.back().id == 0) {
                return -1;
            }
        }
    }
    for (const auto& entry : fs::directory_iterator(playerFolderPath)) {
        if (entry.path().extension() == ".png") {
            Image img = LoadImage(entry.path().string().c_str());
            ImageResize(&img, (int)(standardWidth*visualScalingFactor*entityScaler), (int)(standardHeight*visualScalingFactor*entityScaler));
            playerTextures.push_back(LoadTextureFromImage(img));
            UnloadImage(img);
            if (playerTextures.back().id == 0) {
                return -1;
            }
        }
    }
    for (const auto& entry : fs::directory_iterator(playerAttackFolderPath)) {
        if (entry.path().extension() == ".png") {
            Image img = LoadImage(entry.path().string().c_str());
            ImageResize(&img, (int)(standardWidth*visualScalingFactor*entityScaler), (int)(standardHeight*visualScalingFactor*entityScaler));
            playerAttackTextures.push_back(LoadTextureFromImage(img));
            UnloadImage(img);
            if (playerAttackTextures.back().id == 0) {
                return -1;
            }
        }
    }
    for (const auto& entry : fs::directory_iterator(menuFolderPath)) {
        if (entry.path().extension() == ".png") {
            Image img = LoadImage(entry.path().string().c_str());
            //ImageResize(&img, 100, 100);
            menuTextures.push_back(LoadTextureFromImage(img));
            UnloadImage(img);
            if (menuTextures.back().id == 0) {
                return -1;
            }
        }
    }
    for (const auto& entry : fs::directory_iterator(tileFolderPath)) {
        if (entry.path().extension() == ".png") {
            Image img = LoadImage(entry.path().string().c_str());
            ImageResize(&img, (int)(standardWidth*visualScalingFactor*entityScaler), (int)(standardHeight*visualScalingFactor*entityScaler));
            tileTextures.push_back(LoadTextureFromImage(img));
            UnloadImage(img);
            if (tileTextures.back().id == 0) {
                return -1;
            }
        }
    }
    return 0;
}



void UnloadAllTextures() {
    for (const auto & doorTexture : doorTextures) {
        UnloadTexture(doorTexture);
    }
    for (const auto & enemyTexture : enemyTextures) {
        UnloadTexture(enemyTexture);
    }
    for (const auto & playerTexture : playerTextures) {
        UnloadTexture(playerTexture);
    }
    for (const auto & playerAttackTexture : playerAttackTextures) {
        UnloadTexture(playerAttackTexture);
    }
    for (const auto & menuTexture : menuTextures) {
        UnloadTexture(menuTexture);
    }
}


void setupWindow() {

    backgroundColor = WHITE;
    InitWindow(windowWidth, windowHeight, "Move Box");
    int totalMonitors = GetMonitorCount();
    int display = totalMonitors-1;
    SetWindowMonitor(display);
    ToggleBorderlessWindowed();
    windowWidth = GetMonitorWidth(display);
    windowHeight = GetMonitorHeight(display);
    SetWindowSize(windowWidth, windowHeight);
    visualScalingFactor = windowHeight/10.0/100.0;
    SetTargetFPS(60);
}

void setupTrackers() {
    turnTracker = PLAYERTURN;
    attackTracker = EXECUTE_NOTHING;
}

void setupGrid() {
    mainRoom = Room{30, 30, 0, 0};
    gridMap.resize(30);
    for (auto &i : gridMap) {
        i.resize(30);
    }
    visibleGridLocations.resize(9); //This decides how large the visibility is.
    for (auto &i : visibleGridLocations) {
        i.resize(9);
    }

    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            Location* temp;
            if (i == 0 ||j == 0 || i == 29 || j == 29) {
                 temp = new Location(nullptr, {static_cast<float>(standardWidth*visualScalingFactor*i),static_cast<float>( standardHeight*visualScalingFactor * j), static_cast<float>( standardWidth * visualScalingFactor), static_cast<float>( standardHeight * visualScalingFactor)}, RED);

            }
            else {
                 temp = new Location(nullptr, {static_cast<float>(standardWidth * visualScalingFactor * i),static_cast<float>( standardHeight *visualScalingFactor * j), static_cast<float>( standardWidth * visualScalingFactor), static_cast<float>( standardHeight * visualScalingFactor)}, BLUE);

            }
            gridMap[j][i] = temp;
        }
    }
    for (int i = 0; i< visibleGridLocations.size(); i++) {
        for (int j = 0; j< visibleGridLocations[i].size(); j++) {
            visibleGridLocations[i][j] = gridMap[i][j];
        }
    }
    float centerXPos = windowWidth / 2;
    float centerYPos = windowHeight / 2;

    topLeftCornerYpos = centerYPos - visibleGridLocations[(visibleGridLocations.size()-1) / 2][(visibleGridLocations[0].size()-1)/2]->rectangle.height *((visibleGridLocations.size()-1)/2.0+.5);
    topLeftCornerXPos = centerXPos - visibleGridLocations[(visibleGridLocations.size()-1) / 2][(visibleGridLocations[0].size()-1)/2]->rectangle.width *((visibleGridLocations[0].size()-1)/2.0+.5);
}

void setupPlayer() {
    player = {0, 0, static_cast<float>(standardWidth * visualScalingFactor), static_cast<float>( standardHeight * visualScalingFactor), PLAYER_ID, BLACK, playerTextures[MC_RIGHT_TEXTURE], 0, 14,};
    (gridMap[(visibleGridLocations.size()-1)/2][(visibleGridLocations[0].size()-1)/2]->entity) = &player;
    player.setXGridCoordinate((visibleGridLocations[0].size()-1)/2);
    player.setYGridCoordinate((visibleGridLocations.size()-1)/2);
    entityManager->insertNewEntity(&player);
}