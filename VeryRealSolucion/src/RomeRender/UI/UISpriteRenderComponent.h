#pragma once
#ifndef UISPRITERENDERCOMPONENT
#define UISPRITERENDERCOMPONENT
#include "Component.h"
#include <string>

namespace VeryReal {
class VERYREAL_API UiSpriteRenderer : public Component {
      public:
        //constructora de la clase UiSpriteRendererComponent
        UiSpriteRenderer();
            // Destructor de la clase UiSpriteRendererComponent
        virtual ~UiSpriteRenderer();
        // Inicializa el componente
        bool InitComponent(std::string name, std::string material, int order);
        void Update(const double& dt) override;
            void demo();

      private:      
    };
}
#endif   // !UISPRITERENDERCOMPONENT
