#include "Vector2.h"

VeryReal::Vector2::Vector2() {
	x = 0;
	y = 0;
}
VeryReal::Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y= y;

}
VeryReal::Vector2::Vector2(const VeryReal::Vector2& vector) {
	x = vector.x;
	y = vector.y;
}

VeryReal::Vector2::~Vector2() {

}

VeryReal::Vector2 VeryReal::Vector2::operator+(const VeryReal::Vector2& vector) {
	return {x + vector.x,y + vector.y };
}
VeryReal::Vector2 VeryReal::Vector2::operator+=(const VeryReal::Vector2& vector) {
	return { x + vector.x,y + vector.y };
}
VeryReal::Vector2 VeryReal::Vector2::operator-(const VeryReal::Vector2& vector) {
	return { x - vector.x,y - vector.y };
}
VeryReal::Vector2 VeryReal::Vector2::operator-=(const VeryReal::Vector2& vector) {
	return { x + vector.x,y + vector.y };
}
VeryReal::Vector2 VeryReal::Vector2::operator*(const float k) {
	return{ x * k,y * k };
}
VeryReal::Vector2 VeryReal::Vector2::operator*=(const float k) {
	return{ x * k,y * k };
}
VeryReal::Vector2 VeryReal::Vector2::operator/(const float k) {
	return{ x / k,y / k };
}
VeryReal::Vector2 VeryReal::Vector2::operator/=(const float k) {
	return{ x / k,y / k };
}
VeryReal::Vector2 VeryReal::Vector2::operator=(const VeryReal::Vector2& vector) {
	return{ x = vector.x,y = vector.y };
}

bool VeryReal::Vector2::operator==(const VeryReal::Vector2& vector) {
	return(x == vector.x && y == vector.y);
}
bool VeryReal::Vector2::operator!=(const VeryReal::Vector2& vector) {
	return(x != vector.x && y != vector.y );
}
VeryReal::Vector2 VeryReal::Vector2::Normalize() {
	float m = Magnitude();
	if (m != 0)
		return *this / Magnitude();
	//CERROR
}
//para hacer Cout en la consola, ayudarnos a depurar
std::ostream& operator<<(std::ostream& o, const VeryReal::Vector2& vector) {
	o << vector.GetX() << " , " << vector.GetY() << "\n";
	return o;
}