#pragma once
#ifndef UIBUTTOMCOMPONENT
#define UIBUTTOMCOMPONENT
#include "Component.h"
#include <string>

namespace VeryReal {
class UIButtomComponent : public Component {
        public:
    //constructora de la clase UiSpriteRendererComponent
    UIButtomComponent();
    // Destructor de la clase UiSpriteRendererComponent
    virtual ~UIButtomComponent();
    // Inicializa el componente
    bool InitComponent();
    void Update(const double& dt) override;

        private:
};
}
#endif   // !UIBUTTOMCOMPONENT
