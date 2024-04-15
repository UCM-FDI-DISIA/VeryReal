#pragma once
#ifndef UITRANSFORMCOMPONENT
#define UITRANSFORMCOMPONENT
#include "Component.h"
#include "Vector2.h"
#include "string"

namespace VeryReal {


    class VERYREAL_API UITransformComponent : public Component {

      public:
        //constructora de la clase UITransformComponent
        UITransformComponent();
        // Destructor de la clase UITransformComponent
        virtual ~UITransformComponent();

        // Inicializa el componente 
        bool InitComponent(VeryReal::Vector2 pos, VeryReal::Vector2 sc, bool hide = false, bool interact = false);
       
    
        void Update(const double& dt) override;
        void showElement();        
        void hideElement();        
        //no hay rotacion, se concluyo que mejor sin ella

        VeryReal::Vector2 getPosition();
        void setPosition(VeryReal::Vector2 pos);

        //Getter del multiplicador de las dimensiones del Overlay Element en concreto. Tiene uso para sprite y texto.
        VeryReal::Vector2 getScale();
        //Setter del multiplicador de las dimensiones del Overlay Element en concreto. Tiene uso para sprite y texto.
        void setScale(VeryReal::Vector2 sc);

        void setInteractive(bool isInteractive);

        bool isHidden();
      private:

        VeryReal::Vector2 position;
        //Multiplicador de las dimensiones del Overlay Element en concreto.
        VeryReal::Vector2 scale;
        
        bool hidden;
        bool interactive;
    };

}
#endif   // !UITRANSFORMCOMPONENT

