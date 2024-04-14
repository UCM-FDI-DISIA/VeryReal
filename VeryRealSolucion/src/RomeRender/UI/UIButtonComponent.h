#pragma once
#ifndef UIBUTTOMCOMPONENT
#define UIBUTTOMCOMPONENT
#include "Component.h"
#include <string>

namespace VeryReal {
class UITransformComponent;
    class VERYREAL_API UIButtomComponent : public Component {
     public:
        //constructora de la clase UIButtomComponent
        UIButtomComponent();
        // Destructor de la clase UIButtomComponent
        virtual ~UIButtomComponent();
        virtual void accion(){};
        // Inicializa el componente
        bool InitComponent();
        void Update(const double& dt) override;

     private:
         //metodo que llama cuando se haga click en el boton
        void OnButtonClick();
        void mousePosition();
        //metodo que combrueba su el raton esta dentro del boton y tambien si esta haciendo click
        bool isclicked = false;
        bool overbuttom = false;
        UITransformComponent* UItransofrm;
    };
}
#endif   // !UIBUTTOMCOMPONENT
