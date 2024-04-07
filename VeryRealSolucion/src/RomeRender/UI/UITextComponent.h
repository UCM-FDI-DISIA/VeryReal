#pragma once
#ifndef UITEXTCOMPONENT
#define UITEXTCOMPONENT
#include "Component.h"
#include "string"
#include <Vector2.h>
namespace Ogre {


}
namespace VeryReal {

    class UITextComponent : public Component {

      public:
        //constructora de la clase UITransformComponent
        UITextComponent();
        // Destructor de la clase UITransformComponent
        virtual ~UITextComponent();

        // Inicializa el componente
        bool InitComponent();

        void Update(const double& dt) override;

      private:
       
    };

}
#endif // UITEXTCOMPONENT
