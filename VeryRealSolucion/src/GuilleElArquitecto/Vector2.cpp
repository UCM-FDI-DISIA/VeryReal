#include "Vector2.h"
Vector2::Vector2() {
	x = 0;
	y = 0;
}
Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y= y;

}
Vector2::Vector2(const Vector2& vector) {
	x = vector.x;
	y = vector.y;
}

Vector2::~Vector2() {

}

Vector2 Vector2::operator+(const Vector2& vector) {
	return {x + vector.x,y + vector.y };
}
Vector2 Vector2::operator+=(const Vector2& vector) {
	return { x + vector.x,y + vector.y };
}
Vector2 Vector2::operator-(const Vector2& vector) {
	return { x - vector.x,y - vector.y };
}
Vector2 Vector2::operator-=(const Vector2& vector) {
	return { x + vector.x,y + vector.y };
}
Vector2 Vector2::operator*(const float k) {
	return{ x * k,y * k };
}
Vector2 Vector2::operator*=(const float k) {
	return{ x * k,y * k };
}
Vector2 Vector2::operator/(const float k) {
	return{ x / k,y / k };
}
Vector2 Vector2::operator/=(const float k) {
	return{ x / k,y / k };
}
Vector2 Vector2::operator=(const Vector2& vector) {
	return{ x = vector.x,y = vector.y };
}

bool Vector2::operator==(const Vector2& vector) {
	return(x == vector.x && y == vector.y);
}
bool Vector2::operator!=(const Vector2& vector) {
	return(x != vector.x && y != vector.y );
}
Vector2 Vector2::Normalize() {
	float m = Magnitude();
	if (m != 0)
		return *this / Magnitude();
	//CERROR
}
//para hacer Cout en la consola, ayudarnos a depurar
std::ostream& operator<<(std::ostream& o, const Vector2& vector) {
	o << vector.GetX() << " , " << vector.GetY() << "\n";
	return o;
}