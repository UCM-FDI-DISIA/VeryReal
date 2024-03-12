#pragma once
#pragma once
#ifndef __ENTITYCOMPONENT_AUDIOLISTENER
#define __ENTITYCOMPONENT_AUDIOLISTENER

#include <Component.h>
//#include "EntityComponent/FactoryComponent.h"
#include <Vector3.h>

namespace FMOD {
	class Sound;
}


	class Audio_Leon;

	////Creates and destroys Audio_Listener components
	//class FactoryAudioListener : public FactoryComponent {
	//public:
	//	Component* create(Parameters& params) override;
	//	void destroy(Component* component) override;
	//};


	//FMOD ofrece "escuchadores" dinámicos que hacen de veces de receptores de los sonidos reproducidos por FMOD.
	//Este componente gestiona el listener de una entidad y actualiza sus parámetros.
	class Audio_Listener : public VeryReal::Component
	{
	public:
		//Constructora por defecto de AudioListener.
		Audio_Listener();
		//Destructora del componente AudioListener.
		~Audio_Listener();


		virtual void Start();

		/// <summary>
		/// Actualiza la posición del "listener" de FMOD en función de la posición de la entidad a la que este componente esta enlazado.
		/// </summary>
		/// <param name="dt">El delta time que se encarga de sincronizar las actualizaciones.</param>
		virtual void Update(const double& dt);

		/// <summary>
		/// Establece la posición de un listener.
		/// </summary>
		/// <param name="index">El índice necesario para referirse a un listener.</param>
		/// <param name="listenerPos">´Vector posición a establecer del listener.</param>
		/// <param name="listenerFW">Vector forward a establecer del listener.</param>
		/// <param name="listenerUP">Vector up a establecer del listener.</param>
		/// <param name="listenerVel">Vector de velocidad a establecer del listener.</param>
		void UpdateListenersPosition(int index, VeryReal::Vector3 listenerPos,
			VeryReal::Vector3 listenerFW, VeryReal::Vector3 listenerUP, VeryReal::Vector3 listenerVel = { 0,0,0 });

	private:
		//Posición del listener.
		VeryReal::Vector3 position;
		//Última posicióm registrada del listener.
		VeryReal::Vector3 last_position = { 0,0,0 };
		//Índice con el que se identifica cada listener para FMOD.
		int listener_index;
	};


#endif // !EC_AUDIO_LISTENER