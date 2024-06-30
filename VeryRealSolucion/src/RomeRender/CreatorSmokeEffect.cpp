#include "CreatorSmokeEffect.h"
#include "SmokeEffect.h"

using namespace VeryReal;

Component* CreatorSmokeEffect::CreatorSpecificComponent() { return new SmokeEffect(); }

std::pair<bool, std::string> CreatorSmokeEffect::SpecificInitComponent(Component* c) {
    SmokeEffect* smoke = static_cast<SmokeEffect*>(c);
    std::string particleSystemName;
    std::string templateName;
    VeryReal::Vector3 position;
    VeryReal::Vector3 scale;
    VeryReal::Vector4 color;
    float duration = 0;
    float density = 0;

    // Aquí extraemos los parámetros del mapa parameters_map
    if (parameters_map.find("particleSystemName") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("particleSystemName").GetVariant())) {
            particleSystemName = std::get<std::string>(parameters_map.at("particleSystemName").GetVariant());
        }
        else {
            particleSystemName = "DefaultSmoke";
        }
    }
    else {
        particleSystemName = "DefaultSmoke";
    }

    if (parameters_map.find("templateName") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("templateName").GetVariant())) {
            templateName = std::get<std::string>(parameters_map.at("templateName").GetVariant());
        }
        else {
            templateName = "smokegraydark";
        }
    }
    else {
        templateName = "smokegraydark";
    }

    // Repetir para otros parámetros: position, scale, color, duration, density
    if (parameters_map.find("position") != parameters_map.end()) {
        if (std::holds_alternative<VeryReal::Vector3>(parameters_map.at("position").GetVariant())) {
            position = std::get<VeryReal::Vector3>(parameters_map.at("position").GetVariant());
        }
        else {
            position = VeryReal::Vector3(0, 0, 0);
        }
    }
    else {
        position = VeryReal::Vector3(0, 0, 0);
    }

    if (parameters_map.find("scale") != parameters_map.end()) {
        if (std::holds_alternative<VeryReal::Vector3>(parameters_map.at("scale").GetVariant())) {
            scale = std::get<VeryReal::Vector3>(parameters_map.at("scale").GetVariant());
        }
        else {
            scale = VeryReal::Vector3(1, 1, 1);
        }
    }
    else {
        scale = VeryReal::Vector3(1, 1, 1);
    }

    if (parameters_map.find("color") != parameters_map.end()) {
        if (std::holds_alternative<VeryReal::Vector4>(parameters_map.at("color").GetVariant())) {
            color = std::get<VeryReal::Vector4>(parameters_map.at("color").GetVariant());
        }
        else {
            color = VeryReal::Vector4(1, 1, 1, 1);
        }
    }
    else {
        color = VeryReal::Vector4(1, 1, 1, 1);
    }

    if (parameters_map.find("duration") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("duration").GetVariant())) {
            duration = std::get<float>(parameters_map.at("duration").GetVariant());
        }
        else {
            duration = 10.0f;
        }
    }
    else {
        duration = 10.0f;
    }

    if (parameters_map.find("density") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("density").GetVariant())) {
            density = std::get<float>(parameters_map.at("density").GetVariant());
        }
        else {
            density = 50.0f;
        }
    }
    else {
        density = 50.0f;
    }

    return smoke->InitComponent(particleSystemName, templateName, position, scale, color, duration, density);
}

std::pair<bool, std::string> CreatorSmokeEffect::SpecificInitComponentByCopy(Component* c, Component* other) {
    SmokeEffect* smoke = static_cast<SmokeEffect*>(c);
    SmokeEffect* otherSmoke = static_cast<SmokeEffect*>(other);

    return smoke->InitComponent(otherSmoke->getParticleSystemName(), otherSmoke->getTemplateName(), otherSmoke->getPosition(), otherSmoke->getScale(),
                                otherSmoke->getColor(), otherSmoke->getDuration(), otherSmoke->getDensity());
}
