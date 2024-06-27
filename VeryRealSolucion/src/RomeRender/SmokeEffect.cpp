#pragma once
#pragma warning(disable : 4251)
#include "SmokeEffect.h"
#include "RenderManager.h"
#include "conversorvectores.h"
#include <OgreParticleSystem.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreParticleEmitter.h>
#include <Ogre.h>

using namespace VeryReal;

SmokeEffect::SmokeEffect() { }

SmokeEffect::~SmokeEffect() {
    if (particleSystem && sceneManager) {
        sceneManager->destroyParticleSystem(particleSystem);
        RenderManager::Instance()->DeleteNode(node);
    }
}

std::pair<bool, std::string> SmokeEffect::InitComponent(std::string particleSystemName, std::string templateName, VeryReal::Vector3 position,
                                                        VeryReal::Vector3 scale, VeryReal::Vector4 color, float duration, float density) {
    particle_name = particleSystemName;
    template_name = templateName;
    this->position = position;
    this->scale = scale;
    this->color = color;
    this->duration = duration;
    this->density = density;

    sceneManager = RenderManager::Instance()->SceneManagerOgree();
    if (!sceneManager) {
        return {false, "SceneManager was null, ERROR from InitComponent SmokeEffect"};
    }

    node = RenderManager::Instance()->CreateNode(position);
    particleSystem = sceneManager->createParticleSystem(particle_name, template_name);

    if (!particleSystem) {
        return {false, "Failed to create ParticleSystem"};
    }

    node->attachObject(particleSystem);
    node->setScale(VR2OgreV3(scale));

    // Configurar color, duración y densidad del sistema de partículas

    particleSystem->getEmitter(0)->setParameter("particle_width", std::to_string(scale.GetX()));
    particleSystem->getEmitter(0)->setParameter("particle_height", std::to_string(scale.GetY()));
    particleSystem->getEmitter(0)->setParameter("duration", std::to_string(duration));
    particleSystem->getEmitter(0)->setParameter("emission_rate", std::to_string(density));

    particleSystem->setDefaultDimensions(scale.GetX(), scale.GetY());

    // Configurar color
    Ogre::ColourValue ogreColor(color.GetX(), color.GetY(), color.GetZ(), color.GetW());
    //particleSystem->setColour(ogreColor);

    return {true, "SmokeEffect initialized"};
}

void SmokeEffect::Update(const double& dt) {
    duration -= dt;
    if (duration <= 0) {
        sceneManager->destroyParticleSystem(particleSystem);
        RenderManager::Instance()->DeleteNode(node);
        delete this;
        return;
    }

    // Dispersión del humo
    Ogre::Vector3 displacement(Ogre::Math::RangeRandom(-0.1f, 0.1f), Ogre::Math::RangeRandom(0.0f, 0.1f), Ogre::Math::RangeRandom(-0.1f, 0.1f));
    node->translate(displacement * dt, Ogre::Node::TransformSpace::TS_WORLD);
}

// Implementación de los getters
const VeryReal::Vector3& SmokeEffect::getPosition() const { return position; }

const VeryReal::Vector3& SmokeEffect::getScale() const { return scale; }

const VeryReal::Vector4& SmokeEffect::getColor() const { return color; }

float SmokeEffect::getDuration() const { return duration; }

float SmokeEffect::getDensity() const { return density; }

std::string SmokeEffect::getParticleSystemName() const { return particle_name; }

std::string SmokeEffect::getTemplateName() const { return template_name; }
