#include "Vector3.h"
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
    this->SetX(x + vector.x);
    this->SetY(y + vector.y);
    this->SetZ(z + vector.z);
    return *this;
}

VeryReal::Vector3 VeryReal::Vector3::operator-(const VeryReal::Vector3& vector) {
	return { x - vector.x,y - vector.y,z-vector.z };
}

VeryReal::Vector3 VeryReal::Vector3::operator-=(const VeryReal::Vector3& vector) {
    this->SetX(x - vector.x);
    this->SetY(y - vector.y);
    this->SetZ(z - vector.z);
    return *this;
}

VeryReal::Vector3 VeryReal::Vector3::operator*(const float k) {
	return{ x * k,y * k,z*k };
}

VeryReal::Vector3 VeryReal::Vector3::operator*=(const float k) {
    this->SetX(x * k);
    this->SetY(y * k);
    this->SetZ(z * k);
    return *this;
}

VeryReal::Vector3 VeryReal::Vector3::operator/(const float k) {
	return{ x / k,y / k,z/k };
}

VeryReal::Vector3 VeryReal::Vector3::operator/=(const float k) {
    this->SetX(x / k);
    this->SetY(y / k);
    this->SetZ(z / k);
    return *this;
}

VeryReal::Vector3 VeryReal::Vector3::operator=(const VeryReal::Vector3& vector) {
    this->SetX(vector.x);
    this->SetY(vector.y);
    this->SetZ(vector.z);
    return *this;
}

bool VeryReal::Vector3::operator==(const VeryReal::Vector3& vector) {
	return(x == vector.x && y == vector.y && z == vector.z);
}

bool VeryReal::Vector3::operator!=(const VeryReal::Vector3& vector) {
	return(x != vector.x || y != vector.y || z != vector.z);
}

VeryReal::Vector3 VeryReal::Vector3::Normalize() {
	float m = Magnitude();
	if (m != 0)
		return *this / Magnitude();
	//CERROR

	return Vector3(0,0,0); //warning no todas las rutas devuelven un valor
}

//para hacer Cout en la consola, ayudarnos a depurar
std::ostream& operator<<(std::ostream& o, const VeryReal::Vector3& vector) {
	o << vector.GetX() << " , " << vector.GetY() <<" , "<<vector.GetZ()<<"\n";
	return o;
}

/// Producto escalar de dos vectores
/// @param vector -> El otro vector a multiplicar
/// @return Devuelve la proyección de un vector sobre el otro
float VeryReal::Vector3::Dot(const VeryReal::Vector3& vector) { 
	return this->x * vector.x + this->y * vector.y + this->z * vector.z; 
}

/// Producto vectorial de dos vectores
/// @param vector -> El otro vector a multiplicar
/// @return Devuelve un vector perpendicular a ambos vectores
VeryReal::Vector3 VeryReal::Vector3::Cross(const VeryReal::Vector3& vector) {
    VeryReal::Vector3 perpendicularVector = 
	VeryReal::Vector3((this->y * vector.z - this->z * vector.y), 
					  (this->z * vector.x - this->x * vector.z), 
					  (this->x * vector.y - this->y * vector.x));
    return perpendicularVector;
}

float VeryReal::Vector3::Distance(VeryReal::Vector3 v1) { 
	return abs(sqrtf(powf(v1.GetX() - this->GetX(), 2) + powf(v1.GetY() - this->GetY(), 2) + powf(v1.GetZ() - this->GetZ(), 2)));
}