#pragma once
#ifndef RIGIDBODYCOMPONENT
#define RIGIDBODYCOMPONENT
#define BEDUG_ERROR_TRANSFORM "NO SE HA PODIDO INICIALIZAR EL COMPONENTE RIGIDBODY DADO QUE NO CONTIENE EL COMPONENTE TRANSFORM\n"

#include <memory>
#include <Component.h>
#include "PhysicsValues.h"
#include "Vector3.h"
#include "Vector4.h"
#include "exportPedroBullet.h"

enum PBShapes;
enum PBMovementType;
class btCollisionShape;
class btRigidBody;
struct btDefaultMotionState;

#pragma warning(disable : 4251)

namespace VeryReal {
    class TransformComponent;
    class ColliderComponent;
   
    class  RigidBodyComponent : public Component {
    public:
        VERYREAL_PEDROBULLET RigidBodyComponent();

        VERYREAL_PEDROBULLET bool InitComponent(int shapeType, float mass, float friction = 0.5f, float restitution = 0.0f,
                                                int movementType = MOVEMENT_TYPE_DYNAMIC,
                           bool trigger = false, Vector3 s = {1,1,1}, int mask = -1, int group = 1);

         VERYREAL_PEDROBULLET virtual ~RigidBodyComponent();

        // Funciones para manipular el cuerpo rígido
        VERYREAL_PEDROBULLET void SetVelocityLinear(const Vector3& velocity);
        VERYREAL_PEDROBULLET void SetVelocityAngular(const Vector3& velocity);
        VERYREAL_PEDROBULLET Vector3 GetVelocity() const;

        VERYREAL_PEDROBULLET void SetRotation(const Vector4& rotation);
        VERYREAL_PEDROBULLET void Rotate(const Vector3& axis, int degree);
        VERYREAL_PEDROBULLET Vector4 GetRotation();

        VERYREAL_PEDROBULLET void AddImpulse(const Vector3& impulse);
        VERYREAL_PEDROBULLET void AddTorque(const Vector3& torque);

        VERYREAL_PEDROBULLET void SetActiveTrigger(bool b);
        VERYREAL_PEDROBULLET bool GetActiveTrigger();

         VERYREAL_PEDROBULLET void SetMass(float n);
        VERYREAL_PEDROBULLET float GetMass();

         VERYREAL_PEDROBULLET void SetFriction(float n);
         VERYREAL_PEDROBULLET float GetFriction();

        VERYREAL_PEDROBULLET void SetRestitution(float n);
        VERYREAL_PEDROBULLET float GetRestitution();

        void SetMovementType(PBMovementType mT);

        // Obtiene el btRigidBody 
        btRigidBody* GetBulletRigidBody();

        btCollisionShape* GetCollisionShape();

        // Getter y Setter de mascara de colision
        VERYREAL_PEDROBULLET void setMask(const int n);
        VERYREAL_PEDROBULLET int getMask() const;

        // Getter y Setter de grupo de colision
        VERYREAL_PEDROBULLET void setGroup(const int n);
        VERYREAL_PEDROBULLET int getGroup() const;

        VERYREAL_PEDROBULLET void Update(const double& dt);

        VERYREAL_PEDROBULLET void Decelerate(float percent);

    private:
        TransformComponent* transformComponent;
        btCollisionShape* collisionShape;
        std::unique_ptr<btDefaultMotionState> motionState;
        btRigidBody* rigidBody;

        //grupos y mascaras de colision
        int mask;
        int group;

        bool isTrigger;
        float mass;
        float friction;
        float restitution;
        PBMovementType movementType;
        ColliderComponent* collider = nullptr;
        bool InitializeRigidBody(PBShapes shapeType, PBMovementType movementType, bool trigger, Vector3 s, int mask, int group);
        btCollisionShape* CreateCollisionShape(PBShapes shapeType, Vector3 s);
    };
} 

#pragma warning(default : 4251)

#endif 
