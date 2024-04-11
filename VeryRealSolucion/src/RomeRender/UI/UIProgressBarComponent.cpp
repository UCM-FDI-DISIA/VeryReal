#include "UIProgressBarComponent.h"
using namespace VeryReal;

    //constructora de la clase UIProgressBarComponent
    UIProgressBarComponent::UIProgressBarComponent() {

    }
    // Destructor de la clase UIProgressBarComponent
    UIProgressBarComponent::~UIProgressBarComponent() {

    }
    // Inicializa el componente
    bool UIProgressBarComponent::InitComponent(double maximo, double progres) { 
        maxProgress = maximo;
        progress = progres;
        return true;
    }
    void UIProgressBarComponent::Update(const double& dt) {

    }
    double UIProgressBarComponent::getProgress() { 
        return progress;
    }
    void UIProgressBarComponent::setProgress(double progres) {

        progress = progres;
    }
    double UIProgressBarComponent::getMaximun() { 
        return maxProgress;
    }
    void UIProgressBarComponent::setMaximun(double maximo) {
        maxProgress = maximo;
    }

  
