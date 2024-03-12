#pragma once
#include "Component.h"
#include <string>
#include <unordered_map>

namespace Ogre
{
	class AnimationState;
	class SceneManager;
	class Entity;
	class Animation;
	class KeyFrame;
	class AnimationStateSet;

}
namespace VeryReal {
	class MeshRender;
	class TransformComponent;
	class Vector3;
	class Vector4;
	class  Animator : public Component
	{

	public:
		Animator();
		void InitComponent(Ogre::SceneManager* m_scene_mng, std::string name, TransformComponent* trans, MeshRender* meshrender);
		virtual ~Animator(); //destructora
		void createAnimation(std::string t_name, double t_duration);
		void setFrameAnimation(std::string t_nameAnimation, double t_duration,
			Vector3 t_translate, Vector4 t_rotacion, Vector3 t_scale);
		void setAnimation(std::string t_name, bool t_active, bool t_loop);
		void allAnimations(bool t_active);
		int getAnimationsActive() { return m_num_animations_active; };

		void Update(const double& dt) override;
		

	private:
		bool active;
		bool loop;
		std::unordered_map<std::string, Ogre::AnimationState*> m_animations;
		Ogre::SceneManager* m_scene_mngr;
		TransformComponent* m_transform;
		MeshRender* m_meshRender;
		int m_num_animations_active;
		std::string m_name;



	};

}
