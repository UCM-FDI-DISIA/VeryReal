#pragma once
#ifndef UIPROGRESSBARCOMPONENT
#define UIPROGRESSBARCOMPONENT
#include "Component.h"

namespace VeryReal {
    class VERYREAL_API UIProgressBarComponent : public Component {
      public:
        //constructora de la clase UIProgressBarComponent
        UIProgressBarComponent();
        // Destructor de la clase UIProgressBarComponent
        virtual ~UIProgressBarComponent();
        // Inicializa el componente
        bool InitComponent(double maximo, double progres);
        void Update(const double& dt) override;
        double getProgress();
        void setProgress(double progres);
        double getMaximun();
        void setMaximun(double maximo);
      private:
        double maxProgress = 100;
        double progress = 0;
    };
}
#endif   // !UIPROGRESSBARCOMPONENT
