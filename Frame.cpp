#include "Frame.h"
#include <Windows.h>
#include <wingdi.h>
#include <iostream>

using namespace std;

Frame::Frame() {
    first = nullptr;
    last = nullptr;
    size = Vector2i();
    position = Vector2i();
}

Frame::Frame(Vector2i size, Vector2i position) {
    first = nullptr;
    last = nullptr;
    this->size = size;
    this->position = position;
}

Frame::~Frame() {
    Drawable* current = first;
    while (current != nullptr) {
        Drawable* next = current->next;
        delete current;
        current = next;
    }
}

Sprite* Frame::addSprite(Texture& texture, Vector2f position, int priority) {
    Drawable* sprite = new Sprite(position, &texture, priority);
    if (first == nullptr) {
        first = sprite;
        last = sprite;
    }
    else {
        last->next = sprite;
        sprite->prev = last;
        last = sprite;
    }
    return (Sprite*)sprite;
}

Sprite* Frame::addSprite(Texture* texture, Vector2f position, int priority) {
    Drawable* sprite = new Sprite(position, texture, priority);
    if (first == nullptr) {
        first = sprite;
        last = sprite;
    }
    else {
        last->next = sprite;
        sprite->prev = last;
        last = sprite;
    }
    return (Sprite*)sprite;
}

void Frame::addSprite(Sprite* _sprite) {
    Drawable* sprite = _sprite;
    if (first == nullptr) {
        first = sprite;
        last = sprite;
    }
    else {
        last->next = sprite;
        sprite->prev = last;
        last = sprite;
    }
    return;
}

void Frame::removeSprite(Sprite*& _sprite) {
    Drawable* sprite = _sprite;
    if (!sprite) {
            std::cerr << "Error: Attempt to remove a null node." << std::endl;
            return;
        }

    if (sprite == first) {
        first = sprite->next;
        if (first) {
            first->prev = nullptr;
        }
    } else if (sprite == last) {
        last = sprite->prev;
        if (last) {
            last->next = nullptr;
        }
    } else {
        if (sprite->prev) {
            sprite->prev->next = sprite->next;
        }
        if (sprite->next) {
            sprite->next->prev = sprite->prev;
        }
    }

    delete sprite;
    sprite = nullptr;
}

void Frame::removeAllSprites() {
    Drawable* current = first;
    while (current != nullptr) {
        Drawable* next = current->next;
        delete current;
        current = next;
    }
    first = nullptr;
    last = nullptr;
}

void Frame::update() {
    Drawable* current = first;
    while (current != nullptr) {
        current->update();
        // if (current->getPosition().x > current->getDestination().x || (current->getPosition().x < current->getDestination().x && current->getDestination().x < 0) ) {
        //     removeSprite(current);
        //     continue;
        // }
        current = current->next;
    }
}

void Frame::onEvent(Event& event) {
    Drawable* current = first;
    while (current != nullptr) {
        current->onEvent(event);
        current = current->next;
    }
}

void Frame::draw(HDC hdc) {
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = size.x;
    bmi.bmiHeader.biHeight = -size.y; // Negative height to specify a top-down DIB
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32; // 32 bits per pixel (for RGBA)

    void *bits;
    // Create a DIB section
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);

    if (hBitmap == nullptr) {
        std::cerr << "Failed to create DIB section." << std::endl;
        return;
    }

    // Draw the sprites to the DIB section
    vector<Drawable*> sprites;
    Drawable* current = first;
    while (current != nullptr) {
        sprites.push_back(current);
        current = current->next;
    }

    stable_sort(sprites.begin(), sprites.end(), [](Drawable* a, Drawable* b) {
        return a->getPriority() < b->getPriority();
    });

    for (Drawable* sprite : sprites) {
        sprite->draw(bits, size);
    }

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

    BitBlt(hdc, position.x, position.y, size.x, size.y, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, hOldBitmap);
    DeleteDC(memDC);


    // Clean up the DIB section
    DeleteObject(hBitmap);
}

void Frame::draw(HDC hdc, Sprite* curSprite) {
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = size.x;
    bmi.bmiHeader.biHeight = -size.y; // Negative height to specify a top-down DIB
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32; // 32 bits per pixel (for RGBA)

    void* bits;

    // Create a DIB section
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);

    if (hBitmap == nullptr) {
        std::cerr << "Failed to create DIB section." << std::endl;
        return;
    }


    // Draw the sprite to the DIB section
    curSprite->draw(bits, size);

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

    BitBlt(hdc, position.x, position.y, size.x, size.y, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, hOldBitmap);
    DeleteDC(memDC);

    // Clean up the DIB section
    DeleteObject(hBitmap);
}
void Frame::removeAllSprite()
{
    Drawable* current = first;
    while (current) {
        Drawable* temp = current;
        current = current->next;
        delete temp;
    }
    first = last = nullptr;
    return;
}