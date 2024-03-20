#pragma once
#ifndef UIPROGRESSBARCOMPONENT
#define UIPROGRESSBARCOMPONENT
#include "Component.h"
namespace OgreBites {
    class ProgressBar;
 class TrayManager;
}
namespace VeryReal {

class UIProgressbar : public Component {

        public:
    UIProgressbar();
    // Inicializa el componente
    bool InitComponent(double progres);
    // Destructor de la clase UIPROGRESSBARCOMPONENT.
    virtual ~UIProgressbar();
    void setPercentage();
   void Update(const double& dt) override;

        private:
   OgreBites::TrayManager* mTrayMgr = nullptr;  
      OgreBites::ProgressBar* progressbar;
       double progress;
};

}
#endif   // !UIPROGRESSBARCOMPONENT


