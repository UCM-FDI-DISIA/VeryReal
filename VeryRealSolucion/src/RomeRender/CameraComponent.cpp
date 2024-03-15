#include "CameraComponent.h"
#include <OgreViewport.h>
#include <iostream>
#include <Ogre.h>
#include <Vector3.h>
#include <Vector2.h>
#include "VariantClass.h"
#include "RenderManager.h"
using namespace VeryReal;
using namespace Ogre;

CameraComponent::~CameraComponent()
{
       
}
    void CameraComponent::InitComponent(std::string name, Vector3 color, VeryReal::Vector3 offset) {
        //camara
        mNode = mgr->getRootSceneNode()->createChildSceneNode(); //nodo  de la camara
        mNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
        mNode->setPosition(0, 0, 30);
        camara = mgr->createCamera(name); // objeto y camara en si 
        camara->setNearClipDistance(1); //queremos que serenderice lo mas cerca posible desde la camara
        mNode->attachObject(camara);
        vewport = RenderManager::Instance()->GetRenderWindow()->addViewport(camara);

        //cambio de color de fondo

        vewport->setBackgroundColour(Ogre::ColourValue(color.GetX(), color.GetY(),color.GetZ()));

    }

    void CameraComponent::lookAt( VeryReal::Vector3 pos)
    {
        Ogre::Vector3 p(pos.GetX(), pos.GetY(), pos.GetZ());
        mNode->lookAt(p, Ogre::Node::TransformSpace::TS_PARENT);
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
    void CameraComponent::active()
    {
        vewport->setCamera(camara);
    }

 
    
