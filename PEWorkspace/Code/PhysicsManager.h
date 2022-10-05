#ifndef PHYSICS_MANAGER
#define PHYSICS_MANAGER

#include <vector>
#include "PhysicsComponent.h"
#include "PrimeEngine/Math/Vector3.h"
//#include "PrimeEngine/Scene/SceneNode.h"


//namespace PE {
//	namespace Components {

		class PhysicsManager {
		public:
			PhysicsManager();

			static bool collCheck(PhysicsComponent* phys);

			static void addComponent(PhysicsComponent* p);
			static bool projectPoint(Vector3* center, PrimitiveTypes::Float32 radius, Plane* plane);

			static Vector3 collAdjust(PhysicsComponent);
			static bool pointColl(Vector3* point, Plane* plane);
			static bool pointColl(Vector3 point, Plane* plane);
			static bool spBoxCheck(PhysicsComponent* sphere, PhysicsComponent* box);
			static bool fullCheck(PhysicsComponent* phys);


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