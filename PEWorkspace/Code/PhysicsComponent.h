#ifndef PHYSICS_COMPONENT
#define PHYSICS_COMPONENT


#include "PrimeEngine/Math/Vector3.h"

#include "PrimeEngine/Scene/Mesh.h"
#include "PrimeEngine/Scene/MeshInstance.h"
//namespace PE {
//	namespace Components {

		class PhysicsComponent {
		public:

			// The Physics component should store the points of the object's bounding box in local space, and
			// the world matrix or a way to access it
			// He said it's easier to hard code, but I feel like I should assign this to every mesh instance / scene node
			// The question is, where are mesh instance / scene nodes created?

			PhysicsComponent(PE::Components::Mesh* inputM, PE::Components::MeshInstance* inputMI);

			Vector3* returnPoints();

			bool checkCollision(Vector3& planeVec1, Vector3& planeVec2);

			Vector3 vecCollision(Vector3& planeVec1, Vector3& planeVec2);

			unsigned int label;
			PE::Components::Mesh* m;
			PE::Components::MeshInstance* mi;
			Vector3 points[8];
			Vector3 center;
		};

//	}
//}

#endif