#include "CreatorSmokeEffect.h"
#include "SmokeEffect.h"

using namespace VeryReal;

// Initialize the static counter
int CreatorSmokeEffect::smokeEffectCounter = 0;

Component* CreatorSmokeEffect::CreatorSpecificComponent() { return new SmokeEffect(); }

std::pair<bool, std::string> CreatorSmokeEffect::SpecificInitComponent(Component* c) {
    SmokeEffect* smoke = static_cast<SmokeEffect*>(c);
    std::string particleSystemName = "DefaultSmoke_";
    std::string templateName = "smokegraydark";
    VeryReal::Vector3 position(0, 0, 0);
    VeryReal::Vector3 scale(1, 1, 1);
    VeryReal::Vector4 color(1, 1, 1, 1);
    float duration = 10.0f;
    float density = 50.0f;

    if (parameters_map.find("particleSystemName") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("particleSystemName").GetVariant())) {
            particleSystemName =
                std::get<std::string>(parameters_map.at("particleSystemName").GetVariant());
        }
    }

    if (parameters_map.find("templateName") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("templateName").GetVariant())) {
            templateName = std::get<std::string>(parameters_map.at("templateName").GetVariant());
        }
    }

    if (parameters_map.find("position") != parameters_map.end()) {
        if (std::holds_alternative<VeryReal::Vector3>(parameters_map.at("position").GetVariant())) {
            position = std::get<VeryReal::Vector3>(parameters_map.at("position").GetVariant());
        }
    }

    if (parameters_map.find("scale") != parameters_map.end()) {
        if (std::holds_alternative<VeryReal::Vector3>(parameters_map.at("scale").GetVariant())) {
            scale = std::get<VeryReal::Vector3>(parameters_map.at("scale").GetVariant());
        }
    }

    if (parameters_map.find("color") != parameters_map.end()) {
        if (std::holds_alternative<VeryReal::Vector4>(parameters_map.at("color").GetVariant())) {
            color = std::get<VeryReal::Vector4>(parameters_map.at("color").GetVariant());
        }
    }

    if (parameters_map.find("duration") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("duration").GetVariant())) {
            duration = std::get<float>(parameters_map.at("duration").GetVariant());
        }
    }

    if (parameters_map.find("density") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("density").GetVariant())) {
            density = std::get<float>(parameters_map.at("density").GetVariant());
        }
    }

    return smoke->InitComponent(particleSystemName /*+ std::to_string(smokeEffectCounter++)*/, templateName, position, scale, color, density);
}

std::pair<bool, std::string> CreatorSmokeEffect::SpecificInitComponentByCopy(Component* c, Component* other) {
    SmokeEffect* smoke = static_cast<SmokeEffect*>(c);
    SmokeEffect* otherSmoke = static_cast<SmokeEffect*>(other);

     return {true, ""};


}
