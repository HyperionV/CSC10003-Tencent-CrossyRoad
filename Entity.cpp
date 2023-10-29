#include "Entity.h"
#include <fstream>

Entity::Entity() {}

Entity::Entity(const string& entityName) {
    this->entityName = entityName;
    getResource();
}

void Entity::getResource() {
    int cnt{1};
    if (ifstream(("image_bin/"+entityName+".bin").c_str(), ios::binary).good()) 
        motion.push_back(new Texture("image_bin/"+entityName+".bin"));
    while (true) {
        string path = "image_bin/"+entityName+to_string(cnt++)+".bin";
        if (!ifstream(path.c_str(), ios::binary).good()) {
            break;
        }
        motion.push_back(new Texture(path));
    }
}

void Entity::shiftResource(Sprite* _sprite) {
    motion.push_back(motion.front());
    motion.pop_front();
    _sprite->setTexture(motion.front());
}

Texture* Entity::getCurrentTexture() {
    return motion.front();
}