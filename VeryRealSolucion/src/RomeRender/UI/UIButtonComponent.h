#pragma once
#ifndef UIBUTTONCOMPONENT
#define UIBUTTONCOMPONENT
#include "Component.h"
#include <string>
#include "../exportRomeRender.h"

namespace VeryReal {
class UITransformComponent;
    class VERYREAL_ROMERENDER UIButtonComponent : public Component {
     public:
        //constructora de la clase UIButtomComponent
        UIButtonComponent();
        // Destructor de la clase UIButtomComponent
        virtual ~UIButtonComponent();
        virtual void Action(){};
        // Inicializa el componente
        std::pair<bool, std::string> InitComponent();
        void Update(const double& dt) override;

     private:
         //metodo que llama cuando se haga click en el boton
        void OnButtonClick();
        void mousePosition();
        //metodo que combrueba su el raton esta dentro del boton y tambien si esta haciendo click
        bool isclicked = false;
        bool overbuttom = false;
        UITransformComponent* UItransform = nullptr;
    };
}
#endif   // !UIBUTTONCOMPONENT
