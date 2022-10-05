#ifndef PHYSICS_COMPONENT
#define PHYSICS_COMPONENT


#include "PrimeEngine/Math/Vector3.h"

#include "PrimeEngine/Scene/Mesh.h"
#include "PrimeEngine/Scene/MeshInstance.h"
#include "Plane.h"
#include <string>
//namespace PE {
//	namespace Components {

		class PhysicsComponent {
		public:

			// The Physics component should store the points of the object's bounding box in local space, and
			// the world matrix or a way to access it
			// He said it's easier to hard code, but I feel like I should assign this to every mesh instance / scene node
			// The question is, where are mesh instance / scene nodes created?

			PhysicsComponent(Matrix4x4* in_base, Matrix4x4* in_worldTransform, PE::Components::Mesh* inputM, PE::Components::MeshInstance* inputMI, std::string type);

			~PhysicsComponent();

			Plane* returnPlanes();

			bool checkCollision(Vector3& planeVec1, Vector3& planeVec2);

			Vector3 vecCollision(Vector3& planeVec1, Vector3& planeVec2);

			Plane* maxPoints(PE::Components::Mesh* m);

			Vector3 getCenter();


			unsigned int label;
			PE::Components::Mesh* mesh;
			PE::Components::MeshInstance* meshInstance;
			Matrix4x4* m_base;
			Matrix4x4* m_worldTransform;
			Plane* box;
			Vector3 center;
			PrimitiveTypes::Float32 radius;
			std::string type;
		};

//	}
//}

#endif