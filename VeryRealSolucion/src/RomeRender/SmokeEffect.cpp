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
#include <unordered_map>
#include <string>
#include "Entity.h"
#include <iostream>   // Para los logs

using namespace VeryReal;

namespace {
std::unordered_map<std::string, Ogre::ParticleSystem*> particleSystemCache;
}

SmokeEffect::SmokeEffect() { }

SmokeEffect::~SmokeEffect() {
    if (particleSystem && sceneManager) {
        std::cout << "Destroying ParticleSystem: " << particle_name << std::endl;
        sceneManager->destroyParticleSystem(particleSystem);
        particleSystemCache.erase(particle_name);   // Remove from cache
        particleSystem = nullptr;
    }
    if (node) {
        std::cout << "Deleting Node" << std::endl;
        RenderManager::Instance()->DeleteNode(node);
        node = nullptr;
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

    std::cout << "Initializing SmokeEffect with parameters:" << std::endl;
    std::cout << "ParticleSystemName: " << particleSystemName << std::endl;
    std::cout << "TemplateName: " << templateName << std::endl;
    std::cout << "Position: " << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << std::endl;
    std::cout << "Scale: " << scale.GetX() << ", " << scale.GetY() << ", " << scale.GetZ() << std::endl;
    std::cout << "Color: " << color.GetX() << ", " << color.GetY() << ", " << color.GetZ() << ", " << color.GetW() << std::endl;
    std::cout << "Duration: " << duration << std::endl;
    std::cout << "Density: " << density << std::endl;

    sceneManager = RenderManager::Instance()->SceneManagerOgree();
    if (!sceneManager) {
        return {false, "SceneManager was null, ERROR from InitComponent SmokeEffect"};
    }

    node = RenderManager::Instance()->CreateNode(position);
    if (!node) {
        return {false, "Failed to create SceneNode"};
    }

    // Verificar si el sistema de partículas ya existe en el caché y destruirlo si es así
    //auto it = particleSystemCache.find(particleSystemName);
    //if (it != particleSystemCache.end()) {
    //    if (it->second) {
    //        std::cout << "Destroying existing ParticleSystem in cache: " << particleSystemName << std::endl;
    //        sceneManager->destroyParticleSystem(it->second);
    //    }
    //    particleSystemCache.erase(it);
    //}

    // Crear un nuevo sistema de partículas y almacenarlo en el caché
    try {
        particleSystem = sceneManager->createParticleSystem(particle_name, template_name);
    } catch (Ogre::Exception& e) {
        return {false, "Failed to create ParticleSystem: " + std::string(e.what())};
    }

    if (!particleSystem) {
        return {false, "Failed to create ParticleSystem"};
    }

    //particleSystemCache [particleSystemName] = particleSystem;

    node->attachObject(particleSystem);
    node->setScale(VR2OgreV3(scale));

    // Configurar color, duración y densidad del sistema de partículas
    if (particleSystem->getNumEmitters() > 0) {
        Ogre::ParticleEmitter* emitter = particleSystem->getEmitter(0);
        emitter->setParameter("particle_width", std::to_string(scale.GetX()));
        emitter->setParameter("particle_height", std::to_string(scale.GetY()));
        emitter->setParameter("duration", std::to_string(duration));
        emitter->setParameter("emission_rate", std::to_string(density));
    }

    particleSystem->setDefaultDimensions(scale.GetX(), scale.GetY());

    // Configurar color
    Ogre::ColourValue ogreColor(color.GetX(), color.GetY(), color.GetZ(), color.GetW());
    //particleSystem->setColour(ogreColor);

    std::cout << "SmokeEffect initialized successfully" << std::endl;
    return {true, "SmokeEffect initialized"};
}

void SmokeEffect::Update(const double& dt) {
    duration -= dt;
    std::cout << "Updating SmokeEffect. Remaining Duration: " << duration << std::endl;
    if (duration <= 0) {
        if (particleSystem && sceneManager) {
            std::cout << "Duration expired. Destroying ParticleSystem: " << particle_name << std::endl;
            sceneManager->destroyParticleSystem(particleSystem);
            particleSystemCache.erase(particle_name);   // Remove from cache
            particleSystem = nullptr;
        }
        if (node) {
            std::cout << "Duration expired. Deleting Node" << std::endl;
            RenderManager::Instance()->DeleteNode(node);
            node = nullptr;
        }
        this->GetEntity()->SetActive(false);
        return;
    }

    // Dispersión del humo
    if (node) {
        Ogre::Vector3 displacement(Ogre::Math::RangeRandom(-0.1f, 0.1f), Ogre::Math::RangeRandom(0.0f, 0.1f), Ogre::Math::RangeRandom(-0.1f, 0.1f));
        node->translate(displacement * dt, Ogre::Node::TransformSpace::TS_WORLD);
        std::cout << "SmokeEffect dispersed. New Position: " << node->getPosition().x << ", " << node->getPosition().y << ", "
                  << node->getPosition().z << std::endl;
    }
}

// Implementación de los getters
const VeryReal::Vector3& SmokeEffect::getPosition() const { return position; }

const VeryReal::Vector3& SmokeEffect::getScale() const { return scale; }

const VeryReal::Vector4& SmokeEffect::getColor() const { return color; }

float SmokeEffect::getDuration() const { return duration; }

float SmokeEffect::getDensity() const { return density; }

std::string SmokeEffect::getParticleSystemName() const { return particle_name; }

std::string SmokeEffect::getTemplateName() const { return template_name; }
