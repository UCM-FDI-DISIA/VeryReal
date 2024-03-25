#pragma warning(disable : 4251)
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreSceneManager.h>
#include <OgreAnimationState.h>
#include <OgreEntity.h>
#pragma warning(default : 4251)

#include <Entity.h>

#include "RenderManager.h"
#include "AnimatorComponent.h"
#include "MeshRenderComponent.h"
#include "TransformComponent.h"
#include "conversorvectores.h"

using namespace VeryReal;
using namespace std;

 AnimatorComponent::AnimatorComponent()
{
    scene_mngr = nullptr;
    name = "";
    num_animations_active = (0);
    transform = nullptr;
    meshRender = nullptr;
    transform = nullptr;

    
}

bool AnimatorComponent::InitComponent(std::string name) {
    scene_mngr = RenderManager::Instance()->SceneManagerOgree();
    name = name;
    num_animations_active = (0);

    if (GetEntity()->HasComponent("transform")) transform = GetEntity()->GetComponent<TransformComponent>("transform");
    else {
        #ifdef DEBUG_MODE
        std::cerr << DEBUG_TRANSFORM_ERROR;
        #endif
        return false;
    }
      
    
    if(GetEntity()->HasComponent("meshrender"))meshRender = GetEntity()->GetComponent<MeshRenderComponent>("meshrender");
    else {
        #ifdef DEBUG_MODE
        std::cerr << DEBUG_MESHRENDERER_ERROR;
         #endif
        return false;
    }
      

    animations = std::unordered_map<std::string, Ogre::AnimationState*>();
    if (meshRender->getOgreEntity()->getAllAnimationStates() != nullptr)
        if (meshRender->getOgreEntity()->getAllAnimationStates() != nullptr)
        {
            Ogre::AnimationStateMap mapa = meshRender->getOgreEntity()->getAllAnimationStates()->getAnimationStates();
            for (auto it = mapa.begin(); it != mapa.end(); it++)
            {
                animations.insert({ it->first, it->second });
            }
        }
    return true;
}
AnimatorComponent::~AnimatorComponent()
{
}
void AnimatorComponent::Update(const double& dt)
{
   
    int num = 0;
    auto it = animations.begin();
    while (num != num_animations_active)
    {
        if (it->second->getEnabled())
        {
            it->second->addTime((Ogre::Real)(dt* 0.001));
            num++;
        }
        it++;
    }
}



void AnimatorComponent::createAnimation(std::string t_name, double t_duration)
{
    Ogre::Animation* animation = scene_mngr->createAnimation(t_name, Ogre::Real(t_duration));
    Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
    track->setAssociatedNode(meshRender->getNode());

    auto aux = scene_mngr->createAnimationState(t_name);
    animations.insert({ t_name, aux });
    setAnimation(t_name, false, false);
}

void AnimatorComponent::setFrameAnimation(std::string t_nameAnimation, double t_duration,
    Vector3 t_translate, Vector4 t_rotacion, Vector3 t_scale)
{
    Ogre::Animation* animation = scene_mngr->getAnimation(t_nameAnimation);
    Ogre::NodeAnimationTrack* track = animation->getNodeTrack(0);

    Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(Ogre::Real(t_duration));
   
    kf->setTranslate(VR2OgreV3(t_translate));
    kf->setRotation(Ogre::Quaternion(t_rotacion.GetR(), t_rotacion.GetG(), t_rotacion.GetB(), t_rotacion.GetA()));
    kf->setScale(VR2OgreV3(t_scale));
}

void AnimatorComponent::allAnimations(bool t_active)
{
    num_animations_active = t_active == true ? (int)animations.size() : 0;
    for (auto it = animations.begin(); it != animations.end(); it++)
    {
        it->second->setEnabled(t_active);
        it->second->setLoop(t_active);
    }
}

void AnimatorComponent::setAnimation(std::string t_name, bool t_active, bool t_loop)
{
    auto it = animations.find(t_name);
    if (it != animations.end())
    {
        it->second->setEnabled(t_active);
        it->second->setLoop(t_loop);
        num_animations_active += t_active ? +1 : -1;
    }

}
