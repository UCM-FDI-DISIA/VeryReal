#include "CreatorTransformComponent.h"
#include "TransformComponent.h"
VeryReal::CreatorTransformComponent::CreatorTransformComponent() {

}
VeryReal::CreatorTransformComponent::~CreatorTransformComponent() {

}
VeryReal::Component* VeryReal::CreatorTransformComponent::CreatorSpecificComponent() {
	//FALTA GESTION DE ERRORES
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
		t = new TransformComponent(position, rotation, scale);
	}
	return t;
}