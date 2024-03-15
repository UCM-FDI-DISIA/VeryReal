#pragma once
#ifndef ANIMATIONCOMPONENT
#define ANIMATIONCOMPONENT
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
	class MeshRenderComponent;
	class TransformComponent;
	class Vector3;
	class Vector4;

	class  AnimatorComponent : public Component
	{

		public:
			//constructora de la clase animaci�n que es un componente de cualquier entidad que queramos que tenga movimiento
			AnimatorComponent();
			// Inicializa el componente con un nombre, un gestor de escena, y las componentes de transformaci�n y renderizado de malla.
			bool InitComponent( std::string name);
			// Destructor de la clase AnimatorComponent.
			virtual ~AnimatorComponent(); 
			// Crea una animaci�n con el nombre y la duraci�n especificados.
			void createAnimation(std::string t_name, double t_duration);
			// Establece los fotogramas clave de una animaci�n con la transformaci�n especificada.
			void setFrameAnimation(std::string t_nameAnimation, double t_duration,
				Vector3 t_translate, Vector4 t_rotacion, Vector3 t_scale);
			// Activa o desactiva una animaci�n seg�n el nombre y el comportamiento de bucle.
			void setAnimation(std::string t_name, bool t_active, bool t_loop);
			// Activa o desactiva todas las animaciones.
			void allAnimations(bool t_active);
			// Obtiene el n�mero de animaciones activas.
			int getAnimationsActive() { return num_animations_active; };
			// Actualiza el componente seg�n el tiempo delta proporcionado.
			void Update(const double& dt) override;

		private:
			bool active;
			bool loop;
			std::unordered_map<std::string, Ogre::AnimationState*> animations;
			Ogre::SceneManager* scene_mngr;
			TransformComponent* transform;
			MeshRenderComponent* meshRender;
			int num_animations_active;
			std::string name;



	};

}
#endif // !ANIMATIONCOMPONENT