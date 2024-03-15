#include "TransformComponent.h"
using namespace VeryReal;
TransformComponent::TransformComponent() {

}

TransformComponent::~TransformComponent() {

}
bool TransformComponent::InitComponent(int a,Vector3 position, Vector3 rotation, Vector3 scale) {
	this->a = a;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	return true;
}
void TransformComponent::Translate(VeryReal::Vector3 translateposition) {
	position += translateposition;
}
void TransformComponent::Rotate(VeryReal::Vector3 rotaterotation) {
	rotation += rotaterotation;
}
void TransformComponent::Scaler(VeryReal::Vector3 scalerscale) {
	scale += scalerscale;
}

