#pragma warning(disable : 4251)
#include <OgreParticleSystem.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreParticleEmitter.h>

#pragma warning(disable : 4251)
#include "SmokeEffect.h"
#include "RenderManager.h"
#include "conversorvectores.h"
#include <unordered_map>
#include "Entity.h"
#include <iostream>   // Para los logs

using namespace VeryReal;

namespace {
std::unordered_map<std::string, Ogre::ParticleSystem*> particleSystemCache;
}

SmokeEffect::SmokeEffect() : sceneManager(nullptr), node(nullptr), particleSystem(nullptr) { }

SmokeEffect::~SmokeEffect() {
    if (sceneManager) {
        for (const auto& pair : particleSystemCache) {
            Ogre::ParticleSystem* ps = pair.second;
            if (ps) {
                std::cout << "Destroying ParticleSystem: " << pair.first << std::endl;
                sceneManager->destroyParticleSystem(ps);
            }
        }
        particleSystemCache.clear();
    }

    if (node) {
        std::cout << "Deleting Node" << std::endl;
        RenderManager::Instance()->DeleteNode(node);
        node = nullptr;
    }
}

std::pair<bool, std::string> SmokeEffect::InitComponent(std::string particleSystemName, std::string templateName, VeryReal::Vector3 _position,
                                                        VeryReal::Vector3 _scale, VeryReal::Vector4 _color, float _density) {
    particle_name = particleSystemName;
    template_name = templateName;
    position = _position;
    scale = _scale;
    color = _color;
    density = _density;   // Corrige esta línea, antes se reasignaba density a sí mismo.

    std::cout << "Initializing SmokeEffect with parameters:" << std::endl;
    std::cout << "ParticleSystemName: " << particle_name << std::endl;
    std::cout << "TemplateName: " << templateName << std::endl;
    std::cout << "Position: " << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << std::endl;
    std::cout << "Scale: " << scale.GetX() << ", " << scale.GetY() << ", " << scale.GetZ() << std::endl;
    std::cout << "Color: " << color.GetX() << ", " << color.GetY() << ", " << color.GetZ() << ", " << color.GetW() << std::endl;
    std::cout << "Density: " << density << std::endl;

    sceneManager = RenderManager::Instance()->SceneManagerOgree();
    if (!sceneManager) {
        return {false, "SceneManager was null, ERROR from InitComponent SmokeEffect"};
    }

    node = RenderManager::Instance()->CreateNode(position);
    if (!node) {
        return {false, "Failed to create SceneNode"};
    }

    if (sceneManager->hasParticleSystem(particle_name)) {
        particleSystem = sceneManager->getParticleSystem(particle_name);
    }
    else {
        try {
            particleSystem = sceneManager->createParticleSystem(particle_name, template_name);
            particleSystemCache [particle_name] = particleSystem;

            node->attachObject(particleSystem);
            node->setScale(VR2OgreV3(scale));

            if (particleSystem->getNumEmitters() > 0) {
                Ogre::ParticleEmitter* emitter = particleSystem->getEmitter(0);
                emitter->setParameter("particle_width", std::to_string(scale.GetX()));
                emitter->setParameter("particle_height", std::to_string(scale.GetY()));
                emitter->setParameter("emission_rate", std::to_string(density));
            }

            particleSystem->setDefaultDimensions(scale.GetX(), scale.GetY());

            std::cout << "SmokeEffect initialized successfully" << std::endl;

            return {true, "SmokeEffect initialized"};
        } catch (Ogre::Exception& e) {
            return {false, "Failed to create ParticleSystem: " + std::string(e.what())};
        }
    }

    return {true, "SmokeEffect initialized"};
}

void SmokeEffect::Update(const double& dt) {
    if (node) {
        Ogre::Vector3 displacement(Ogre::Math::RangeRandom(-0.1f, 0.1f), Ogre::Math::RangeRandom(0.0f, 0.1f), Ogre::Math::RangeRandom(-0.1f, 0.1f));
        node->translate(displacement * dt, Ogre::Node::TransformSpace::TS_WORLD);
        std::cout << "SmokeEffect dispersed. New Position: " << node->getPosition().x << ", " << node->getPosition().y << ", "
                  << node->getPosition().z << std::endl;
    }
}

const VeryReal::Vector3& SmokeEffect::getPosition() const { return position; }
const VeryReal::Vector3& SmokeEffect::getScale() const { return scale; }
const VeryReal::Vector4& SmokeEffect::getColor() const { return color; }
float SmokeEffect::getDensity() const { return density; }
std::string SmokeEffect::getParticleSystemName() const { return particle_name; }
std::string SmokeEffect::getTemplateName() const { return template_name; }
