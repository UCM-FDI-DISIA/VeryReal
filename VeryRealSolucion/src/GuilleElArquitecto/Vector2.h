#pragma once
#include <math.h>
#include <iostream>
class Vector2
{
private: 
	float x;
	float y;
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& vector);
	
	virtual ~Vector2();

	inline void SetX(float x) { this->x = x; }
	inline void SetY(float y) { this->y = y; }
	inline void SetVector(float x, float y) { this->x = x; this->y = y; }
	inline void SetVector(const Vector2& vector) { x = vector.x; y = vector.y; }

	inline float GetX()const { return x; }
	inline float GetY()const { return y; }
	inline Vector2 GetVector() { return { x,y }; }

	Vector2 operator+(const Vector2& vector);
	Vector2 operator-(const Vector2& vector);
	Vector2 operator*(const float k);
	Vector2 operator/(const float k);
	Vector2 operator=(const Vector2& vector);
	bool operator==(const Vector2& vector);
	bool operator!=(const Vector2& vector);
	
	//devuelve el modulo
	inline float Magnitude() { return sqrtf(powf(x, 2) + powf(y, 2)); }
	//normaliza el vector
	inline Vector2 Normalize();
};
std::ostream& operator<<(std::ostream& o, const Vector2& vec);

