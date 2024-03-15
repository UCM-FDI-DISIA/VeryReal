#include "Light.h"
#include <OgreLight.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>
#include <Entity.h>
#include "RenderManager.h"
#include <TransformComponent.h>
#include "conversorvectores.h"
#include "VariantClass.h"

using namespace VeryReal;

VeryReal::Light::Light():light(nullptr),shadowdist(10),ineerangle_(45),outerangle(90),shadowfardist(10),diffusecolour(Vector3(0,0,0)),nearclipdist(0.5),shdws(true) {

}
VeryReal::Light::~Light() {

}
void VeryReal::Light::InitComponent(int type, VeryReal::Vector3 const& diffusecolour, float shadowfardist,float shadowdist,float ineerangle, float outerangle, float nearclipdist, bool shdws) {
	if(GetEntity()->HasComponent("transform"))trans = GetEntity()->GetComponent<TransformComponent>("transform");
	else std::cerr << "NO SE PUEDE INICIALIZAR EL COMPONENTE LIGHT DEBIDO A QUE NO TIENE EL COMPONENTE TRANSFORM\n";
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
}

void VeryReal::Light::Update() {
	Ogre::Vector3 v(trans->GetPosition().GetX(), trans->GetPosition().GetY(), trans->GetPosition().GetZ());
	mNode->setPosition(v);
}
void VeryReal::Light::SetDirection(VeryReal::Vector3 const& v) {
	Ogre::Vector3 vec(v.GetX(), v.GetY(), v.GetZ());
	mNode->setDirection(vec);
}
void VeryReal::Light::setType(int const dir) {
	
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

void VeryReal::Light::SetDiffuseColour(VeryReal::Vector3 const& color) {
	this->diffusecolour = color;
	light->setDiffuseColour(color.GetX(), color.GetY(), color.GetZ());
	
}
void VeryReal::Light::SetshadowFarDistance(float distance) {
	this->shadowfardist=distance;
	light->setShadowFarClipDistance(distance);
}

void VeryReal::Light::SetSpotlightInnerAngle(float dist) {
	this->ineerangle_ = dist;
	light->setSpotlightInnerAngle(Ogre::Radian(dist));
}
void VeryReal::Light::SetSpotlightOuterAngle(float dist) {
	this->outerangle = dist;
	light->setSpotlightOuterAngle(Ogre::Radian(dist));
}

void VeryReal::Light::SetSpotlightNearClipDistance(float dist) {
	this->nearclipdist = dist;
	light->setSpotlightNearClipDistance(dist);
}

void VeryReal::Light::ActivateShadows(bool shdows) {
	this->shdws = shdows;
	light->setCastShadows(shdows);
}

int VeryReal::Light::getType() const {
	return type;
}

VeryReal::Vector3 VeryReal::Light::getDiffuseColour() const {
	return diffusecolour;
}

float VeryReal::Light::getShadowFarDistance() const {
	return shadowfardist;
}

float VeryReal::Light::getSpotlightInnerAngle() const {
	return ineerangle_;
}

float VeryReal::Light::getSpotlightOuterAngle() const {
	return outerangle;
}

float VeryReal::Light::getSpotlightNearClipDistance() const {
	return nearclipdist;
}

bool VeryReal::Light::areShadowsActivated() const {
	return shdws;
}