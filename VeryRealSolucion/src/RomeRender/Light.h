#pragma once
#ifndef LIGHT
#define LIGHT

#include "Component.h"
#include <Vector3.h>	

#define DEBUG_TRANSFORM_ERROR "NO SE PUEDE INICIALIZAR EL COMPONENTE LIGHT DEBIDO A QUE NO TIENE EL COMPONENTE TRANSFORM\n"

namespace Ogre {
    class SceneNode;
    class SceneManager;
    class Light;
}

namespace  VeryReal {
    class TransformComponent;
    class Conversor;

    class Light:public Component {
    public:
        // Constructuora del componente Light
        Light();
        //destructpra del componente light
        ~Light();
       
        virtual void Update();
        //initcomponent de light, pone la posicion, tamaño... del modo atachado al componente a parti de su transform
        bool InitComponent(int type, VeryReal::Vector3 const& diffusecolour, float shadowfardist, float shadowdist, float ineerangle, float outerangle, float nearclipdist, bool shdws);

        // Gira el nodo del componente los grados dados en el vector
        // @param vector que indica la cantidad qie será pasada a grados  
        void SetDirection(VeryReal::Vector3 const& v);
        //Cambia el tipo de la luz 
        // @param Int 0;DIRECCIONAL 1:PUNTO 2:RECTÁNGULO LUZ  3:FOCO
        void setType(int const dir);
        //Indica el color difuso de la luz
        // @param Vector3 que Indica en color de la luz en rgb
        void SetDiffuseColour(VeryReal::Vector3 const& color);
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

        //Gets y eso

  
        /// <returns>El tipo de luz (0 para DIRECCIONAL, 1 para PUNTO, etc.).</returns>
        int getType() const;

    
        /// <returns>El color difuso de la luz como un objeto Vector3.</returns>
        VeryReal::Vector3 getDiffuseColour() const;

        
        /// <returns>La distancia hasta la que se generan sombras.</returns>
        float getShadowFarDistance() const;

        /// <returns>El ángulo interno del foco de la luz.</returns>
        float getSpotlightInnerAngle() const;

        /// <returns>El ángulo externo del foco de la luz.</returns>
        float getSpotlightOuterAngle() const;

       
        float getSpotlightNearClipDistance() const;

        
        /// <returns>true si las sombras están activadas, false si no.</returns>
        bool  areShadowsActivated() const;

    protected:
        Ogre::Light* light=nullptr;
        Ogre::SceneNode* mNode=nullptr;
        Ogre::SceneManager* mngr_=nullptr;
        TransformComponent* trans=nullptr;
        int type=0;
        Vector3 diffusecolour; //de 0 a 1
        float shadowfardist=0.25;
        float shadowdist=5;
        float ineerangle_=45;//0 a 180
        float outerangle=25;//0 a 180
        float nearclipdist=10;
        bool shdws=false;
    };
}

#endif // !LIGHT