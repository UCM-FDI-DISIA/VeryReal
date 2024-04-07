//#pragma once
//#ifndef UIPROGRESSBARCOMPONENT
//#define UIPROGRESSBARCOMPONENT
//#include "Component.h"
//#include <string>
//
//namespace OgreBites {
//    class ProgressBar;
//    class TrayManager;
//}
//
// namespace VeryReal {
//
//     enum Location { TOPLEFT, TOP, TOPRIGHT, LEFT, CENTER, RIGHT, BOTTOMLEFT, BOTTOM, BOTTOMRIGHT, NONE };
//
//
//     class UIProgressbar : public Component {
//         public:
//         UIProgressbar();
//         // Inicializa el componente
//         bool InitComponent(double prog, std::string nameobject, Location loc, std::string nameobjective, int whith, int contentwith);
//         // Destructor de la clase UIPROGRESSBARCOMPONENT.
//         virtual ~UIProgressbar();
//         void setPercentage(int percentage);
//         void Update(const double& dt) override;
//         void showprogress();
//         void hideprogress();
//         void getProgress();
//
//         private:
//         OgreBites::TrayManager* mTrayMgr = nullptr;
//         OgreBites::ProgressBar* progressbar = nullptr;
//         double progress = 50.0;
//     };
// }
//#endif   // !UIPROGRESSBARCOMPONENT
//
//
#pragma once
#ifndef UIPROGRESSBARCOMPONENT
#define UIPROGRESSBARCOMPONENT
#include "Component.h"
#include <string>

namespace VeryReal {
class UIProgressBarComponent : public Component {
        public:
    //constructora de la clase UiSpriteRendererComponent
    UIProgressBarComponent();
    // Destructor de la clase UiSpriteRendererComponent
    virtual ~UIProgressBarComponent();
    // Inicializa el componente
    bool InitComponent();
    void Update(const double& dt) override;

        private:
};
}
#endif   // !UIPROGRESSBARCOMPONENT
