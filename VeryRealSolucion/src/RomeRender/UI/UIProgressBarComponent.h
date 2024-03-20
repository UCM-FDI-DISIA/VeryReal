#pragma once
#ifndef UIPROGRESSBARCOMPONENT
#define UIPROGRESSBARCOMPONENT
#include "Component.h"
#include "string"
namespace OgreBites {
    class ProgressBar;
 class TrayManager;
}
namespace VeryReal {

     enum Location   
     {
        TOPLEFT,
        TOP,
        TOPRIGHT,
        LEFT,
        CENTER,
        RIGHT,
        BOTTOMLEFT,
        BOTTOM,
        BOTTOMRIGHT,
        NONE
     };



class UIProgressbar : public Component {

   public:
    UIProgressbar();
    // Inicializa el componente
    bool InitComponent(double prog, string nameobject, Location loc, string nameobjective, int whith, int contentwith);
    // Destructor de la clase UIPROGRESSBARCOMPONENT.
    virtual ~UIProgressbar();
    void setPercentage(int percentage);
    void Update(const double& dt) override;
    void showprogress();
    void hideprogress();
    void getProgress();
  private:
    OgreBites::TrayManager* mTrayMgr = nullptr;  
    OgreBites::ProgressBar* progressbar;
    double progress;
};

}
#endif   // !UIPROGRESSBARCOMPONENT


