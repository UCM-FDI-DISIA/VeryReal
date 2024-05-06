#pragma once
#ifndef CAMERACOMPONENT
#define CAMERACOMPONENT
#include "Component.h"
#include <string>
#include "exportRomeRender.h"
#include "Vector3.h"

namespace Ogre {
class Camera;
class SceneNode;
class SceneManager;
class Viewport;
class ColourValue;
class RenderWindow;
class MovableObject;
}

#pragma warning(disable : 4251)

namespace VeryReal {
class Vector4;
class Vector3;
class Vector2;
class Entity;

class CameraComponent : public Component {
        public:
    // Constructor por defecto de la clase CameraComponent.
    VERYREAL_ROMERENDER CameraComponent(){};

    // Inicializa el componente de c�mara con un nombre, un color, una ventana de renderizado de Ogre,
    // un gestor de escena de Ogre y un desplazamiento de posici�n.
    VERYREAL_ROMERENDER bool InitComponent(std::string name, VeryReal::Vector3 color, float alfa, VeryReal::Vector3 m_offset, int zOrder,VeryReal::Vector3 position);
    //actualiza la posicion de la camara
    VERYREAL_ROMERENDER void Update(const double& dt) override;

    // Destructor de la clase CameraComponent.
    VERYREAL_ROMERENDER virtual ~CameraComponent();

    // Apunta la c�mara hacia una posici�n espec�fica.
    VERYREAL_ROMERENDER void lookAt(Vector3 pos);

    // Realiza una translaci�n de la c�mara seg�n los valores de desplazamiento especificados en los ejes x, y y z.
    VERYREAL_ROMERENDER void translate(float x, float y, float z);

    // Realiza un giro de la c�mara seg�n el �ngulo especificado en grados.
    VERYREAL_ROMERENDER void roll(float d);

    // Realiza un giro de la c�mara en el eje de direcci�n (yaw) seg�n el �ngulo especificado en grados.
    VERYREAL_ROMERENDER void yaw(float d);

    // Realiza un giro de la c�mara en el eje transversal (pitch) seg�n el �ngulo especificado en grados.
    VERYREAL_ROMERENDER void pitch(float d);

    VERYREAL_ROMERENDER void rotate(float d, VeryReal::Vector3 v);

    // Aplica un desplazamiento de posici�n de la c�mara.
    VERYREAL_ROMERENDER void Offset(VeryReal::Vector2 offset);

    // Establece la distancia del plano de recorte cercano de la c�mara.
    VERYREAL_ROMERENDER void setNearClipDistance(float t_clip);

    // Establece la distancia del plano de recorte lejano de la c�mara.
    VERYREAL_ROMERENDER void setFarClipDistance(float t_clip);

    // Establece el color de fondo del puerto de vista de la c�mara.
    void setViewPortBackgroundColour(Ogre::ColourValue color);

    // Desactiva el puerto de vista de la c�mara.
    VERYREAL_ROMERENDER void desactiveViewport();

    // Activa el puerto de vista de la c�mara.
    VERYREAL_ROMERENDER void activeViewport();

    // Desactiva la c�mara.
    VERYREAL_ROMERENDER void desactive();

    // Activa la camara.
    VERYREAL_ROMERENDER void active();
    //setter para el target al que seguira la camara
    VERYREAL_ROMERENDER void SetTarget(VeryReal::Entity* e);
    // Obtiene el nodo de escena asociado a la c�mara.
    Ogre::SceneNode* getNode();

    // Funci�n para convertir un punto de pantalla a un punto del mundo.
    VERYREAL_ROMERENDER VeryReal::Vector3 ScreenToWorldPoint(const VeryReal::Vector2& screenPoint);


        protected:
    Ogre::SceneNode* mNode = nullptr;
    Ogre::Camera* camara = nullptr;
    Ogre::Viewport* vewport = nullptr;
    Ogre::SceneManager* mgr = nullptr;
    VeryReal::Entity* ent = nullptr;
    VeryReal::Vector3 offset;
};
}

#pragma warning(default : 4251)

#endif !CAMERACOMPONENT