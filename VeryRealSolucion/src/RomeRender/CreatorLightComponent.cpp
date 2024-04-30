#include "CreatorLightComponent.h"
#include "LightComponent.h"
using namespace VeryReal;
Component* CreatorLightComponent::CreatorSpecificComponent() { return new LightComponent(); }

void CreatorLightComponent::SpecificInitComponent(Component* c) {
    int type = 0;
    Vector3 diffusecolour(0, 0, 0);
    float shadowfardist = 0, shadowdist = 0, ineerangle = 0, outerangle = 0, nearclipdist = 0;
    bool shdws = 0;


#pragma region Type
    if (parameters_map.find("type") != parameters_map.end()) {
        if (std::holds_alternative<int>(parameters_map.at("type")->GetVariant())) {
            type = std::get<int>(parameters_map.at("type")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para type este sera seteado por defecto" << std::endl;
            type = 0;
        }
    }
    else {
        std::cout << "No existe ningun parametro type este sera seteado por defecto" << std::endl;
        type = 0;
    }
#pragma endregion

#pragma region DiffuseColor
    if (parameters_map.find("diffusecolour") != parameters_map.end()) {
        if (std::holds_alternative<Vector3>(parameters_map.at("diffusecolour")->GetVariant())) {
            diffusecolour = std::get<Vector3>(parameters_map.at("diffusecolour")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para diffusecolour este sera seteado por defecto" << std::endl;
            diffusecolour = Vector3(0, 0, 0);
        }
    }
    else {
        std::cout << "No existe ningun parametro diffusecolour este sera seteado por defecto" << std::endl;
        diffusecolour = Vector3(0, 0, 0);
    }
#pragma endregion

#pragma region ShadowFardist
    if (parameters_map.find("shadowfardist") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("shadowfardist")->GetVariant())) {
            shadowfardist = std::get<float>(parameters_map.at("shadowfardist")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para shadowfardist este sera seteado por defecto" << std::endl;
            shadowfardist = 0;
        }
    }
    else {
        std::cout << "No existe ningun parametro shadowfardist este sera seteado por defecto" << std::endl;
        shadowfardist = 0;
    }
#pragma endregion

#pragma region ShadowDist
    if (parameters_map.find("shadowdist") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("shadowdist")->GetVariant())) {
            shadowdist = std::get<float>(parameters_map.at("shadowdist")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para shadowdist este sera seteado por defecto" << std::endl;
            shadowdist = 0;
        }
    }
    else {
        std::cout << "No existe ningun parametro shadowdist este sera seteado por defecto" << std::endl;
        shadowdist = 0;
    }
#pragma endregion

#pragma region InnerAngle
    if (parameters_map.find("ineerangle") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("ineerangle")->GetVariant())) {
            ineerangle = std::get<float>(parameters_map.at("ineerangle")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para ineerangle este sera seteado por defecto" << std::endl;
            ineerangle = 0;
        }
    }
    else {
        std::cout << "No existe ningun parametro ineerangle este sera seteado por defecto" << std::endl;
        ineerangle = 0;
    }
#pragma endregion

#pragma region OuterAngle
    if (parameters_map.find("outerangle") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("outerangle")->GetVariant())) {
            outerangle = std::get<float>(parameters_map.at("outerangle")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para outerangle este sera seteado por defecto" << std::endl;
            outerangle = 0;
        }
    }
    else {
        std::cout << "No existe ningun parametro outerangle este sera seteado por defecto" << std::endl;
        outerangle = 0;
    }
#pragma endregion

#pragma region NearClipDistance
    if (parameters_map.find("nearclipdist") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("nearclipdist")->GetVariant())) {
            nearclipdist = std::get<float>(parameters_map.at("nearclipdist")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para nearclipdist este sera seteado por defecto" << std::endl;
            nearclipdist = 0;
        }
    }
    else {
        std::cout << "No existe ningun parametro nearclipdist este sera seteado por defecto" << std::endl;
        nearclipdist = 0;
    }
#pragma endregion

#pragma region Shadows
    if (parameters_map.find("shdws") != parameters_map.end()) {
        if (std::holds_alternative<bool>(parameters_map.at("shdws")->GetVariant())) {
            shdws = std::get<bool>(parameters_map.at("shdws")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para shdws este sera seteado por defecto" << std::endl;
            shdws = false;
        }
    }
    else {
        std::cout << "No existe ningun parametro shdws este sera seteado por defecto" << std::endl;
        shdws = false;
    }
#pragma endregion

    //if (std::holds_alternative<int>(parameters_map.at("type")->GetVariant())) {
    //    type = std::get<int>(parameters_map.at("type")->GetVariant());
    //}
    //if (std::holds_alternative<Vector3>(parameters_map.at("diffusecolour")->GetVariant())) {
    //    diffusecolour = std::get<Vector3>(parameters_map.at("diffusecolour")->GetVariant());
    //}
    //if (std::holds_alternative<float>(parameters_map.at("shadowfardist")->GetVariant())) {
    //    shadowfardist = std::get<float>(parameters_map.at("shadowfardist")->GetVariant());
    //}
    //if (std::holds_alternative<float>(parameters_map.at("shadowdist")->GetVariant())) {
    //    shadowdist = std::get<float>(parameters_map.at("shadowdist")->GetVariant());
    //}
    //if (std::holds_alternative<float>(parameters_map.at("ineerangle")->GetVariant())) {
    //    ineerangle = std::get<float>(parameters_map.at("ineerangle")->GetVariant());
    //}
    //if (std::holds_alternative<float>(parameters_map.at("outerangle")->GetVariant())) {
    //    outerangle = std::get<float>(parameters_map.at("outerangle")->GetVariant());
    //}
    //if (std::holds_alternative<float>(parameters_map.at("nearclipdist")->GetVariant())) {
    //    nearclipdist = std::get<float>(parameters_map.at("nearclipdist")->GetVariant());
    //}
    //if (std::holds_alternative<bool>(parameters_map.at("shdws")->GetVariant())) {
    //    shdws = std::get<bool>(parameters_map.at("shdws")->GetVariant());
    //}
    bool b =
        static_cast<LightComponent*>(c)->InitComponent(type, diffusecolour, shadowfardist, shadowdist, ineerangle, outerangle, nearclipdist, shdws);
}