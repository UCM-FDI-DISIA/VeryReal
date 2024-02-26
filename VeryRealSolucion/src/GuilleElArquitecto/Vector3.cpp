#include "Vector3.h"
Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}
Vector3::Vector3(float x, float y,float z) {
	this->x = x;
	this->y = y;
	this->z = z;

}
Vector3::Vector3(const Vector3& vector) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

Vector3::~Vector3() {

}
Vector3 Vector3::operator+(const Vector3& vector) {
	return { x + vector.x,y + vector.y,z+vector.z };
}
Vector3 Vector3::operator+=(const Vector3& vector) {
	return { x + vector.x,y + vector.y,z + vector.z };
}
Vector3 Vector3::operator-(const Vector3& vector) {
	return { x - vector.x,y - vector.y,z-vector.z };
}
Vector3 Vector3::operator-=(const Vector3& vector) {
	return { x - vector.x,y - vector.y,z - vector.z };
}
Vector3 Vector3::operator*(const float k) {
	return{ x * k,y * k,z*k };
}
Vector3 Vector3::operator*=(const float k) {
	return{ x * k,y * k,z * k };
}
Vector3 Vector3::operator/(const float k) {
	return{ x / k,y / k,z/k };
}
Vector3 Vector3::operator/=(const float k) {
	return{ x / k,y / k,z / k };
}
Vector3 Vector3::operator=(const Vector3& vector) {
	return{ x = vector.x,y = vector.y,z=vector.z };
}
bool Vector3::operator==(const Vector3& vector) {
	return(x == vector.x && y == vector.y && z == vector.z);
}
bool Vector3::operator!=(const Vector3& vector) {
	return(x != vector.x && y != vector.y && z != vector.z);
}

Vector3 Vector3::Normalize() {
	float m = Magnitude();
	if (m != 0)
		return *this / Magnitude();
	//CERROR
}
//para hacer Cout en la consola, ayudarnos a depurar
std::ostream& operator<<(std::ostream& o, const Vector3& vector) {
	o << vector.GetX() << " , " << vector.GetY() <<" , "<<vector.GetZ()<<"\n";
	return o;
}