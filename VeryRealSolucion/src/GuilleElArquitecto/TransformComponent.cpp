#include "TransformComponent.h"
using namespace VeryReal;
TransformComponent::TransformComponent() {

}

TransformComponent::~TransformComponent() {

}
bool TransformComponent::InitComponent(Vector3 position, Vector3 rotation, Vector3 scale) {
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

Component* CreatorTransformComponent::CreatorSpecificComponent() {
	Vector3 position, rotation, scale;
	TransformComponent* t;
	if (parameters_map.empty()) {
		t = new TransformComponent();
	}
	else {
		if (std::holds_alternative<Vector3>(parameters_map.at("position")->GetVariant())) {
			position = std::get<Vector3>(parameters_map.at("position")->GetVariant());
		}
		if (std::holds_alternative<Vector3>(parameters_map.at("rotation")->GetVariant())) {
			rotation = std::get<Vector3>(parameters_map.at("rotation")->GetVariant());
		}
		if (std::holds_alternative<Vector3>(parameters_map.at("rotation")->GetVariant())) {
			scale = std::get<Vector3>(parameters_map.at("scale")->GetVariant());
		}
		t = new TransformComponent();
		t->InitComponent(position, rotation, scale);//FALTA GESTION DE ERRORES
	}
	return t;
}