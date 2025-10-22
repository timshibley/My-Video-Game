//
// Created by shibl on 1/15/2025.
//

#include "EntityNode.h"


EntityNode::EntityNode(Entity* e) {
    entry = e;
    next = nullptr;
    prev = nullptr;
    level = 0;
    newID = nullptr;
    prevID = nullptr;
}

EntityNode::EntityNode(float x, float y, float width, float height, int i, int v, Color c, Texture2D t, int k, int xGrid, int yGrid) {
    entry = new Entity(x, y, width, height, i, v, c, t, k, xGrid, yGrid);
    next = nullptr;
    newID = nullptr;
    level = 0;
    prev = nullptr;
    prevID = nullptr;
}

EntityNode::EntityNode() {
    entry = nullptr;
    level = 0;
    next =nullptr;
    newID = nullptr;
    prevID = nullptr;
    prev = nullptr;
}

