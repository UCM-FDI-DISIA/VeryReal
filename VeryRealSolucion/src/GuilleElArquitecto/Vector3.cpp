#include "Vector3.h"
#include <fmod.hpp>

VeryReal::Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}
VeryReal::Vector3::Vector3(float x, float y,float z) {
	this->x = x;
	this->y = y;
	this->z = z;

}
VeryReal::Vector3::Vector3(const VeryReal::Vector3& vector) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

VeryReal::Vector3::~Vector3() {

}
VeryReal::Vector3 VeryReal::Vector3::operator+(const VeryReal::Vector3& vector) {
	return { x + vector.x,y + vector.y,z+vector.z };
}
VeryReal::Vector3 VeryReal::Vector3::operator+=(const VeryReal::Vector3& vector) {
	return { x + vector.x,y + vector.y,z + vector.z };
}
VeryReal::Vector3 VeryReal::Vector3::operator-(const VeryReal::Vector3& vector) {
	return { x - vector.x,y - vector.y,z-vector.z };
}
VeryReal::Vector3 VeryReal::Vector3::operator-=(const VeryReal::Vector3& vector) {
	return { x - vector.x,y - vector.y,z - vector.z };
}
VeryReal::Vector3 VeryReal::Vector3::operator*(const float k) {
	return{ x * k,y * k,z*k };
}
VeryReal::Vector3 VeryReal::Vector3::operator*=(const float k) {
	return{ x * k,y * k,z * k };
}
VeryReal::Vector3 VeryReal::Vector3::operator/(const float k) {
	return{ x / k,y / k,z/k };
}
VeryReal::Vector3 VeryReal::Vector3::operator/=(const float k) {
	return{ x / k,y / k,z / k };
}
VeryReal::Vector3 VeryReal::Vector3::operator=(const VeryReal::Vector3& vector) {
	return{ x = vector.x,y = vector.y,z=vector.z };
}
bool VeryReal::Vector3::operator==(const VeryReal::Vector3& vector) {
	return(x == vector.x && y == vector.y && z == vector.z);
}
bool VeryReal::Vector3::operator!=(const VeryReal::Vector3& vector) {
	return(x != vector.x && y != vector.y && z != vector.z);
}

VeryReal::Vector3 VeryReal::Vector3::Normalize() {
	float m = Magnitude();
	if (m != 0)
		return *this / Magnitude();
	//CERROR
}

FMOD_VECTOR VeryReal::Vector3::v3ToFmodV3() const
{
	FMOD_VECTOR newVector;
	newVector.x = x; newVector.y = y; newVector.z = z;
	return newVector;
}

//para hacer Cout en la consola, ayudarnos a depurar
std::ostream& operator<<(std::ostream& o, const VeryReal::Vector3& vector) {
	o << vector.GetX() << " , " << vector.GetY() <<" , "<<vector.GetZ()<<"\n";
	return o;
}