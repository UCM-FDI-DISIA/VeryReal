#include "ErrorManager.h"
#include "Scene.h"
using namespace std;

VeryReal::ErrorManager::~ErrorManager(){}


void VeryReal::ErrorManager::Update(const double& dt) {}

void VeryReal::ErrorManager::canBeError(std::pair<bool, std::string> maybeError) 
{
    if (!maybeError.first) this->error = maybeError;

}