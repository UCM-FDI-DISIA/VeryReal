#include "Light.h"
#include <OgreLight.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>
#include <Entity.h>
#include "RenderManager.h"
#include <TransformComponent.h>
VeryReal::Light::Light() {

}
VeryReal::Light::~Light() {

}
void VeryReal::Light::Update() {

 }
void VeryReal::Light::InitComponent(int type, VeryReal::Vector3 const& diffusecolour, float shadowfardist,float shadowdist,float ineerangle, float outerangle, float nearclipdist, bool shdws) {
	trans_ = GetEntity()->GetComponent<TransformComponent>("transform");
	light_ = VeryReal::RenderManager::Instance()->SceneManagerOgree()->createLight("LuzPrincipal");
	mNode = VeryReal::RenderManager::Instance()->CreateNode();
	
	SetDirection(trans_->GetPosition());
	setType(type);
	SetDiffuseColour(diffusecolour);
	SetshadowFarDistance(shadowdist);
	SetSpotlightInnerAngle(ineerangle);
	SetSpotlightOuterAngle(outerangle);
	SetSpotlightNearClipDistance(nearclipdist);
	ActivateShadows(shdws);
	mNode->attachObject(light_);
}


void VeryReal::Light::SetDirection(VeryReal::Vector3 const& v) {
	Ogre::Vector3 vec(v.GetX(), v.GetY(), v.GetZ());
	mNode->setDirection(vec);
}
void VeryReal::Light::setType(int const dir) {
	
	this->type_ = dir;
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

void VeryReal::Light::SetDiffuseColour(VeryReal::Vector3 const& color) {
	this->diffusecolour_ = color;
	light_->setDiffuseColour(color.GetX(), color.GetY(), color.GetZ());
	
}
void VeryReal::Light::SetshadowFarDistance(float distance) {
	this->shadowfardist_=distance;
	light_->setShadowFarClipDistance(distance);
}

void VeryReal::Light::SetSpotlightInnerAngle(float dist) {
	this->ineerangle_ = dist;
	light_->setSpotlightInnerAngle(Ogre::Radian(dist));
}
void VeryReal::Light::SetSpotlightOuterAngle(float dist) {
	this->outerangle_ = dist;
	light_->setSpotlightOuterAngle(Ogre::Radian(dist));
}

void VeryReal::Light::SetSpotlightNearClipDistance(float dist) {
	this->nearclipdist_ = dist;
	light_->setSpotlightNearClipDistance(dist);
}

void VeryReal::Light::ActivateShadows(bool shdows) {
	this->shdws_ = shdows;
	light_->setCastShadows(shdows);
}

int VeryReal::Light::getType() const {
	return type_;
}

VeryReal::Vector3 VeryReal::Light::getDiffuseColour() const {
	return diffusecolour_;
}

float VeryReal::Light::getShadowFarDistance() const {
	return shadowfardist_;
}

float VeryReal::Light::getSpotlightInnerAngle() const {
	return ineerangle_;
}

float VeryReal::Light::getSpotlightOuterAngle() const {
	return outerangle_;
}

float VeryReal::Light::getSpotlightNearClipDistance() const {
	return nearclipdist_;
}

bool VeryReal::Light::areShadowsActivated() const {
	return shdws_;
}