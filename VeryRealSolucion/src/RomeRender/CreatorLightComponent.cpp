#include "CreatorLightComponent.h"
#include "Light.h"
using namespace VeryReal;
Component* CreatorLightComponent::CreatorSpecificComponent() {
	Light* l = new Light();
	int type = 0;
	Vector3 diffusecolour (0,0,0);
	float shadowfardist = 0, shadowdist = 0, ineerangle = 0, outerangle = 0, nearclipdist = 0;
	bool shdws = 0;
	if (std::holds_alternative<int>(parameters_map.at("type")->GetVariant())) {
		type = std::get<int>(parameters_map.at("type")->GetVariant());
	}
	if (std::holds_alternative<Vector3>(parameters_map.at("diffusecolour")->GetVariant())) {
		diffusecolour = std::get<Vector3>(parameters_map.at("diffusecolour")->GetVariant());
	}
	if (std::holds_alternative<float>(parameters_map.at("shadowfardist")->GetVariant())) {
		shadowfardist = std::get<float>(parameters_map.at("shadowfardist")->GetVariant());
	}
	if (std::holds_alternative<float>(parameters_map.at("shadowdist")->GetVariant())) {
		shadowdist = std::get<float>(parameters_map.at("shadowdist")->GetVariant());
	}
	if (std::holds_alternative<float>(parameters_map.at("ineerangle")->GetVariant())) {
		ineerangle = std::get<float>(parameters_map.at("ineerangle")->GetVariant());
	}
	if (std::holds_alternative<float>(parameters_map.at("outerangle")->GetVariant())) {
		outerangle = std::get<float>(parameters_map.at("outerangle")->GetVariant());
	}
	if (std::holds_alternative<float>(parameters_map.at("nearclipdist")->GetVariant())) {
		nearclipdist = std::get<float>(parameters_map.at("nearclipdist")->GetVariant());
	}
	if (std::holds_alternative<bool>(parameters_map.at("shdws")->GetVariant())) {
		shdws = std::get<bool>(parameters_map.at("shdws")->GetVariant());
	}
	bool b= l->InitComponent(type, diffusecolour, shadowfardist, shadowdist, ineerangle, outerangle, nearclipdist, shdws);
	if (!b) {
		return nullptr;
	}
	return l;
}