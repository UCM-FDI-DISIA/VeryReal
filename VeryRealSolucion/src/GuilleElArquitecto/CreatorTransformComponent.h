#pragma once
#include "CreatorComponent.h"
#include "export.h"
namespace VeryReal
{
class VERYREAL_API CreatorTransformComponent : public CreatorComponent {
	private:
	public:
		CreatorTransformComponent() {}
		virtual ~CreatorTransformComponent() {}
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
};

