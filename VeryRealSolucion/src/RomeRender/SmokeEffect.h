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
class Entity;
}

namespace VeryReal {
class SmokeEffect : public Component {
        public:
    // Constructor
    VERYREAL_ROMERENDER SmokeEffect();

    // Destructor
    VERYREAL_ROMERENDER virtual ~SmokeEffect();

    // Inicializa el efecto de humo con los parámetros proporcionados
    VERYREAL_ROMERENDER std::pair<bool, std::string> InitComponent(std::string particleSystemName, std::string templateName,
                                                                   VeryReal::Vector3 position, VeryReal::Vector3 scale, VeryReal::Vector4 color,
                                                                   float density);

    // Actualiza el efecto de humo
    VERYREAL_ROMERENDER virtual void Update(const double& dt);

    // Getters para los miembros privados
    VERYREAL_ROMERENDER const VeryReal::Vector3& getPosition() const;
    VERYREAL_ROMERENDER const VeryReal::Vector3& getScale() const;
    VERYREAL_ROMERENDER const VeryReal::Vector4& getColor() const;
    VERYREAL_ROMERENDER float getDensity() const;
    VERYREAL_ROMERENDER std::string getParticleSystemName() const;
    VERYREAL_ROMERENDER std::string getTemplateName() const;

        private:
    Ogre::ParticleSystem* particleSystem = nullptr;
    Ogre::SceneNode* node = nullptr;
    Ogre::SceneManager* sceneManager = nullptr;
    VeryReal::Vector3 position;
    VeryReal::Vector3 scale;
    VeryReal::Vector4 color;

    float density;
    std::string particle_name;
    std::string template_name;
};
}

#endif   // SMOKEEFFECT_H
