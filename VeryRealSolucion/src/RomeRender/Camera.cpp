#include "Camera.h"
#include <OgreViewport.h>
#include <iostream>

using namespace VeryReal;
using namespace Ogre;

    Camara::Camara(std::string name, float t_color_x, float t_color_y, float t_color_z){
        vewport = nullptr;
        /* auto sys = m_mngr->getSystem<RenderSystem>();
                m_scene_mngr = FlamingoSceneManager().getSceneToAttach()->getSceneManger();
                m_cam = nullptr;
                m_vp = nullptr;
                m_target = nullptr;
                m_window = sys->getWindow();
                m_cam_node = FlamingoSceneManager().getSceneToAttach()->getSceneRoot()->createChildSceneNode();
                m_name = t_name;
                m_color = { t_color_x, t_color_y, t_color_z };*/
    }

    Camara::~Camara()
    {
       
    }

    void Camara::InitComponent()
    {
        //auto t = getComponent<Transform>(m_ent);
        //if (t == nullptr)
        //{
        //    throw std::exception("Transform is missing");
        //}
        //m_cam = m_scene_mngr->createCamera(m_name);
        //m_cam_node->setScale(t->getScale());
        //m_cam_node->setPosition(t->getPosition());
        //m_cam_node->attachObject(m_cam);

        //m_vp = m_window->getRenderWindow()->addViewport(m_cam, -m_window->getRenderWindow()->getNumViewports());
        //m_vp->setDimensions(0, 0, 1, 1); // Tamaño completo de la ventana
        //m_vp->setBackgroundColour(m_color);
    }

    void Camara::lookAt( Vector3 t_pos)
    {
       
        mNode->lookAt(t_pos, Ogre::Node::TransformSpace::TS_PARENT);
            
    }

    void Camara::translate(float t_x, float t_y, float t_z)
    {
        mNode->translate(t_x, t_y, t_z, Ogre::Node::TransformSpace::TS_LOCAL);
    }

    void Camara::roll(float t_d)
    {
        mNode->roll(Ogre::Degree(t_d));
    }

    void Camara::yaw(float t_d)
    {
        mNode->yaw(Ogre::Degree(t_d));
    }

    void Camara::pitch(float t_d)
    {
        mNode->pitch(Ogre::Degree(t_d));
    }

    void Camara::setAutoAspectRatio(bool t_b)
    {
        camara->setAspectRatio(t_b);
    }

    void Camara::setNearClipDistance(float t_clip)
    {
        camara->setNearClipDistance(t_clip);
    }

    void Camara::setFarClipDistance(float t_clip)
    {
        camara->setFarClipDistance(t_clip);
    }

    void Camara::setViewPortBackgroundColour(Ogre::ColourValue t_vp_color)
    {
        vewport->setBackgroundColour(t_vp_color);
    }

    void Camara::desactiveViewport()
    {
        vewport->setVisibilityMask(0);
    }

    void Camara::activeViewport()
    {
        vewport->setVisibilityMask(1);
    }
    void Camara::desactive()
    {
        vewport->setCamera(nullptr);
    }
    Ogre::SceneNode* Camara::getNode()
    {
        return mNode;
    }
    void Camara::active()
    {
        vewport->setCamera(camara);
    }

    
    void Camara::setOffset(Vector3 offset)
    {
        m_offset = offset;
    }
    void Camara::FollowTarget()
    {
        /*if (m_target != nullptr)
        {
            auto trpTarget = m_mngr->getComponent<Transform>(m_target);
            auto mtrp = m_mngr->getComponent<Transform>(m_ent);

            SVector3 newOffset = trpTarget->getRotation().Rotate(m_offset);
            mtrp->setPosition(trpTarget->getPosition() - newOffset);
            mtrp->setRotation(trpTarget->getRotation(), WORLD);

            lookAt({ trpTarget->getPosition().getX(), trpTarget->getPosition().getY(), trpTarget->getPosition().getZ() }, WORLD);
            roll(180);
        }*/
    }