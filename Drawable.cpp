#include "Drawable.h"

Drawable::Drawable() {
    next = nullptr;
    prev = nullptr;
}

Drawable::Drawable(Drawable* next, Drawable* prev) {
    this->next = next;
    this->prev = prev;
}

Drawable::~Drawable() {
    next = nullptr;
    prev = nullptr;
}

int Drawable::getPriority() {
    return priority;
}

void Drawable::setPriority(int priority) {
    this->priority = priority;
}

void Drawable::onEvent(Event& event) {
    // Do nothing for now
}

