#pragma warning(disable : 4251)
#include <OgreTrays.h>
#pragma warning(default : 4251)

#include "UIProgressBarComponent.h"

using namespace VeryReal;
using namespace std;

UIProgressbar::UIProgressbar() { }

bool UIProgressbar::InitComponent(double prog, std::string nameobject, Location loc, std::string nameobjective, int whith, int contentwith) {
    OgreBites::TrayLocation trayLoc = OgreBites::TrayLocation::TL_NONE;

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
    }

    progress = prog;
    ////init
    progressbar = mTrayMgr->createProgressBar(trayLoc, nameobject, nameobjective, (Ogre::Real)whith, (Ogre::Real)contentwith);
   
    //mHealthBar->setComment(" ");
    return true;
}

UIProgressbar::~UIProgressbar() { }

void UIProgressbar::Update(const double& dt) { 
    progressbar->setProgress((Ogre::Real)progress);
}

void UIProgressbar::setPercentage(int percentage) { progress = percentage; }
void UIProgressbar::showprogress() { progressbar->show(); }
void UIProgressbar::hideprogress() { progressbar->hide(); }
void UIProgressbar::getProgress() { progressbar->getProgress(); }