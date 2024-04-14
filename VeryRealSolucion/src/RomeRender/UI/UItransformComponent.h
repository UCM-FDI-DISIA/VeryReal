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
        bool InitComponent(VeryReal::Vector2 pos, VeryReal::Vector2 scale, bool hide = false, bool interact = false);
       
    
        void Update(const double& dt) override;
        void showElement();        
        void hideElement();        
        //no hay rotacion, se concluyo que mejor sin ella
        VeryReal::Vector2 getPosition();
        void setPosition(VeryReal::Vector2 pos);
        VeryReal::Vector2 getSize();
        void setSize(VeryReal::Vector2 size);

        void setInteractive(bool isInteractive);

        bool isHidden();
      private:

        VeryReal::Vector2 position;
        VeryReal::Vector2 size;
        bool hidden;
        bool interactive;
    };

}
#endif   // !UITRANSFORMCOMPONENT

