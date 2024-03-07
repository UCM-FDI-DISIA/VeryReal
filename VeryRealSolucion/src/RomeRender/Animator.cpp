#include "Animator.h"
#include "MeshRender.h"
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Entity.h>
#include <OgreAnimationState.h>
using namespace VeryReal;
using namespace std;


Animator::Animator()
{
    m_scene_mngr = nullptr;
    m_name = "";
    m_num_animations_active = (0);
    m_transform = nullptr;
    m_meshRender = nullptr;
    m_transform = nullptr;

    
}
void Animator::InitComponent(Ogre::SceneManager* m_scene_mng, std::string name, TransformComponent* trans, MeshRender* meshrender) {
    m_scene_mngr = m_scene_mng;
    m_name = name;
    m_num_animations_active = (0);
    m_transform = nullptr;
    m_meshRender = nullptr;
    m_transform = trans;

    if (m_transform == nullptr)
    {
        throw std::exception("no existe Transform");
    }

    m_meshRender = meshrender;

    if (m_meshRender == nullptr)
    {
        throw std::exception("no existe MeshRender");
    }

    m_animations = std::unordered_map<std::string, Ogre::AnimationState*>();
    if (m_meshRender->getOgreEntity()->getAllAnimationStates() != nullptr)
        if (m_meshRender->getOgreEntity()->getAllAnimationStates() != nullptr)
        {
            Ogre::AnimationStateMap mapa = m_meshRender->getOgreEntity()->getAllAnimationStates()->getAnimationStates();
            for (auto it = mapa.begin(); it != mapa.end(); it++)
            {
                m_animations.insert({ it->first, it->second });
            }
        }
}
Animator::~Animator()
{
}
void Animator::update(const double& dt)
{
    if (mCurrentState != nullptr && active) {
        // Increment the animation time by the time between frames
        mCurrentState->addTime(dt);
    }
    int num = 0;
    auto it = m_animations.begin();
   /* while (num != m_num_animations_active)
    {
        if (it->second->getEnabled())
        {
            it->second->addTime(Ogre::Real(time));
            num++;
        }
        it++;
    }*/
}

void Animator::setActive(bool active)
{
    // Set the enabled state for the current animation
    mCurrentState->setEnabled(active);
}

void Animator::setLoop(bool loop)
{
    // Set the loop state for the current animation
    mCurrentState->setLoop(loop);
}

std::string Animator::getCurrAnimName()
{
    // Return the name of the current animation
    return mCurrentState->getAnimationName();
}

bool Animator::isActive()
{
    // Return whether the current animation is enabled
    return mCurrentState->getEnabled();
}

bool Animator::isLoop()
{
    // Return whether the current animation is set to loop
    return mCurrentState->getLoop();
}


void Animator::playAnim(std::string anim, bool loop)
{
    if (mCurrentState != nullptr)
        mCurrentState->setEnabled(false);

    // cambia el estado actual
    mCurrentState = mAnimStatesMap->getAnimationState(anim);
    // lo activa
    mCurrentState->setEnabled(true);
    // bucle
    mCurrentState->setLoop(loop);
    mCurrentState->setTimePosition(0);
    active = true;
}

void Animator::stopAnim()
{

    active = false;
}

void Animator::resumeAnim()
{

    active = true;
}



void Animator::createAnimation(std::string t_name, double t_duration)
{
    Ogre::Animation* animation = m_scene_mngr->createAnimation(t_name, Ogre::Real(t_duration));
    Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
    track->setAssociatedNode(m_meshRender->getNode());

    auto aux = m_scene_mngr->createAnimationState(t_name);
    m_animations.insert({ t_name, aux });
    setAnimation(t_name, false, false);
}

void Animator::setFrameAnimation(std::string t_nameAnimation, double t_duration,
    Vector3 t_translate, Vector4 t_rotacion, Vector3 t_scale)
{
    Ogre::Animation* animation = m_scene_mngr->getAnimation(t_nameAnimation);
    Ogre::NodeAnimationTrack* track = animation->getNodeTrack(0);

    Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(Ogre::Real(t_duration));
   /* kf->setTranslate(t_translate);
    kf->setRotation(t_rotacion);
    kf->setScale(t_scale);*/
}

void Animator::allAnimations(bool t_active)
{
    m_num_animations_active = t_active == true ? m_animations.size() : 0;
    for (auto it = m_animations.begin(); it != m_animations.end(); it++)
    {
        it->second->setEnabled(t_active);
        it->second->setLoop(t_active);
    }
}

void Animator::setAnimation(std::string t_name, bool t_active, bool t_loop)
{
    auto it = m_animations.find(t_name);
    if (it != m_animations.end())
    {
        it->second->setEnabled(t_active);
        it->second->setLoop(t_loop);
        m_num_animations_active += t_active ? +1 : -1;
    }

}
