//#include "Animator.h"
//#include "MeshRender.h"
//#include <OgreAnimation.h>
//#include <OgreKeyFrame.h>
//#include <OgreSceneManager.h>
//#include <OgreEntity.h>
//#include <string.h>
//#include <Entity.h>
//#include <OgreAnimationState.h>
//using namespace VeryReal;
//using namespace std;
//
//
//Animator::Animator(Ogre::SceneManager* m_scene_mng, std::string name, TransformComponent* trans, MeshRender* meshrender)
//{
//    m_scene_mngr = m_scene_mng;
//    m_name = name;
//    m_num_animations_active = (0);
//    m_transform = nullptr;
//    m_meshRender = nullptr;
//    m_transform = trans;
//
//    if (m_transform == nullptr)
//    {
//        throw std::exception("no existe Transform");
//    }
//
//    m_meshRender = meshrender;
//
//    if (m_meshRender == nullptr)
//    {
//        throw std::exception("no existe MeshRender");
//    }
//
//    m_animations = std::unordered_map<std::string, Ogre::AnimationState*>();
//    if (m_meshRender->getOgreEntity()->getAllAnimationStates() != nullptr)
//    if (m_meshRender->getOgreEntity()->getAllAnimationStates() != nullptr)
//    {
//        Ogre::AnimationStateMap mapa = m_meshRender->getOgreEntity()->getAllAnimationStates()->getAnimationStates();
//        for (auto it = mapa.begin(); it != mapa.end(); it++)
//        {
//            m_animations.insert({ it->first, it->second });
//        }
//    }
//}
//
//Animator::~Animator()
//{
//}
//void Animator::update(const double& dt)
//{
//    if (mCurrentState != nullptr && active) {
//        // Increment the animation time by the time between frames
//        mCurrentState->addTime(dt);
//    }
//    
//}
//
//void Animator::setActive(bool active)
//{
//    // Set the enabled state for the current animation
//    mCurrentState->setEnabled(active);
//}
//
//void Animator::setLoop(bool loop)
//{
//    // Set the loop state for the current animation
//    mCurrentState->setLoop(loop);
//}
//
//std::string Animator::getCurrAnimName()
//{
//    // Return the name of the current animation
//    return mCurrentState->getAnimationName();
//}
//
//bool Animator::isActive()
//{
//    // Return whether the current animation is enabled
//    return mCurrentState->getEnabled();
//}
//
//bool Animator::isLoop()
//{
//    // Return whether the current animation is set to loop
//    return mCurrentState->getLoop();
//}
//
//
//void Animator::playAnim(std::string anim, bool loop)
//{
//    if (mCurrentState != nullptr)
//        mCurrentState->setEnabled(false);
//
//    // cambia el estado actual
//    mCurrentState = mAnimStatesMap->getAnimationState(anim);
//    // lo activa
//    mCurrentState->setEnabled(true);
//    // bucle
//    mCurrentState->setLoop(loop);
//    mCurrentState->setTimePosition(0);
//    active = true;
//}
//
//void Animator::stopAnim()
//{
//
//    active = false;
//}
//
//void Animator::resumeAnim()
//{
//
//    active = true;
//}
//
