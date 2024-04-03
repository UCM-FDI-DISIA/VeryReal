#include "CreatorTransformComponent.h"
#include "TransformComponent.h"
using namespace VeryReal;

Component* CreatorTransformComponent::CreatorSpecificComponent() {
    return new TransformComponent();
}

void CreatorTransformComponent::SpecificInitComponent(Component* c) {
	Vector3 position, rotation, scale;
	int a = 0;
	TransformComponent* t = static_cast<TransformComponent*>(c);
	if (!parameters_map.empty()) {
        /*if (std::holds_alternative<int>(parameters_map.at("aux")->GetVariant())) {
		a = std::get<int>(parameters_map.at("aux")->GetVariant());
	}*/
        if (std::holds_alternative<Vector3>(parameters_map.at("position")->GetVariant())) {
            position = std::get<Vector3>(parameters_map.at("position")->GetVariant());
        }
        if (std::holds_alternative<Vector3>(parameters_map.at("rotation")->GetVariant())) {
            rotation = std::get<Vector3>(parameters_map.at("rotation")->GetVariant());
        }
        if (std::holds_alternative<Vector3>(parameters_map.at("scale")->GetVariant())) {
            scale = std::get<Vector3>(parameters_map.at("scale")->GetVariant());
        }
        bool b = t->InitComponent(a, position, rotation, scale);
        if (!b) {
        }   //FALTA GESTION DE ERRORES
	}
}