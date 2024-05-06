#pragma once
#pragma warning(disable : 4251)
#include <OgreLight.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#pragma warning(default : 4251)

#include <Entity.h>
#include "RenderManager.h"
#include <TransformComponent.h>
#include "LightComponent.h"
#include "conversorvectores.h"

using namespace VeryReal;

LightComponent::LightComponent(): light(nullptr), shadowdist(10), ineerangle_(45), outerangle(90), shadowfardist(10), diffusecolour(Vector3(0, 0, 0)), nearclipdist(0.5),
      shdws(true) {

}

LightComponent::~LightComponent() {

}

bool LightComponent::InitComponent(int type, Vector3 const& diffusecolour, float shadowfardist, float shadowdist, float ineerangle, float outerangle,
                                   float nearclipdist, bool shdws, float intensity) {
	if(GetEntity()->HasComponent("TransformComponent"))trans = GetEntity()->GetComponent<TransformComponent>();
	else {
		#ifdef DEBUG_MODE
		std::cerr << DEBUG_TRANSFORM_ERROR;
		#endif
		 return false;//devolverá false en este caso
	
	}
	light = VeryReal::RenderManager::Instance()->SceneManagerOgree()->createLight();
	mNode = VeryReal::RenderManager::Instance()->CreateNode();
	
	SetDirection(trans->GetPosition());
	setType(type);
	SetDiffuseColour(diffusecolour);
	SetshadowFarDistance(shadowdist);
	SetSpotlightInnerAngle(ineerangle);
	SetSpotlightOuterAngle(outerangle);
	SetSpotlightNearClipDistance(nearclipdist);
	ActivateShadows(shdws);
	mNode->attachObject(light);
    light->setPowerScale(Ogre::Real(intensity));
	return true;
}

void LightComponent::Update(const double& dt) {
    mNode->setPosition(VR2OgreV3(trans->GetPosition()));
}

void LightComponent::SetDirection(Vector3 const& v) {
        mNode->setDirection(VR2OgreV3(v));
}

void LightComponent::setType(int const dir) {
	this->type = dir;
	switch (dir) {
	case 0:
		light->setType(Ogre::Light::LT_DIRECTIONAL);
		break;
	case 1: light->setType(Ogre::Light::LT_POINT);
		break;
	case 2:
		light->setType(Ogre::Light::LT_RECTLIGHT);
		break;
	case 3:
		light->setType(Ogre::Light::LT_SPOTLIGHT);
		break;
	default:
		break;
	}
}

void LightComponent::SetDiffuseColour(Vector3 const& color) {
	this->diffusecolour = color;
	light->setDiffuseColour(color.GetX(), color.GetY(), color.GetZ());
	
}

void LightComponent::SetshadowFarDistance(float distance) {
	this->shadowfardist=distance;
	light->setShadowFarClipDistance(distance);
}

void LightComponent::SetSpotlightInnerAngle(float dist) {
	this->ineerangle_ = dist;
	light->setSpotlightInnerAngle(Ogre::Radian(dist));
}

void LightComponent::SetSpotlightOuterAngle(float dist) {
	this->outerangle = dist;
	light->setSpotlightOuterAngle(Ogre::Radian(dist));
}

void LightComponent::SetSpotlightNearClipDistance(float dist) {
	this->nearclipdist = dist;
	light->setSpotlightNearClipDistance(dist);
}

void LightComponent::ActivateShadows(bool shdows) {
	this->shdws = shdows;
	light->setCastShadows(shdows);
}

int LightComponent::getType() const {
	return type;
}

Vector3 LightComponent::getDiffuseColour() const {
	return diffusecolour;
}

float LightComponent::getShadowFarDistance() const {
	return shadowfardist;
}

float LightComponent::getSpotlightInnerAngle() const {
	return ineerangle_;
}

float LightComponent::getSpotlightOuterAngle() const {
	return outerangle;
}

float LightComponent::getSpotlightNearClipDistance() const {
	return nearclipdist;
}

bool LightComponent::areShadowsActivated() const {
	return shdws;
}

void LightComponent::setVisible(bool visibility) { 
	mNode->setVisible(visibility); 
}