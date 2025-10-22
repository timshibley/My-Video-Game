//
// Created by shibl on 1/15/2025.
//

#include "EntityList.h"
#include "Entity.h"
EntityList::EntityList(EntityNode* h)
{
    head = h;
}
EntityList::EntityList() {
    head = nullptr;

}

void EntityList::insertNewEntity(Entity* e) {
    auto* newNode = new EntityNode(e);
    int depth = 0 ;
    if (head == nullptr) {
        head = newNode;
        newNode->level = depth;
        return;
    }
    EntityNode* temp = findIDTree(e->getId());
    if (temp == nullptr) {
        temp = head;
        while (temp->newID != nullptr) {
            temp = temp->newID;
        }
        temp->newID = newNode;
        newNode->level = depth;
        newNode->prevID = temp;
    }
    else {
        while (temp->next != nullptr) {
            temp = temp->next;
            depth++;
        }
        depth++;
        temp->next = newNode;
        newNode->level = depth;
        newNode->prev = temp;
    }
}

void EntityList::insertNewEntity(float x, float y, float width, float height, int i, int v, Color c, Texture2D t, int k, int xGrid, int yGrid) {
    auto* newNode = new EntityNode(x, y, width, height, i, v, c, t, k, xGrid, yGrid);
    int depth = 0 ;
    if (head == nullptr) {
        head = newNode;
        newNode->level = depth;
        return;
    }
    EntityNode* temp = findIDTree(i);
    if (temp == nullptr) {
        temp = head;
        while (temp->newID != nullptr) {
            temp = temp->newID;
        }
        temp->newID = newNode;
        newNode->level = depth;
        newNode->prevID = temp;
    }
    else {
        while (temp->next != nullptr) {
            temp = temp->next;
            depth++;
        }
        depth++;
        temp->next = newNode;
        newNode->level = depth;
        newNode->prev = temp;
    }

}

EntityNode* EntityList::findIDTree(int id) {
    EntityNode* temp = head;
    while (temp != nullptr && temp->entry->getId() != id) {
        temp = temp->newID;
    }
    return temp;
}

void EntityList::deleteNthID(int chosenID, int n) {
    EntityNode* temp = findIDTree(chosenID);
    if (temp == nullptr) {
        return;
    }
    int tracker = 0;
    if (n ==0) {
        if (temp->prevID != nullptr) {
            //There is an ID before
            if (temp->newID != nullptr) {
                //There is an ID before and after
                if (temp->next !=nullptr) {
                    //This is if there are more entities of the same ID
                    temp->next->prevID = temp->prevID;
                    temp->next->newID = temp->newID;
                    temp->next->prev = nullptr;
                    EntityNode* temp2 = temp->next;
                    while (temp2 != nullptr) {
                        temp2->level = temp2->level - 1;
                        temp2 = temp2->next;
                    }
                }
                else {
                    //This is there are not more entities of the same ID
                    temp->prevID->newID = temp->newID;
                    temp->newID->prevID = temp->prevID;
                }
            }
            else {
                //There is an ID before but not after
                if (temp->next !=nullptr) {
                    //There are more entities of the same id
                    temp->next->prev = nullptr;
                    temp->next->prevID = temp->prevID;
                    temp->prevID->newID = temp->next;
                    EntityNode* temp2 = temp->next;
                    while (temp2 != nullptr) {
                        temp2->level = temp2->level - 1;
                        temp2 = temp2->next;
                    }
                }
                else {
                    //There are not more entities of the same id
                    temp->prevID->newID = nullptr;
                    head = nullptr;
                }
            }
        }
        else {
            if (temp->newID != nullptr) {
                //This is when there is an ID after but not an ID before
                if (temp->next != nullptr) {
                    //This is if there are more entities of the same id
                    temp->newID->prevID = temp->next;
                    temp->next->prev = nullptr;
                    temp->next->newID = temp->newID;
                    head = temp->next;
                    EntityNode* temp2 = temp->next;
                    while (temp2 != nullptr) {
                        temp2->level = temp2->level - 1;
                        temp2 = temp2->next;
                    }
                }
                else {
                    //There are no more entities of the same id
                    temp->newID->prevID = nullptr;
                    head = temp->newID;
                }
            }
            else {
                //This is when it has neither a newID in front nor a newID before it
                if (temp->next != nullptr) {
                    //This is there are more entities of the same ID
                    head = temp->next;
                    EntityNode* temp2 = temp->next;
                    while (temp2 != nullptr) {
                        temp2->level = temp2->level - 1;
                        temp2 = temp2->next;
                    }
                }
                else {
                    //This is if there are not more entities of the same ID. You are deleting the last item in the entity manager.
                    head = nullptr;
                }
            }
        }
        delete temp;
        return;
    }
    while (tracker != n && temp != nullptr) {
        tracker++;
        temp = temp->next;
    }
    if (temp == nullptr) {
        return;
    }
    if (temp->next != nullptr) {
        //There are more entities of the same id
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        EntityNode* temp2 = temp->next;
        while (temp2 != nullptr) {
            temp2->level = temp2->level - 1;
            temp2 = temp2->next;
        }
        delete temp2;
    }
    else {
        //You are deleting the bottom entity
        temp->prev->next = nullptr;
        delete temp;
    }
}


