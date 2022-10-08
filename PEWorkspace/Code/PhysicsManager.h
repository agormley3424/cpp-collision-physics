#ifndef PHYSICS_MANAGER
#define PHYSICS_MANAGER

#include <vector>
#include "PhysicsComponent.h"
#include "PrimeEngine/Math/Vector3.h"
#include "PrimeEngine/Scene/SceneNode.h"
//#include "PrimeEngine/Scene/SceneNode.h"


//namespace PE {
//	namespace Components {

		class PhysicsManager {
		public:
			PhysicsManager();

			static bool collCheck(PhysicsComponent* phys);

			static void addComponent(PhysicsComponent* p);
			static bool projectPoint(Vector3 center, PrimitiveTypes::Float32 radius, Plane plane, Matrix4x4* m_base);

			static Vector3 collAdjust(PhysicsComponent);
			static bool pointColl(Vector3 point, Plane plane, Matrix4x4* m_base);
			static bool spBoxCheck(PhysicsComponent* sphere, PhysicsComponent* box, Matrix4x4* m_base);
			static std::vector<PhysicsComponent*> PhysicsManager::fullCheck(PhysicsComponent* phys);

			static Vector3 nearestPlane(Plane* planeArr, Vector3 forwardVec, Vector3 point);

			static void checkAndMove(Matrix4x4* m_base, PhysicsComponent* p, Vector3 curPos, Vector3 dir, float dist);


			//static vector<PhysicsComponent*> objectArr(100, NULL);
			//static std::vector<int> objectArr;
			//std::vector<void*> objectArr(100, nullptr);
			//static PhysicsComponent* objectArr[100];
			//static int arrSize = 0;
			//objectArr[0] = nullptr;
			//PhysicsComponent* object(100, void*);

			static std::vector<PhysicsComponent*> objectArr;

		};

//	}
//}


		//std::vector<PhysicsComponent*> objectArr = {};
#endif