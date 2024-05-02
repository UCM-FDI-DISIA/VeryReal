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
#include <Vector4.h>
#include "../../dependencies/Bullet/Src/src/LinearMath/btVector3.h"

using namespace VeryReal;
using namespace Ogre;

CameraComponent::~CameraComponent() {
       
}

bool CameraComponent::InitComponent(std::string name, Vector3 color, float alfa, VeryReal::Vector3 offset) {
    //camara
    mgr = VeryReal::RenderManager::Instance()->SceneManagerOgree();
    mNode = mgr->getRootSceneNode()->createChildSceneNode();   //nodo  de la camara
    mNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
    mNode->setPosition(0, 0, 30);
    camara = mgr->createCamera(name);   // objeto y camara en si
    camara->setNearClipDistance(1);     //queremos que serenderice lo mas cerca posible desde la camara
    mNode->attachObject(camara);
    vewport = RenderManager::Instance()->GetRenderWindow()->addViewport(camara);

    //cambio de color de fondo
    ent = this->GetEntity();
    Ogre::ColourValue* v = new ColourValue(color.GetX(), color.GetY(), color.GetZ(), alfa);
    vewport->setBackgroundColour(*v);
    return true;
}

void CameraComponent::Update(const double& dt) {
    //seguimiento 
    if (ent != nullptr) {
        VeryReal::Vector3 v = ent->GetComponent<TransformComponent>()->GetPosition();
        
        mNode->setPosition(v.GetX(), v.GetY(), v.GetZ());
 
        //mNode->roll(-mNode->getOrientation().getRoll());
    }
}

void CameraComponent::lookAt( VeryReal::Vector3 pos) {
    mNode->lookAt(VR2OgreV3(pos), Ogre::Node::TransformSpace::TS_PARENT);
}



void CameraComponent::translate(float x, float y, float z) {
    mNode->translate(x, y, z, Ogre::Node::TransformSpace::TS_LOCAL);
}

void CameraComponent::roll(float d) {
    //mNode->roll(Ogre::Degree(d));
     mNode->rotate(VeryReal::VR2OgreV3(Vector3(0, 0, 1)), Ogre::Degree(d), Ogre::Node::TS_WORLD);
}

void CameraComponent::yaw(float d) {
    //mNode->yaw(Ogre::Degree(d));
     mNode->rotate(VeryReal::VR2OgreV3(Vector3(0, 1, 0)), Ogre::Degree(d), Ogre::Node::TS_WORLD);
}

void CameraComponent::pitch(float d) {
    //mNode->pitch(Ogre::Degree(d));
     mNode->rotate(VeryReal::VR2OgreV3(Vector3(1, 0, 0)), Ogre::Degree(d), Ogre::Node::TS_WORLD);
}

void CameraComponent::rotate(float d, VeryReal::Vector3 v) { 
    mNode->rotate(VeryReal::VR2OgreV3(v), Ogre::Degree(d), Ogre::Node::TS_WORLD); 
}

void CameraComponent::Offset(VeryReal::Vector2 offset) {
    camara->setFrustumOffset(offset.GetX(), offset.GetY());
}

void CameraComponent::setNearClipDistance(float t_clip) {
    camara->setNearClipDistance(t_clip);
}

void CameraComponent::setFarClipDistance(float t_clip) {
    camara->setFarClipDistance(t_clip);
}

void CameraComponent::setViewPortBackgroundColour(Ogre::ColourValue t_vp_color) {
    vewport->setBackgroundColour(t_vp_color);
}

void CameraComponent::desactiveViewport() {
    vewport->setVisibilityMask(0);
}

void CameraComponent::activeViewport() {
    vewport->setVisibilityMask(1);
}

void CameraComponent::desactive() {
    vewport->setCamera(nullptr);
}

Ogre::SceneNode* CameraComponent::getNode() {
    return mNode;
}

void CameraComponent::SetTarget(VeryReal::Entity* e) { 
    ent = e;
}

void CameraComponent::active() {
    vewport->setCamera(camara);
}