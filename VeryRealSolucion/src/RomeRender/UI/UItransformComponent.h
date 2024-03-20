#pragma once
#ifndef UITRANSFORMCOMPONENT
#define UITRANSFORMCOMPONENT
#include "Component.h"
#include "string"
#include <Vector2.h>
namespace Ogre {

   
}
namespace VeryReal {
   
    class UITransformComponent : public Component {

      public:
  
        UITransformComponent();
        // Inicializa el componente 
        bool InitComponent();
        // Destructor de la clase UITransformComponent.
        virtual ~UITransformComponent();
    
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

