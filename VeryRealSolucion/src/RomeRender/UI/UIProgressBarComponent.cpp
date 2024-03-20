
#include "UIProgressBarComponent.h"

#include <OgreTrays.h>
using namespace VeryReal;
using namespace std;

UIProgressbar::UIProgressbar() { }
bool UIProgressbar::InitComponent(double prog, string nameobject, Location loc, string nameobjective, int whith, int contentwith) {
           OgreBites::TrayLocation trayLoc;

            switch (loc) {
            case TOPLEFT : trayLoc = OgreBites::TrayLocation::TL_TOPLEFT; break;
            case TOP : trayLoc = OgreBites::TrayLocation::TL_TOP; break;
            case TOPRIGHT : trayLoc = OgreBites::TrayLocation::TL_TOPRIGHT; break;
            case LEFT : trayLoc = OgreBites::TrayLocation::TL_LEFT; break;
            case CENTER : trayLoc = OgreBites::TrayLocation::TL_CENTER; break;
            case RIGHT : trayLoc = OgreBites::TrayLocation::TL_RIGHT; break;
            case BOTTOMLEFT : trayLoc = OgreBites::TrayLocation::TL_BOTTOMLEFT; break;
            case BOTTOM : trayLoc = OgreBites::TrayLocation::TL_BOTTOM; break;
            case BOTTOMRIGHT : trayLoc = OgreBites::TrayLocation::TL_BOTTOMRIGHT; break;
            case NONE : trayLoc = OgreBites::TrayLocation::TL_NONE; break;
            }
    progress = prog;
    ////init
    progressbar = mTrayMgr->createProgressBar(trayLoc, nameobject, nameobjective, whith, contentwith);
   
    //mHealthBar->setComment(" ");
    return true;
}
UIProgressbar::~UIProgressbar() { }
void UIProgressbar::Update(const double& dt) { 

    progressbar->setProgress(progress);
   
}

void UIProgressbar::setPercentage(int percentage) { progress = percentage; }
void UIProgressbar::showprogress() { progressbar->show(); }
void UIProgressbar::hideprogress() { progressbar->hide(); }
void UIProgressbar::getProgress() { progressbar->getProgress(); }