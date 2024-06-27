#pragma once
#ifndef SMOKEEFFECT_H
#define SMOKEEFFECT_H

#include "Component.h"
#include "Vector3.h"
#include "Vector4.h"
#include "exportRomeRender.h"
#include <string>

namespace Ogre {
class ParticleSystem;
class SceneManager;
class SceneNode;
}

namespace VeryReal {
class SmokeEffect : public Component {
        public:
    // Constructor
    SmokeEffect();

    // Destructor
    virtual ~SmokeEffect();

    // Inicializa el efecto de humo con los parámetros proporcionados
    std::pair<bool, std::string> InitComponent(std::string particleSystemName, std::string templateName, VeryReal::Vector3 position,
                                               VeryReal::Vector3 scale, VeryReal::Vector4 color, float duration, float density);

    // Actualiza el efecto de humo
    virtual void Update(const double& dt);

    // Getters para los miembros privados
    const VeryReal::Vector3& getPosition() const;
    const VeryReal::Vector3& getScale() const;
    const VeryReal::Vector4& getColor() const;
    float getDuration() const;
    float getDensity() const;
    std::string getParticleSystemName() const;
    std::string getTemplateName() const;

        private:
    Ogre::ParticleSystem* particleSystem = nullptr;
    Ogre::SceneNode* node = nullptr;
    Ogre::SceneManager* sceneManager = nullptr;
    VeryReal::Vector3 position;
    VeryReal::Vector3 scale;
    VeryReal::Vector4 color;
    float duration;
    float density;
    std::string particle_name;
    std::string template_name;
};
}

#endif   // SMOKEEFFECT_H