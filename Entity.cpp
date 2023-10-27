#include "Entity.h"
#include <fstream>

Entity::Entity() {}

Entity::Entity(const string& entityName) {
    this->entityName = entityName;
    getResource();
}

void Entity::getResource() {
    int cnt{1};
    while (true) {
        string path = "image_bin/"+entityName+to_string(cnt++)+".bin";
        if (!ifstream(path.c_str(), ios::binary).good()) {
            break;
        }
        motion.push_back(new Texture(path));
    }
}

void Entity::shiftResource() {
    // cout << "Adding Sprite" << endl;
    // Sprite *curr = mainFrame.addSprite(*motion.front(), Vector2f(0,0));
    // cout << "Setting end pos" << endl;
    // curr->setEndPos(Vector2f(1560, 960), 0);
    motion.push_back(motion.front());
    motion.pop_front();
}

Texture* Entity::getCurrentTexture() {
    return motion.front();
}