//
// Created by shibl on 1/28/2025.
//

#ifndef MENU_H
#define MENU_H
#include <vector>

#include "raylib.h"


class Menu {
    Texture2D container;
    bool isVisible;
    Vector2 topLeftCorner;
    //Color color;
    std::vector<Rectangle> buttons;
    public:
    Menu(Texture2D c, Vector2 t);
    Menu(Texture2D c, Vector2 t, std::vector<Rectangle> b);
    Menu();
    Vector2 getTopLeftCorner();
    void setTopLeftCorner(Vector2 p);
    void setContainer(Rectangle c);
    void setButtons(std::vector<Rectangle> b);
    void setVisibility(bool v);
    bool getVisibility();
    void setTexture(Texture2D t);
 //   Rectangle* getContainer();
    std::vector<Rectangle> getButtons();
   // Color getColor();
    void draw();
};



#endif //MENU_H
