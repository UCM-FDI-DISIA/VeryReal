#include "Vector4.h"
VeryReal::Vector4::Vector4() {
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}
VeryReal::Vector4::Vector4(float r, float g, float b,float a) {
	if (r < 0 || g < 0 || b < 0 || a < 0 ||
		r>255 || g>255 || b>255 || a>1) {
		//CERROR
	}
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}
VeryReal::Vector4::Vector4(const VeryReal::Vector4& vector) {
	if (vector.r < 0 || vector.g < 0 || vector.b < 0 || vector.a < 0 ||
		vector.r>255 || vector.g>255 || vector.b>255 || vector.a>1) {
		//CERROR
	}
	r = vector.r;
	g = vector.g;
	b = vector.b;
	a = vector.a;
}

VeryReal::Vector4::~Vector4() {
}
VeryReal::Vector4 VeryReal::Vector4::operator=(const VeryReal::Vector4& vector) {
	return{ r = vector.r,g = vector.g,b = vector.b,a = vector.a };
}
bool VeryReal::Vector4::operator==(const VeryReal::Vector4& vector) {
	return(r == vector.r && g == vector.g&& b == vector.b && a==vector.a) ;
}
bool VeryReal::Vector4::operator!=(const VeryReal::Vector4& vector) {
	return(r != vector.r || g != vector.g || b != vector.b || a != vector.a);
}
//para hacer Cout en la consola, ayudarnos a depurar
std::ostream& operator<<(std::ostream& o, const VeryReal::Vector4& vector) {
	o << vector.GetR() << " , " << vector.GetG() << " , " << vector.GetB() << " , " << vector.GetA() << "\n";
	return o;
}