int EntityList::lengthOfID(int i ) {
    EntityNode* temp = findIDTree(i);
    int counter = 0;
    if (temp == nullptr) {
        return 0;
    }
    while (temp != nullptr) {
        counter++;
        temp = temp->next;
    }
    return counter;
}

//MAKE SURE TO START N FROM 0
EntityNode* EntityList::findNthEntry(int chosenID, int n) {
    EntityNode* temp = findIDTree(chosenID);
    if (temp == nullptr) {
        return nullptr;
    }
    while (temp != nullptr && temp->level != n) {
        temp = temp->next;
    }
    return temp; //will return nullptr if there are fewer entries than n
}

Entity* EntityList::findAtUltimateXY(int x, int y) {
    EntityNode* temp = head;
  //  bool done = false;
    while (temp != nullptr) {
        if (temp->entry->getXGridCoordinate() == x && temp->entry->getYGridCoordinate() == y) {
            return (temp->entry);
        }
        if (temp->next == nullptr) {
            temp = findIDTree(temp->entry->getId());
            temp = temp->newID;
        }
        else {
            temp = temp->next;
        }
    }
    if (temp == nullptr) {
        return nullptr;
    }
    return (temp->entry);
}


void EntityList::deleteEntity(Entity *e) { //can make more efficient by going to the ID first then going down the list.
    EntityNode* temp = head;
    while (temp != nullptr) {
        if (temp->entry == e) {
            deleteNthID(e->getId(), temp->level);
            return;
        }
        if (temp->next == nullptr) {
            temp = findIDTree(temp->entry->getId());
            temp = temp->newID;
        }
        else {
            temp = temp->next;
        }
    }
}


EntityNode* EntityList::findLastNode() {
    EntityNode* temp = head;
    if (temp == nullptr) {
        return nullptr;
    }
    while (temp->newID != nullptr) {
        temp = temp->newID;
    }
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    return temp;
}

void EntityList::deleteAllNodes() {
    EntityNode* temp = findLastNode();
    while (temp != nullptr) {
        deleteNthID(temp->entry->getId(), temp->level);
        temp = findLastNode();
    }
}

Entity* EntityList::findAtVisibleXY(int x, int y) {
    EntityNode* temp = head;
    //  bool done = false;
    while (temp != nullptr) {
        if (temp->entry->getXVisibleCoordinate() == x && temp->entry->getYVisibleCoordinate() == y) {
            return (temp->entry);
        }
        if (temp->next == nullptr) {
            temp = findIDTree(temp->entry->getId());
            temp = temp->newID;
        }
        else {
            temp = temp->next;
        }
    }
    if (temp == nullptr) {
        return nullptr;
    }
    return (temp->entry);
}
