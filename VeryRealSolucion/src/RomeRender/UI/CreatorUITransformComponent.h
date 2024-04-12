#pragma once
#include "CreatorComponent.h"
namespace VeryReal
{
class VERYREAL_API CreatorUITransformComponent : public CreatorComponent
	{
	public:
    CreatorUITransformComponent() { }
    virtual ~CreatorUITransformComponent() { }
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
};

