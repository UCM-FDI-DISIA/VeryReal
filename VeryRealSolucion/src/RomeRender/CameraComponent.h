#pragma once
#ifndef CAMERACOMPONENT
#define CAMERACOMPONENT
#include "Component.h"
#include <string>

namespace Ogre {
    class Camera;
    class SceneNode;
    class SceneManager;
    class Viewport;
    class ColourValue;
    class RenderWindow;
}

#pragma warning(disable : 4251)

namespace  VeryReal {
    class Vector3;
    class Vector2;
    class Entity;

    class VERYREAL_API CameraComponent : public Component {
    public:
        // Constructor por defecto de la clase CameraComponent.
        CameraComponent() {};

        // Inicializa el componente de cámara con un nombre, un color, una ventana de renderizado de Ogre,
        // un gestor de escena de Ogre y un desplazamiento de posición.
        bool InitComponent(std::string name, VeryReal::Vector3 color, VeryReal::Vector3 m_offset);
        //actualiza la posicion de la camara
        void Update(const double& dt) override;

        // Destructor de la clase CameraComponent.
        virtual ~CameraComponent();

        // Apunta la cámara hacia una posición específica.
        void lookAt(Vector3 pos);

        // Realiza una translación de la cámara según los valores de desplazamiento especificados en los ejes x, y y z.
        void translate(float x, float y, float z);

        // Realiza un giro de la cámara según el ángulo especificado en grados.
        void roll(float d);

        // Realiza un giro de la cámara en el eje de dirección (yaw) según el ángulo especificado en grados.
        void yaw(float d);

        // Realiza un giro de la cámara en el eje transversal (pitch) según el ángulo especificado en grados.
        void pitch(float d);

        // Aplica un desplazamiento de posición de la cámara.
        void Offset(VeryReal::Vector2 offset);

        // Establece la distancia del plano de recorte cercano de la cámara.
        void setNearClipDistance(float t_clip);

        // Establece la distancia del plano de recorte lejano de la cámara.
        void setFarClipDistance(float t_clip);

        // Establece el color de fondo del puerto de vista de la cámara.
        void setViewPortBackgroundColour(Ogre::ColourValue color);

        // Desactiva el puerto de vista de la cámara.
        void desactiveViewport();

        // Activa el puerto de vista de la cámara.
        void activeViewport();

        // Desactiva la cámara.
        void desactive();

        // Activa la camara.
        void active();
        //setter para el target al que seguira la camara 
        void SetTarget(VeryReal::Entity* e);
        // Obtiene el nodo de escena asociado a la cámara.
        Ogre::SceneNode* getNode();

        
    protected:
        Ogre::SceneNode* mNode=nullptr;
        Ogre::Camera* camara=nullptr;
        Ogre::Viewport* vewport=nullptr;
        Ogre::SceneManager* mgr=nullptr;
        VeryReal::Entity* ent = nullptr;
    };
}

#pragma warning(default : 4251)

#endif !CAMERACOMPONENT