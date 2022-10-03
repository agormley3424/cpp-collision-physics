#include "PhysicsManager.h"
#include "PhysicsComponent.h"
#include <vector>

//namespace PE {
//	namespace Components {


		//bool PhysicsManager::collCheck(PhysicsComponent) {
		//	return false;
		//}

std::vector<PhysicsComponent*>* PhysicsManager::objectArr = {};

		bool PhysicsManager::collCheck(PhysicsComponent) {
			return false;
		}

		void PhysicsManager::addComponent(PhysicsComponent* p) {
			p->label = PhysicsManager::objectArr->size();
			//objectArr[0] = p;
			PhysicsManager::objectArr->push_back(p);
		}


		Vector3 PhysicsManager::collAdjust(PhysicsComponent) {
			return Vector3();
		}
//	}
//}