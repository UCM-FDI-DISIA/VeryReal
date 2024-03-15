#pragma once
#include "CreatorComponent.h"
namespace VeryReal
{
	class CreatorTransformComponent :public CreatorComponent {
	private:
	public:
		CreatorTransformComponent() {}
		virtual ~CreatorTransformComponent() {}
		Component* CreatorSpecificComponent() override;
	};
};

