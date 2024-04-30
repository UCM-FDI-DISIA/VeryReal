#include "Vector4.h"
#include "Vector3.h"
VeryReal::Vector4::Vector4() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}
VeryReal::Vector4::Vector4(float a, float b, float c, float d, bool isColor) {
    if (isColor) {
        if (x < 0 || y < 0 || z < 0 || w < 0 || x > 255 || y > 255 || z > 255 || w > 1) {
            //CERROR
        }
        this->x = a;
        this->y = b;
        this->z = c;
        this->w = d;
    }
    else {
        this->x = a;
        this->y = b;
        this->z = c;
        this->w = d;
    }
}
VeryReal::Vector4::Vector4(const VeryReal::Vector4& vector, bool isColor) {
    if (isColor) {
        if (vector.x < 0 || vector.y < 0 || vector.z < 0 || vector.w < 0 || vector.x > 255 || vector.y > 255 || vector.z > 255 || vector.w > 1) {
            //CERROR
        }
        x = vector.GetX();
        y = vector.GetY();
        z = vector.GetZ();
        w = vector.GetW();
    }
    else {
        x = vector.GetX();
        y = vector.GetY();
        z = vector.GetZ();
        w = vector.GetW();
    }
}

VeryReal::Vector4::Vector4(float a, float b, float c) {

    double cy = cos(c * (float)M_PI / 180.0 / 2.0);
    double sy = sin(c * (float)M_PI / 180.0 / 2.0);
    double cp = cos(b * (float)M_PI / 180.0 / 2.0);
    double sp = sin(b * (float)M_PI / 180.0 / 2.0);
    double cr = cos(a * (float)M_PI / 180.0 / 2.0);
    double sr = sin(a * (float)M_PI / 180.0 / 2.0);

    w = cy * cp * cr + sy * sp * sr;
    x = cy * cp * sr - sy * sp * cr;
    y = sy * cp * sr + cy * sp * cr;
    z = sy * cp * cr - cy * sp * sr;
}

VeryReal::Vector4::Vector4(const VeryReal::Vector3& v_) {

    double cy = cos(v_.GetZ() * (float)M_PI / 180.0 / 2.0);
    double sy = sin(v_.GetZ() * (float)M_PI / 180.0 / 2.0);
    double cp = cos(v_.GetY() * (float)M_PI / 180.0 / 2.0);
    double sp = sin(v_.GetY() * (float)M_PI / 180.0 / 2.0);
    double cr = cos(v_.GetX() * (float)M_PI / 180.0 / 2.0);
    double sr = sin(v_.GetX() * (float)M_PI / 180.0 / 2.0);

    w = cy * cp * cr + sy * sp * sr;
    x = cy * cp * sr - sy * sp * cr;
    y = sy * cp * sr + cy * sp * cr;
    z = sy * cp * cr - cy * sp * sr;
}

VeryReal::Vector4::~Vector4() { }
VeryReal::Vector4 VeryReal::Vector4::operator+=(const Vector4& vector) {
    this->SetX(x + vector.x);
    this->SetY(y + vector.y);
    this->SetZ(z + vector.z);
    this->SetW(w + vector.w);
    return *this;
}

VeryReal::Vector4 VeryReal::Vector4::operator=(const VeryReal::Vector4& vector) { return {x = vector.x, y = vector.y, z = vector.z, w = vector.w}; }

bool VeryReal::Vector4::operator==(const VeryReal::Vector4& vector) { return (x == vector.x && y == vector.y && z == vector.z && w == vector.w); }

bool VeryReal::Vector4::operator!=(const VeryReal::Vector4& vector) { return (x != vector.x || y != vector.y || z != vector.z || w != vector.w); }

VeryReal::Vector3 VeryReal::Vector4::toEuler() { 
    double roll = atan2(2.0 * (y * w + x * z), 1.0 - 2.0 * (y * y + x * x));
    double pitch = asin(2.0 * (w * x - y * z));
    double yaw = atan2(2.0 * (z * w + x * y), 1.0 - 2.0 * (z * z + x * x));

    Vector3 angles;
    angles.SetY(roll * 180.0 / (float)M_PI);
    angles.SetZ(pitch * 180.0 / (float)M_PI);
    angles.SetX(yaw * 180.0 / (float)M_PI);

    return angles;
}

//para hacer Cout en la consola, ayudarnos a depurar
std::ostream& VeryReal::operator<<(std::ostream& o, const VeryReal::Vector4& vec) {
    o << vec.GetX() << " , " << vec.GetY() << " , " << vec.GetZ() << " , " << vec.GetW() << "\n";
    return o;
}
