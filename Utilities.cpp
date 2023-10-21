#include "Utilities.h"
#include <math.h>

using namespace std;
using namespace utility;

//extern void setSpeedMultiplier(float speedMultiplier) {
//    SPEED_MULTIPLIER = speedMultiplier;
//}

Vector2i::Vector2i() {
    x = 0;
    y = 0;
}

Vector2i::Vector2i(int x, int y) {
    this->x = x;
    this->y = y;
}

Vector2i::Vector2i(const Vector2i& other) {
    x = other.x;
    y = other.y;
}

Vector2i::~Vector2i() {
    // Do nothing
}

Vector2i Vector2i::operator+(const Vector2i& other) {
    return Vector2i(x + other.x, y + other.y);
}

Vector2i Vector2i::operator-(const Vector2i& other) {
    return Vector2i(x - other.x, y - other.y);
}

Vector2i Vector2i::operator*(const int& other) {
    return Vector2i(x * other, y * other);
}

Vector2i Vector2i::operator/(const int& other) {
    return Vector2i(x / other, y / other);
}

Vector2i Vector2i::operator+=(const Vector2i& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2i Vector2i::operator-=(const Vector2i& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2i Vector2i::operator*=(const int& other) {
    x *= other;
    y *= other;
    return *this;
}

Vector2i Vector2i::operator/=(const int& other) {
    x /= other;
    y /= other;
    return *this;
}

bool Vector2i::operator==(const Vector2i& other) {
    return x == other.x && y == other.y;
}

bool Vector2i::operator!=(const Vector2i& other) {
    return x != other.x || y != other.y;
}

float Vector2i::modulus() {
    return sqrt(x * x + y * y);
}

Vector2f::Vector2f() {
    x = 0;
    y = 0;
}

Vector2f::Vector2f(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2f::Vector2f(const Vector2f& other) {
    x = other.x;
    y = other.y;
}

Vector2f::~Vector2f() {
    // Do nothing
}

Vector2f Vector2f::operator+(const Vector2f& other) {
    return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2f::operator-(const Vector2f& other) {
    return Vector2f(x - other.x, y - other.y);
}

Vector2f Vector2f::operator*(const float& other) {
    return Vector2f(x * other, y * other);
}

Vector2f Vector2f::operator/(const float& other) {
    return Vector2f(x / other, y / other);
}

Vector2f Vector2f::operator+=(const Vector2f& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2f Vector2f::operator-=(const Vector2f& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2f Vector2f::operator*=(const float& other) {
    x *= other;
    y *= other;
    return *this;
}

Vector2f Vector2f::operator/=(const float& other) {
    x /= other;
    y /= other;
    return *this;
}

bool Vector2f::operator==(const Vector2f& other) {
    return x == other.x && y == other.y;
}

bool Vector2f::operator!=(const Vector2f& other) {
    return x != other.x || y != other.y;
}

float Vector2f::modulus() {
    return sqrt(x * x + y * y);
}

Rect2D::Rect2D() {
    this->top = 0;
    this->left = 0;
    this->width = 0;
    this->height = 0;
}

Rect2D::Rect2D(int top, int left, int width, int height) {
    this->top = top;
    this->left = left;
    this->width = width;
    this->height = height;
}

Rect2D::Rect2D(Vector2i topLeft, Vector2i bottomRight) {
    this->top = topLeft.y;
    this->left = topLeft.x;
    this->width = bottomRight.x - topLeft.x;
    this->height = bottomRight.y - topLeft.y;
}

Rect2D::Rect2D(Vector2i topLeft, int width, int height) {
    this->top = topLeft.y;
    this->left = topLeft.x;
    this->width = width;
    this->height = height;
}

Rect2D::Rect2D(const Rect2D& other) {
    this->top = other.top;
    this->left = other.left;
    this->width = other.width;
    this->height = other.height;
}

Rect2D::~Rect2D() {
    // Do nothing
}







