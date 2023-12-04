#include "Entity.h"
#include <fstream>

Entity::Entity() {}

Entity::Entity(const string& entityName) {
    int cnt{ 1 };
    if (ifstream(("image_bin/" + entityName + ".bin").c_str(), ios::binary).good()) {
        motion.push_back(new Texture("image_bin/" + entityName + ".bin"));
        //cerr << "image_bin/" + entityName + ".bin";
    }
    while (true) {
        string path = "image_bin/" + entityName + "_motion(" + to_string(cnt++) + ")" + ".bin";
        if (!ifstream(path.c_str(), ios::binary).good()) {
            break;
        }
        motion.push_back(new Texture(path));
        //cerr << "added " << path << '\n';

    }
}

Entity::Entity(const string & entityName, char ) {
    int cnt{ 1 };
    if (ifstream(("image_bin/" + entityName + ".bin").c_str(), ios::binary).good()) {
        motion.push_back(new Texture("image_bin/" + entityName + ".bin"));
        //cerr << "image_bin/" + entityName + ".bin";
    }
    while (true) {
        string path = "image_bin/" + entityName + "_motion (" + to_string(cnt++) + ")" + ".bin";
        if (!ifstream(path.c_str(), ios::binary).good()) {
            break;
        }
        motion.push_back(new Texture(path));
        //cerr << "added " << path << '\n';
    }
}

Entity::Entity(const string& entityName, int) {
    int cnt{ 1 };
    if (ifstream(("image_bin/" + entityName + ".bin").c_str(), ios::binary).good()) {
        motion.push_back(new Texture("image_bin/" + entityName + ".bin"));
        //cerr << "image_bin/" + entityName + ".bin";
    }
    while (true) {
        string path = "image_bin/" + entityName + to_string(cnt++) + ".bin";
        if (!ifstream(path.c_str(), ios::binary).good()) {
            break;
        }
        motion.push_back(new Texture(path));
        //cerr << "added " << path << '\n';
    }
}


Entity::Entity(const string& entityName, bool) {
    if (ifstream(("image_bin/" + entityName + ".bin").c_str(), ios::binary).good()) {
        motion.push_back(new Texture("image_bin/" + entityName + ".bin"));
    }
}

Entity::Entity(const Entity& other) {
    for (auto& i : other.motion) {
        motion.push_back(new Texture(*i));
    }
}

void Entity::shiftResource() {
    motion.push_back(motion.front());
    motion.pop_front();
}

Texture* Entity::getCurrentTexture() const {
    return motion.front();
}

Texture* Entity::getPreviousTexture() {
    return motion.back();
}

void Entity::flipHorizontal() {
    for (auto& i : motion) {
        i->flipHorizontal();
    }
}

int Entity::getMotionSize() {
    return (int)motion.size();
}

//Entity::~Entity() {
//    while (motion.size() > 0) {
//        Texture* dummy = motion.front();
//        delete dummy;
//        motion.pop_front();
//    }
//}