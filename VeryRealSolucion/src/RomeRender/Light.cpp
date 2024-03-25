#include "Light.h"
#include <OgreLight.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>
#include <Entity.h>
#include "RenderManager.h"
#include <TransformComponent.h>
#include "conversorvectores.h"


using namespace VeryReal;

Light::Light():light(nullptr),shadowdist(10),ineerangle_(45),outerangle(90),shadowfardist(10),diffusecolour(Vector3(0,0,0)),nearclipdist(0.5),shdws(true) {

}
Light::~Light() {

}
bool Light::InitComponent(int type, Vector3 const& diffusecolour, float shadowfardist,float shadowdist,float ineerangle, float outerangle, float nearclipdist, bool shdws) {
	if(GetEntity()->HasComponent("transform"))trans = GetEntity()->GetComponent<TransformComponent>("transform");
	else {
		#ifdef DEBUG_MODE
		std::cerr << DEBUG_TRANSFORM_ERROR;
		#endif
		 return false;//devolverá false en este caso
	
	}
	light = VeryReal::RenderManager::Instance()->SceneManagerOgree()->createLight("LuzPrincipal");
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
	return true;
}

void Light::Update() {

    mNode->setPosition(VR2OgreV3(trans->GetPosition()));
}
void Light::SetDirection(Vector3 const& v) {
        mNode->setDirection(VR2OgreV3(v));
}
void Light::setType(int const dir) {
	
	this->type = dir;
	switch (dir)
	{
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

void Light::SetDiffuseColour(Vector3 const& color) {
	this->diffusecolour = color;
	light->setDiffuseColour(color.GetX(), color.GetY(), color.GetZ());
	
}
void Light::SetshadowFarDistance(float distance) {
	this->shadowfardist=distance;
	light->setShadowFarClipDistance(distance);
}

void Light::SetSpotlightInnerAngle(float dist) {
	this->ineerangle_ = dist;
	light->setSpotlightInnerAngle(Ogre::Radian(dist));
}
void Light::SetSpotlightOuterAngle(float dist) {
	this->outerangle = dist;
	light->setSpotlightOuterAngle(Ogre::Radian(dist));
}

void Light::SetSpotlightNearClipDistance(float dist) {
	this->nearclipdist = dist;
	light->setSpotlightNearClipDistance(dist);
}

void Light::ActivateShadows(bool shdows) {
	this->shdws = shdows;
	light->setCastShadows(shdows);
}

int Light::getType() const {
	return type;
}

Vector3 Light::getDiffuseColour() const {
	return diffusecolour;
}

float Light::getShadowFarDistance() const {
	return shadowfardist;
}

float Light::getSpotlightInnerAngle() const {
	return ineerangle_;
}

float Light::getSpotlightOuterAngle() const {
	return outerangle;
}

float Light::getSpotlightNearClipDistance() const {
	return nearclipdist;
}

bool Light::areShadowsActivated() const {
	return shdws;
}