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
        void SpecificInitComponent(Component* c) override;
	};
}


