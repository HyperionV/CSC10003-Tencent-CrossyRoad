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
    Sprite* current = first;
    while (current != nullptr) {
        Sprite* next = current->next;
        delete current;
        current = next;
    }
}

Sprite* Frame::addSprite(Texture texture, Vector2f position) {
    Sprite* sprite = new Sprite(position, &texture);
    if (first == nullptr) {
        first = sprite;
        last = sprite;
    }
    else {
        last->next = sprite;
        sprite->prev = last;
        last = sprite;
    }
    return sprite;
}

void Frame::removeSprite(Sprite*& sprite) {
    if (sprite == first) {
        first = sprite->next;
        first->prev = nullptr;
    }
    else if (sprite == last) {
        last = sprite->prev;
        last->next = nullptr;
    }
    else {
        sprite->prev->next = sprite->next;
        sprite->next->prev = sprite->prev;
    }
    delete sprite;
    sprite = nullptr;
}

void Frame::update() {
    Sprite* current = first;
    while (current != nullptr) {
        current->updateSprite();
        // if (current->getPosition().x > current->getDestination().x || (current->getPosition().x < current->getDestination().x && current->getDestination().x < 0) ) {
        //     removeSprite(current);
        //     continue;
        // }
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
    Sprite* current = first;
    while (current != nullptr) {
        current->draw(bits, size);
        current = current->next;
    }

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

    BitBlt(hdc, position.x, position.y, size.x, size.y, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, hOldBitmap);
    DeleteDC(memDC);

    // Clean up the DIB section
    DeleteObject(hBitmap);
}