#pragma once
#ifndef ERRORMANAGER
#define ERRORMANAGER
#include "Manager.h"
#include <list>
#include <string>

using scene_name = std::string;

#pragma warning(disable : 4251)

namespace VeryReal {
class Scene;
class VERYREAL_GUILLEELARQUITECTO ErrorManager : public VeryReal::Manager<ErrorManager> {
        private:
    std::pair<bool, std::string> error = {true, ""};
    ErrorManager(){};

        public:
    static std::pair<bool, std::string> Init() {
        ErrorManager* a = new ErrorManager();
        if (a != nullptr) {
            instance_pointer.reset(a);
            return {true, "ErrorManager pointer sucesfully initialized"};
        }
        return {false, "ErrorManager pointer a problem while it was initializing"};
    }
    virtual ~ErrorManager();

    void Update(const double& dt);

    void canBeError(std::pair<bool, std::string> maybeError);

    inline std::pair<bool, std::string> getError() { return error; }
  
};
}

#pragma warning(default : 4251)

#endif