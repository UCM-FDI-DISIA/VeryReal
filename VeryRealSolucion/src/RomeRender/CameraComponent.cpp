#pragma once
#pragma warning(disable : 4251)
#include <Ogre.h>
#include <OgreViewport.h>
#pragma warning(default : 4251)

#include "CameraComponent.h"
#include <iostream>
#include <Vector2.h>
#include "RenderManager.h"
#include "conversorvectores.h"
#include "TransformComponent.h"
#include "Entity.h"

using namespace VeryReal;
using namespace Ogre;

CameraComponent::~CameraComponent() {
       
}

bool CameraComponent::InitComponent(std::string name, Vector3 color, VeryReal::Vector3 offset) {
    //camara
    mgr = VeryReal::RenderManager::Instance()->SceneManagerOgree();
    mNode = mgr->getRootSceneNode()->createChildSceneNode(); //nodo  de la camara
    mNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
    mNode->setPosition(0, 0, 30);
    camara = mgr->createCamera(name); // objeto y camara en si 
    camara->setNearClipDistance(1); //queremos que serenderice lo mas cerca posible desde la camara
    mNode->attachObject(camara);
    vewport = RenderManager::Instance()->GetRenderWindow()->addViewport(camara);

    //cambio de color de fondo

    vewport->setBackgroundColour(Ogre::ColourValue(color.GetX(), color.GetY(),color.GetZ()));
    return true;

}

void CameraComponent::Update(const double& dt) {

    if (ent != nullptr) {
        VeryReal::Vector3 v = ent->GetComponent<TransformComponent>("transform")->GetPosition();

        translate(v.GetX(), v.GetY(), v.GetZ());
    }
}
void CameraComponent::lookAt( VeryReal::Vector3 pos)
{
    mNode->lookAt(VR2OgreV3(pos), Ogre::Node::TransformSpace::TS_PARENT);
}

void CameraComponent::translate(float x, float y, float z)
{
    mNode->translate(x, y, z, Ogre::Node::TransformSpace::TS_LOCAL);
}

void CameraComponent::roll(float d)
{
    mNode->roll(Ogre::Degree(d));
}

void CameraComponent::yaw(float d)
{
    mNode->yaw(Ogre::Degree(d));
}

void CameraComponent::pitch(float d)
{
    mNode->pitch(Ogre::Degree(d));
}
void CameraComponent::Offset(VeryReal::Vector2 offset)
{
    camara->setFrustumOffset(offset.GetX(), offset.GetY());
}
void CameraComponent::setNearClipDistance(float t_clip)
{
    camara->setNearClipDistance(t_clip);
}

void CameraComponent::setFarClipDistance(float t_clip)
{
    camara->setFarClipDistance(t_clip);
}

void CameraComponent::setViewPortBackgroundColour(Ogre::ColourValue t_vp_color)
{
    vewport->setBackgroundColour(t_vp_color);
}

void CameraComponent::desactiveViewport()
{
    vewport->setVisibilityMask(0);
}

void CameraComponent::activeViewport()
{
    vewport->setVisibilityMask(1);
}

void CameraComponent::desactive()
{
    vewport->setCamera(nullptr);
}

Ogre::SceneNode* CameraComponent::getNode()
{
    return mNode;
}

void CameraComponent::SetTarget(VeryReal::Entity* e) { 
    ent = e;
}

void CameraComponent::active()
{
    vewport->setCamera(camara);
}