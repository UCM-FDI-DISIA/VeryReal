#include "CreatorTransformComponent.h"
#include "TransformComponent.h"
using namespace VeryReal;

Component* CreatorTransformComponent::CreatorSpecificComponent() {
	Vector3 position, rotation, scale;
	int a = 0;
	TransformComponent* t;
	if (parameters_map.empty()) {
		t = new TransformComponent();
	}
	else {
		if (std::holds_alternative<int>(parameters_map.at("aux")->GetVariant())) {
			a = std::get<int>(parameters_map.at("aux")->GetVariant());
		}
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
		bool b= t->InitComponent(a, position, rotation, scale);
		if (!b) {}//FALTA GESTION DE ERRORES
	}
	return t;
}