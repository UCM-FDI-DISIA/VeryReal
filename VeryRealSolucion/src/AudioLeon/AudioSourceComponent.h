#pragma once
#ifndef __ENTITYCOMPONENT_AUDIOSOURCE
#define __ENTITYCOMPONENT_AUDIOSOURCE

#include <string>
#include <Component.h>
#include "exportAudioLeon.h"

namespace FMOD {
	class Sound;
}

namespace VeryReal {
	class TransformComponent;
	class Vector3;
    class AudioManager;
  }

enum FMOD_RESULT;
typedef unsigned int FMOD_MODE;
	

	
#pragma warning(disable : 4251)

	//AudioSourceComponent se encarga de reproducir un archivo de audio en la escena.
	//Los Audio_Listeners que se encuentren en rango escucharán el audio con distintas variaciones en lugar de su posición en la escena.
	class  VERYREAL_AUDIOLEON  AudioSourceComponent : public VeryReal::Component {
	public:

		//Constructor por defecto.
		AudioSourceComponent();
		//Destructora que se encarga de eliminar la memoria dinámica del sonido concreto.
		~AudioSourceComponent();
		bool InitComponent(std::string name, std::string path, bool onstart=false, std::string groupchannel="master", float volume=0.1,
		bool threed=false, bool loop=false, float mindistance=1.0f, float maxdistance=60.0f);


		/// <summary>
		/// Crea un sonido 3D.
		/// </summary>
		/// <returns>Devuelve true o false en función de si el sonido fue creado con éxito o no.</returns>
		bool Create3DSound();

		/// <summary>
		/// Crea un sonido no 3D.
		/// </summary>
		/// <returns>Devuelve true o false en función de si el sonido fue creado con éxito o no.</returns>
		bool CreateNormalSound();

		/// <summary>
		/// Configuira los atributos 3D (posición y velocidad) de un sonido.
		/// </summary>
		/// <param name="soundName">El nombre del sonido cuyos atributos se van a configurar.</param>
		/// <param name="position">El valor de la posición de la fuente de sonido.</param>
		/// <param name="velocity"EL valor de la velocidad a la que se mueve la fuente de sonido.</param>
		/// <returns>Devuelve true o false en función de si los atributos fueron configurados con éxito o no.</returns>
		bool Set3DSoundAtributes(VeryReal::Vector3 position, VeryReal::Vector3 velocity);

		/// <summary>
		/// Comprueba si hay algún canal disponible para reproducir el sonido asignado al componente y se lo asigna para ser reproducido.
		/// </summary>
		/// <param name="channelGroup">EL grupo de canales desde el que se reproducirá el sonido.</param>
		/// <param name="channelPos">La posición del canal que será usado para paneado y atenuación.</param>
		/// <param name="channelVel">La velocidad del cana que será usado para efecto doppler.</param>
		/// <param name="channelVolume">Volumen de reproducción del sonido.</param>
		/// <returns>Devuelve true o false en función de si se encontró un canal para re3producir el sonido.</returns>
		bool PlayAudioSource(std::string channelGroup, VeryReal::Vector3* channelPos, VeryReal::Vector3* channelVel, float channelVolume);

		/// <summary>
		/// Busca un canal y en caso de que exista, para el sonido que se este reproduciendo, devolviéndolo al principio. 
		/// </summary>
		/// <returns>Devuelve true o false en función de si el sonido fue detenido con éxito o no.</returns>
		bool StopSound();

		/// <summary>
		/// Busca un canal y en caso de que exista, pause el sonido que se esté reproduciendo en ese canal.
		/// </summary>
		/// <param name="Pause">: indica si se pausa o se reactiva</param>
		/// <returns>Devuelve true o false en función de si el sonido fue detenido con éxito o no.</returns>
		bool PauseSound(bool Pause);

		/// <summary>
		/// Inicia el sonido con los parámetros que se hayan facilitado desde la factoría.
		/// </summary>
		virtual void Start();

		/// <summary>
		/// Actualiza a cada paso del bucle principal el componente AudioSource.
		/// </summary>
		/// <param name="dt">El delta time que se encarga de sincronizar las actualizaciones.</param>
		virtual void Update(const double& dt);

		/// <summary>
		/// Le da play al sonido del AudioSourceComponent.
		/// </summary>
		void Play();

		/// <summary>
		/// Detiene por completo el sonido del AudioSourceComponent.
		/// </summary>
		void Stop();

		/// <summary>
		/// Para el sonido del AudioSourceComponent.
		/// </summary>
		void Pause();

		/// <summary>
		/// Vuelve a reproducir un sonido desde donde se pausó.
		/// </summary>
		void Resume();

		/// <summary>
		/// Chequea si un audio esta siendo reproducido o no.
		/// </summary>
		/// <returns>DEvuelve truo o false en funcón de si el audio esta siendo reproducido o no.</returns>
		bool IsPlaying();

		/// <summary>
		/// Establece el volumen con el que un sonido será reproducido.
		/// </summary>
		/// <param name="value">El valor para el volumen que se establecerá.</param>
		/// <returns>Devuelve true o false en función de si se ha cambiado el volumen con éxito o no.</returns>
		bool SetVolume(float value);

		/// <summary>
		/// Establece la velocidad a la que un sonido será reproducido.
		/// </summary>
		/// <param name="newSpeed"></param>
		/// <returns></returns>
		bool SetSpeed(float newSpeed);

		/// <summary>
		/// Establece una nueva configuración para la atenuación mínima y máxima que sufrirña un sonido por distancia.
		/// </summary>
		/// <param name="minDistance">Distancia a la que no habrá ninguna atenuación.</param>
		/// <param name="maxDistance">Distancia a la que habrá máxima atenuación</param>
		/// <returns>Devuelve true o false en función de si las nuevas configuraciones para la atenuación fueron o no establecidas.</returns>
		bool SetMinMaxDistance(float minDistance, float maxDistance);

		/// <summary>
		/// Establece el modo de FMOD para cada sonido.
		/// </summary>
		/// <param name="newMode">Nueva flag que indica el modo a establecer.</param>
		/// <returns>Devuelve true o false en función de si el nuevo modo de reproducción fue establecido con éxito o no.</returns>
		bool SetMode(FMOD_MODE newMode);

		/// <summary>
		/// Almacena la ruta relativa del archivo de audio.
		/// </summary>
		/// <param name="path">El nombre de la ruta relativa.</param>
		void SetSourcePath(std::string path);

		/// <summary>
		/// Almacena el nombre dado por el usuario al sonido de FMOD.
		/// </summary>
		/// <param name="name">El nombre dado por el jugador.</param>
		void SetSourceName(std::string name);

		/// <summary>
		/// Almacena el nombre de grupo de canales desde el cuál se reproducirá este sonido.
		/// </summary>
		/// <param name="name">EL nombre del grupo de canales.</param>
		void SetGroupChannelName(std::string name);

		/// <summary>
		/// Almacena le condición de bucle del sonido de FMOD.
		/// </summary>
		/// <param name="lop">Devuelve true o false en función de si el sonido se reproducirá en bucle o no.</param>
		void SetLoop(bool lop);

		/// <summary>
		/// Almacena la condición de 3D del sonido de FMOD.
		/// </summary>
		/// <param name="threeD">La condición a almacenar.</param>
		void SetIsThreeD(bool threeD);

		/// <summary>
		/// Almacena si el sonido de FMOD será reproducido en cuanto sea posible o si hará falta darle al play.
		/// </summary>
		/// <param name="playOnStart">Si el sonido debe ser reproducido en cuanto sea posible o no.</param>
		void SetPlayOnStart(bool playOnStart);

		/**
		* Get the volume of the audio.
		* @return The current volume value.
		*/

		//Devuelve el valor de volumen almacenado en este componente.
		float GetVolume();


	private:
		//El volumen del sonido.
		float volume;
		//La velocidad de reproducción del audio.
		float speed;
		//Distancia de mínima atenuación de un sonido 3D.
		float min_distance;
		//Distancia de máxima atenuación de un sonido 3D.
		float max_distance;

		//FMOD::Sound* mSound; // The FMOD sound object
		//El número que se corresponde con el canal en el que se reproducirá este sonido.
		int sound_channel;
		//El nombre de grupo de canales en el que se reproducirá este sonido.
		std::string sound_group;
		//La ruta relativa al archivo de audio con el que se creará el sonido de FMOD.
		std::string sound_path;
		//El nombre dado por el usuario al sonido de FMOD.
		std::string sound_name;
		//Si el sonido esta siendo reproducido o no.
		bool playing = true;
		//Si el sonido se reproducirá en bucle o no.
		bool loop = false;
		//Si el sonido es 3D o no.
		bool is_three_d = false;
		//Si el sonido se reproducirá de inicio o no.
		bool play_on_start = true;

		//Variable de control que sirve de comprobación después de hacer uso de cualquiera de las funciones de sistema de sonido.
		FMOD_RESULT result;
		//Almacena el componente "Transform" y ·RigdBody" de la entidad a la que este componente esta enlazada.
		VeryReal::TransformComponent* transform = nullptr;
	};

#pragma warning(default : 4251)

#endif