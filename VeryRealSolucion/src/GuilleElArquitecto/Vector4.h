#pragma once
#ifndef VECTOR4VR
#define VECTOR4VR
#include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include "export.h"

namespace VeryReal {
class Vector3;
class VERYREAL_GUILLEELARQUITECTO Vector4 {
        private:
    //Variables Vector 4
    float x;
    float y;
    float z;
    float w;

        public:
    //MIRAR CONVERSION A VECTORES DE LIBRERIAS OGRE, STD, FMOD, BULLET
    Vector4();
    Vector4(float a, float b, float c, float d, bool isColor = true);
    Vector4(const VeryReal::Vector4& vector, bool isColor = true);
    Vector4(float a, float b, float c);
    Vector4(const VeryReal::Vector3& v_);

    virtual ~Vector4();

    inline void SetX(float x) { this->x = x; }
    inline void SetY(float y) { this->y = y; }
    inline void SetZ(float z) { this->z = z; }
    inline void SetW(float w) { this->w = z; }
    inline void SetVector(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    inline void SetVector(const Vector4& vector) {
        x = vector.x;
        y = vector.y;
        z = vector.z;
        w = vector.w;
    }

    inline float GetX() const { return x; }
    inline float GetY() const { return y; }
    inline float GetZ() const { return z; }
    inline float GetW() const { return w; }
    inline VeryReal::Vector4 GetVector() { return {x, y, z, w}; }

    VeryReal::Vector4 operator+=(const Vector4& vector);
    VeryReal::Vector4 operator=(const VeryReal::Vector4& vector);
    bool operator==(const VeryReal::Vector4& vector);
    bool operator!=(const VeryReal::Vector4& vector);

    VeryReal::Vector3 toEuler();
};
std::ostream& operator<<(std::ostream& o, const VeryReal::Vector4& vec);
}
#endif