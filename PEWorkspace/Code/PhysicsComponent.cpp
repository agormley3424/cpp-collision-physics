#include "PhysicsComponent.h"
#include "PrimeEngine/Math/Vector3.h"

#include "PrimeEngine/Scene/Mesh.h"
#include "PrimeEngine/Scene/MeshInstance.h"

//namespace PE {
//	namespace Components {


		PhysicsComponent::PhysicsComponent(PE::Components::Mesh* inputM, PE::Components::MeshInstance* inputMI) {
			//PhysicsManager::addComponent(this);
			m = inputM;
			mi = inputMI;
		}

		Vector3* PhysicsComponent::returnPoints() {
			return points;
		}

		bool PhysicsComponent::checkCollision(Vector3& planeVec1, Vector3& planeVec2) {
			return false;
		}

		Vector3 PhysicsComponent::vecCollision(Vector3& planeVec1, Vector3& planeVec2) {
			return Vector3();
		}

//	}
//}