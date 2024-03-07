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
	using namespace std;
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
		void update(const double& dt);
		void setActive(bool a); //metodo para activar la animacion
		void setLoop(bool l);  //metodo que pone la animacion en bucle
		string getCurrAnimName();  //para que devuelva el nombre de la anim actual
		bool isActive(); // getter
		bool isLoop(); //geter
		void playAnim(string animacion, bool loop = true); //inicia una aminacion
		void stopAnim(); //la para
		void resumeAnim(); //la vuelve a iniciar (no la crea)
		void createAnimation(string t_name, double t_duration);
		void setAnimation(std::string t_name, bool t_active, bool t_loop);
		void allAnimations(bool t_active);
		void setFrameAnimation(std::string t_nameAnimation, double t_duration,
			Vector3 t_translate, Vector4 t_rotacion, Vector3 t_scale);

	private:
		bool active;
		bool loop;
		unordered_map<string, Ogre::AnimationState*> m_animations;
		Ogre::SceneManager* m_scene_mngr;
		TransformComponent* m_transform;
		MeshRender* m_meshRender;
		int m_num_animations_active;
		std::string m_name;
		Ogre::AnimationState* mCurrentState; // Pointer to the current animation state

		Ogre::AnimationStateSet* mAnimStatesMap; // Pointer to the animation state set


	};

}
