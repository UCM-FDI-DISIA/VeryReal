
#include "UIProgressBarComponent.h"

#include <OgreTrays.h>
using namespace VeryReal;
using namespace std;

UIProgressbar::UIProgressbar() { }
bool UIProgressbar::InitComponent(double prog) {

    progress = prog;
    ////init
     progressbar = mTrayMgr->createProgressBar(OgreBites::TrayLocation::TL_BOTTOMLEFT, "HealthBar", "Health", 100, 50);
    //mHealthBar->setComment(" ");
    //
    //mHealthBar->setProgress(1);
}
UIProgressbar::~UIProgressbar() { }
void UIProgressbar::Update(const double& dt) { 
    ////update
    //mHealthBar->setProgress(progress);
    //progress = progress - 0.1;
    //if (progress <= 0) progress == 1;
    //
    //
}

    
