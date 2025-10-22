
#include "Menu.h"

#include <string>

Menu::Menu() {
}


Menu::Menu(Texture2D c, Vector2 t) {
    container = c;
    topLeftCorner = t;
    isVisible = false;
}

Menu::Menu(Texture2D c, Vector2 t, std::vector<Rectangle> b) {
    container = c;
    topLeftCorner = t;
    isVisible = false;
}

void Menu::draw() {
    DrawTexture(container, topLeftCorner.x, topLeftCorner.y, {255, 255, 255, 128});
}

bool Menu::getVisibility() {
    return isVisible;
}

Vector2 Menu::getTopLeftCorner() {
    return topLeftCorner;
}

void Menu::setTopLeftCorner(Vector2 p) {
    topLeftCorner = p;
}

void Menu::setVisibility(bool v) {
    isVisible = v;
}

void Menu::setTexture(Texture2D c) {
    container = c;
}