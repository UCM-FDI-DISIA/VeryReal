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
	class  Animator : public Component
	{

	public:
		Animator();
		Animator(Ogre::SceneManager* m_scene_mng, std::string name, TransformComponent* trans, MeshRender* meshrender); //constructora
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
