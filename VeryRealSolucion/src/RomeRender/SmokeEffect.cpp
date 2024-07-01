#include "SmokeEffect.h"
#include "RenderManager.h"
#include "conversorvectores.h"
#include <OgreParticleSystem.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreParticleEmitter.h>
#include <unordered_map>
#include <iostream>   // Para los logs

using namespace VeryReal;

namespace {
std::unordered_map<std::string, Ogre::ParticleSystem*> particleSystemCache;
}

SmokeEffect::~SmokeEffect() {
    if (sceneManager) {
        for (const auto& pair : particleSystemCache) {
            Ogre::ParticleSystem* ps = pair.second;
            if (ps) {
                ps->setEmitting(false);
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
                                                        VeryReal::Vector3 _scale, VeryReal::Vector4 _color, float _density,
                                                        VeryReal::Vector3 _direction, float _duration) {
    particle_name = particleSystemName;
    template_name = templateName;
    position = _position;
    scale = _scale;
    color = _color;
    density = _density;
    direction = _direction;
    duration = _duration;

    std::cout << "Initializing SmokeEffect with parameters:" << std::endl;
    std::cout << "ParticleSystemName: " << particle_name << std::endl;
    std::cout << "TemplateName: " << template_name << std::endl;
    std::cout << "Position: " << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << std::endl;
    std::cout << "Scale: " << scale.GetX() << ", " << scale.GetY() << ", " << scale.GetZ() << std::endl;
    std::cout << "Color: " << color.GetX() << ", " << color.GetY() << ", " << color.GetZ() << ", " << color.GetW() << std::endl;
    std::cout << "Density: " << density << std::endl;
    std::cout << "Direction: " << direction.GetX() << ", " << direction.GetY() << ", " << direction.GetZ() << std::endl;
    std::cout << "Duration: " << duration << std::endl;

    sceneManager = RenderManager::Instance()->SceneManagerOgree();
    if (!sceneManager) {
        return {false, "SceneManager was null, ERROR from InitComponent SmokeEffect"};
    }

    node = RenderManager::Instance()->CreateNode(position);
    if (!node) {
        return {false, "Failed to create SceneNode"};
    }

    // Check if particle system already exists
    if (particleSystemCache.find(particle_name) != particleSystemCache.end()) {
        particleSystem = particleSystemCache [particle_name];

        // Detach from the old node if it's already attached
        if (particleSystem->isAttached()) {
            particleSystem->getParentSceneNode()->detachObject(particleSystem);
        }

        // Attach to the new node
        node->attachObject(particleSystem);
        node->setPosition(VR2OgreV3(position));

        std::cout << "ParticleSystem " << particle_name << " already exists, reattached to the new node." << std::endl;
    }
    else {
        // Create new particle system
        particleSystem = sceneManager->createParticleSystem(particle_name, template_name);
        particleSystemCache [particle_name] = particleSystem;

        node->attachObject(particleSystem);
        node->setScale(VR2OgreV3(scale));

        if (particleSystem->getNumEmitters() > 0) {
            Ogre::ParticleEmitter* emitter = particleSystem->getEmitter(0);
            emitter->setParameter("particle_width", std::to_string(scale.GetX()));
            emitter->setParameter("particle_height", std::to_string(scale.GetY()));
            emitter->setParameter("emission_rate", std::to_string(density));
            emitter->setParameter("time_to_live", std::to_string(duration));
            emitter->setParameter("velocity", "5");   // Ajusta la velocidad de las partículas si es necesario
            emitter->setParameter("direction", std::to_string(1) + " " + std::to_string(1) + " " + std::to_string(1));

            std::cout << "Emitter parameters set:" << std::endl;
            std::cout << "Particle Width: " << scale.GetX() << std::endl;
            std::cout << "Particle Height: " << scale.GetY() << std::endl;
            std::cout << "Emission Rate: " << density << std::endl;
            std::cout << "Time to Live: " << duration << std::endl;
            std::cout << "Velocity: 100" << std::endl;
            std::cout << "Angle: 30" << std::endl;
            std::cout << "Direction: " << direction.GetX() << " " << direction.GetY() << " " << direction.GetZ() << std::endl;
        }

        particleSystem->setDefaultDimensions(1, 1);
        particleSystem->setEmitting(true);
    }

    if (particleSystem){
        std::cout << "SmokeEffect initialized successfully" << std::endl;
        return {true, "SmokeEffect initialized"};
    }
    else
    {
        return {false, "Failed to create ParticleSystem"};
    }


}

void SmokeEffect::Update(const double& dt) {
    if (node) {
        Ogre::Vector3 displacement(Ogre::Math::RangeRandom(-0.1f, 0.1f), Ogre::Math::RangeRandom(0.0f, 0.1f), Ogre::Math::RangeRandom(-0.1f, 0.1f));
        node->translate(displacement * dt, Ogre::Node::TransformSpace::TS_WORLD);
        //std::cout << "SmokeEffect dispersed. New Position: " << node->getPosition().x << ", " << node->getPosition().y << ", " << node->getPosition().z << std::endl;
    }

    // Reasignar particleSystem desde la caché si es null
    if (!particleSystem) {
        particleSystem = particleSystemCache [getParticleSystemName()];
    }

    if (particleSystem) {
        particleSystem->setEmitting(encendido);
    }
}

void SmokeEffect::setEncendido() {
    encendido = true;
    if (particleSystem) {
        particleSystem->setEmitting(true);
        std::cout << "ParticleSystem emitting set to true. Current emitting state: " << particleSystem->getEmitting() << std::endl;
    }
}


void SmokeEffect::setApagado() {
    encendido = false;
    if (particleSystem) {
        particleSystem->setEmitting(false);
        std::cout << "ParticleSystem emitting set to false. Current emitting state: " << particleSystem->getEmitting() << std::endl;

    }
}

const VeryReal::Vector3& SmokeEffect::getPosition   () const { return position; }
void SmokeEffect::setPosition(VeryReal::Vector3 v)  {
    position = v;   // Actualiza la posición interna

    if (node) {
        node->setPosition(VR2OgreV3(v));   // Actualiza la posición del nodo de Ogre
    }

    std::cout << "SmokeEffect position set to: " << v.GetX() << ", " << v.GetY() << ", " << v.GetZ() << std::endl;
}

const VeryReal::Vector3& SmokeEffect::getScale() const { return scale; }
const VeryReal::Vector4& SmokeEffect::getColor() const { return color; }
float SmokeEffect::getDensity() const { return density; }
std::string SmokeEffect::getParticleSystemName() const { return particle_name; }
std::string SmokeEffect::getTemplateName() const { return template_name; }
float SmokeEffect::getDuration() const { return duration; }
const VeryReal::Vector3& SmokeEffect::getDirection() const { return direction; }
