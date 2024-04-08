#pragma once
#include "CreatorComponent.h"
namespace VeryReal {
	class VERYREAL_API CreatorAudioSourceComponent :public CreatorComponent
	{
	public:
        CreatorAudioSourceComponent() { }
		virtual ~CreatorAudioSourceComponent() { }
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
}


