
#ifdef _DEBUG

#ifndef PHYSICSDEBUG
#define PHYSICSDEBUG
#include <vector>
#include <btBulletCollisionCommon.h>
#include <Ogre.h>
/// <summary>
/// Struct para guardar los puntos de cintacto entre bodies
/// </summary>


struct ContactPoint {
    Ogre::Vector3 from;
    Ogre::Vector3 to;
    Ogre::ColourValue color;
    size_t dieTime;
};
namespace VeryReal {

class DebugMode : public btIDebugDraw, public Ogre::FrameListener {
        private:
    DebugDrawModes mDebugModes;
    Ogre::SceneNode* node;
    std::list<Ogre::ManualObject*> lines;
    Ogre::MaterialPtr mtl;


        protected:
 
        public:
    VERYREAL_PEDROBULLET DebugMode();
    VERYREAL_PEDROBULLET ~DebugMode();
    /// <summary>
    /// Método para dibujar las lineas de los cuerpos fisicos
    /// </summary>
    virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
   
    /// <summary>
    /// Método para representar los puntos de choque de dos cuerpos fisicos
    /// </summary>
    virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
    VERYREAL_PEDROBULLET virtual void reportErrorWarning(const char* warningString);
    virtual void draw3dText(const btVector3& location, const char* textString);
    VERYREAL_PEDROBULLET virtual void setDebugMode(int debugMode);
    VERYREAL_PEDROBULLET virtual int getDebugMode() const;
    VERYREAL_PEDROBULLET void clearLines() override;
};
}
#endif   // DebugDrawer_h__

#endif //Debug