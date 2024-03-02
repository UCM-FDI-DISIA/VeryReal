#pragma once
#ifndef LIGHT
#define LIGHT
#endif // !LIGHT

#include "Component.h"
#include "Vector3.h"
 
namespace Ogre
{
    class SceneNode;
    class SceneManager;
    class Light;
}

namespace  VeryReal {
    class Light {
    public:
        // Constructuora del componente Light
        Light();
        //destructpra del componente light
        ~Light();
       
        virtual void Update();
        //initcomponent de light, pone la posicion, tamaño... del modo atachado al componente a parti de su transform
        void InitComponent();

        // Gira el nodo del componente los grados dados en el vector
        // @param vector que indica la cantidad qie será pasada a grados  
        void SetDirection(Vector3 const& v);
        //Cambia el tipo de la luz 
        // @param Int 0;DIRECCIONAL 1:PUNTO 2:RECTÁNGULO LUZ  3:FOCO
        void setType(int const dir);
        //Indica el color difuso de la luz
        // @param Vector3 que Indica en color de la luz en rgb
        void SetDiffuseColour(Vector3 const& color);
        // Distancia hasta la que se generan sombras
        //  @param float 
        void SetshadowFarDistance(float distance);
        // Establece el ángulo interno del foco de la luz.
        // @param dist El ángulo interno del foco.
        void SetSpotlightInnerAngle(float dist);

        // Establece el ángulo externo del foco de la luz.
        // @param dist El ángulo externo del foco.
        void SetSpotlightOuterAngle(float dist);


        // Establece la distancia de recorte cercano del foco de la luz.
        // @param dist La distancia de recorte cercano del foco.
        void SetSpotlightNearClipDistance(float dist);

        // Actica o desactiva la generación de sombras
        // @param bool shdows que indica si se generan sombras o no.
        void ActivateShadows(bool shdows);
    protected:
        Ogre::Light* light_;
        Ogre::SceneNode* mNode;
        Ogre::SceneManager* mngr_;
    };


}

