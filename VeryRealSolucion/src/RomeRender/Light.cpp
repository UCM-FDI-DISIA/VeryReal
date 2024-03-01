#include "Light.h"

#include <OgreLight.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>
VeryReal::Light::Light() {

}
VeryReal::Light::~Light() {

}
void VeryReal::Light::Update() {

 }
void VeryReal::Light::InitComponent() {

}


void VeryReal::Light::SetDirection(Vector3 const& v) {
	Ogre::Vector3 vec(v.GetX(), v.GetY(), v.GetZ());
	mNode->setDirection(vec);
}
void VeryReal::Light::setType(int const dir) {
	
	switch (dir)
	{
	case 0:
		light_->setType(Ogre::Light::LT_DIRECTIONAL);
		break;
	case 1: light_->setType(Ogre::Light::LT_POINT);
		break;

	case 2:
		light_->setType(Ogre::Light::LT_RECTLIGHT);
		break;
	case 3:
		light_->setType(Ogre::Light::LT_SPOTLIGHT);
		break;
	default:
		break;
	}
}

void VeryReal::Light::SetDiffuseColour(Vector3 const& color) {
	light_->setDiffuseColour(color.GetX(), color.GetY(), color.GetZ());
	
}
void VeryReal::Light::SetshadowFarDistance(float distance) {
	light_->setShadowFarClipDistance(distance);
}

void VeryReal::Light::SetSpotlightInnerAngle(float dist) {
	light_->setSpotlightInnerAngle(Ogre::Radian(dist));
}
void VeryReal::Light::SetSpotlightOuterAngle(float dist) {
	light_->setSpotlightOuterAngle(Ogre::Radian(dist));
}

void VeryReal::Light::SetSpotlightNearClipDistance(float dist) {

	light_->setSpotlightNearClipDistance(dist);
}

void VeryReal::Light::ActivateShadows(bool shdows) {
	light_->setCastShadows(shdows);
}