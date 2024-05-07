#pragma once
#include "CreatorComponent.h"
#include "exportAudioLeon.h"
namespace VeryReal {
	class  VERYREAL_AUDIOLEON  CreatorAudioSourceComponent :public CreatorComponent
	{
	public:
        CreatorAudioSourceComponent() { }
		virtual ~CreatorAudioSourceComponent() { }
		Component* CreatorSpecificComponent() override;
        std::pair<bool,std::string> SpecificInitComponent(Component* c) override;
		std::pair<bool, std::string> SpecificInitComponentByCopy(Component* c, Component* other) override;
	};
}


