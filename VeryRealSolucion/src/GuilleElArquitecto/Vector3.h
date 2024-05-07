#pragma once
#ifndef VECTOR3VR
#define VECTOR3VR
#include <math.h>
#include <iostream>
#include "export.h"
namespace VeryReal {
	class VERYREAL_GUILLEELARQUITECTO Vector3
	{
	private:
		float x;
		float y;
		float z;
	public:
		
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(const Vector3& vector);

		virtual ~Vector3();

		inline void SetX(float x) { this->x = x; }
		inline void SetY(float y) { this->y = y; }
		inline void SetZ(float z) { this->z = z; }
		inline void SetVector(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
		inline void SetVector(const Vector3& vector) { x = vector.x; y = vector.y; z = vector.z; }

		inline float GetX()const { return x; }
		inline float GetY()const { return y; }
		inline float GetZ()const { return z; }
		inline VeryReal::Vector3 GetVector() { return { x,y,z }; }

		Vector3 operator+(const Vector3& vector);
		Vector3 operator+=(const Vector3& vector);
		Vector3 operator-(const Vector3& vector);
		Vector3 operator-=(const Vector3& vector);
		Vector3 operator*(const float k);
		Vector3 operator*=(const float k);
		Vector3 operator/(const float k);
		Vector3 operator/=(const float k);
		Vector3 operator=(const Vector3& vector);
		bool operator==(const Vector3& vector);
		bool operator!=(const Vector3& vector);

		//devuelve el modulo
		inline float Magnitude() { return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2)); }
		//normaliza el vector
        Vector3 Normalize();

		// Multiplicar vectores
        float Dot(const VeryReal::Vector3& vector);
        VeryReal::Vector3 Cross(const VeryReal::Vector3& vector);

		// Calcula la distancia entre dos vectores
        float Distance(VeryReal::Vector3 v1);
	};
	std::ostream& operator<<(std::ostream& o, const Vector3& vec);
}
#endif