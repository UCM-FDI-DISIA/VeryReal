#pragma once
#ifndef VECTOR4
#define VECTOR4
#include <math.h>
#include <iostream>
#include "export.h"

namespace VeryReal {
class VERYREAL_API Vector4
	{
	private:
		float r;
		float g;
		float b;
		float a;
	public:
		//MIRAR CONVERSION A VECTORES DE LIBRERIAS OGRE, STD, FMOD, BULLET
		Vector4();
		Vector4(float r, float g, float b, float a);
		Vector4(const VeryReal::Vector4& vector);

		virtual ~Vector4();

		inline void SetR(float r) { this->r = r; }
		inline void SetG(float g) { this->g = g; }
		inline void SetB(float b) { this->b = b; }
		inline void SetA(float a) { this->a = a; }
		inline void SetVector(float r, float g, float b, float a) { this->r = r; this->g = g; this->b = b; this->a = a; }
		inline void SetVector(const Vector4& vector) { r = vector.r; g = vector.g; b = vector.b; a = vector.a; }

		inline float GetR()const { return r; }
		inline float GetG()const { return g; }
		inline float GetB()const { return b; }
		inline float GetA()const { return a; }
		inline VeryReal::Vector4 GetVector() { return { r,g,b,a }; }

		VeryReal::Vector4 operator=(const VeryReal::Vector4& vector);
		bool operator==(const VeryReal::Vector4& vector);
		bool operator!=(const VeryReal::Vector4& vector);
	};
	std::ostream& operator<<(std::ostream& o, const VeryReal::Vector4& vec);
}
#endif