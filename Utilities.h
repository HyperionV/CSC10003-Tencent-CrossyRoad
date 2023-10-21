#pragma once

namespace utility {

//    float SPEED_MULTIPLIER = 1.0f;
//    void setSpeedMultiplier(float speedMultiplier);

    struct Vector2i {
        int x;
        int y;

        Vector2i();

        Vector2i(int x, int y);

        Vector2i(const Vector2i &other);

        ~Vector2i();

        Vector2i operator+(const Vector2i &other);

        Vector2i operator-(const Vector2i &other);

        Vector2i operator*(const int &other);

        Vector2i operator/(const int &other);

        Vector2i operator+=(const Vector2i &other);

        Vector2i operator-=(const Vector2i &other);

        Vector2i operator*=(const int &other);

        Vector2i operator/=(const int &other);

        bool operator==(const Vector2i &other);

        bool operator!=(const Vector2i &other);

        float modulus();
    };

    struct Vector2f {
        float x;
        float y;

        Vector2f();

        Vector2f(float x, float y);

        Vector2f(const Vector2f &other);

        ~Vector2f();

        Vector2f operator+(const Vector2f &other);

        Vector2f operator-(const Vector2f &other);

        Vector2f operator*(const float &other);

        Vector2f operator/(const float &other);

        Vector2f operator+=(const Vector2f &other);

        Vector2f operator-=(const Vector2f &other);

        Vector2f operator*=(const float &other);

        Vector2f operator/=(const float &other);

        bool operator==(const Vector2f &other);

        bool operator!=(const Vector2f &other);

        float modulus();
    };

    struct Rect2D{
        int top;
        int left;
        int width;
        int height;

        Rect2D();
        Rect2D(int top, int left, int width, int height);
        Rect2D(Vector2i topLeft, Vector2i bottomRight);
        Rect2D(Vector2i topLeft, int width, int height);
        Rect2D(const Rect2D& other);
        ~Rect2D();
    };

}