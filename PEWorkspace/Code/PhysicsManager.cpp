#include "PhysicsManager.h"
#include "PhysicsComponent.h"
#include <vector>
#include <assert.h>

//namespace PE {
//	namespace Components {


		//bool PhysicsManager::collCheck(PhysicsComponent) {
		//	return false;
		//}

std::vector<PhysicsComponent*> PhysicsManager::objectArr = {};



// Returns true if pint is "inside" the given plane
bool PhysicsManager::pointColl(Vector3 point, Plane plane, Matrix4x4* m_base) {
	//point = { 0, 0, 0 };
	Matrix4x4 inverseTranspose = ((*m_base).inverse()).transpose();
	//Vector3 newNorm = inverseTranspose * plane.normal;
	//newNorm.normalize();
	Vector3 newNorm = plane.normal;
	PrimitiveTypes::Float32 d = newNorm.dotProduct(plane.getPoints()[0]) * -1;
	PrimitiveTypes::Float32 e = point.dotProduct(newNorm);

	return (e + d) <= 0.0 + std::numeric_limits<PrimitiveTypes::Float32>::epsilon() ? true : false;
}


// Extends the center the distance of its radius along the orthogonal path to the plane
// Then checks whether it's "behind" the plane or not
// If I run this on every single plane, and they all come back as collisions, this should work, even though it's using infinite plane equations (I think)
bool PhysicsManager::projectPoint(Vector3 center, PrimitiveTypes::Float32 radius, Plane plane, Matrix4x4* m_base) {
	//assert(plane->normal.length() >= 0.99 && plane->normal.length() <= 1);
	
	Vector3 planeDir = plane.normal * -1;

	planeDir *= radius;

	Vector3 projectedPoint = center + planeDir;

	return pointColl(projectedPoint, plane, m_base);
	
	//PrimitiveTypes::Float32 dMag = norman.dotProduct(plane->points[0]);
	//Vector3 dVec = dMag * norman;
	//PrimitiveTypes::Float32 eMag = norman.dotProduct(*center);
	//Vector3 eVec = e
}

// Collision logic:
// Compare phys to every component that is not itself
// For checking a sphere against a box, first check if the center intersects,
// If that fails, find the orthogonal distance between the plane and the center, normalize this vector, and project the center along it with the magnitude of the radius
// For checking a sphere against a sphere, 
// For checking a box against a box, 



// Check a collision between a sphere and a box
// Returns true on a collision, false otherwise 
bool PhysicsManager::spBoxCheck(PhysicsComponent* sphere, PhysicsComponent* box, Matrix4x4* m_base) {
	assert(sphere->type.compare("sphere") == 0 && box->type.compare("box") == 0);
	Plane* planes = box->returnPlanes();
	Vector3 center = sphere->getCenter();
	PrimitiveTypes::Float32 radius = sphere->radius;


	for (int i = 0; i < 6; ++i) {
		if (!projectPoint(center, radius, planes[i], m_base)) {
			return false;
		}
	}

	return true;
}


//// Returns true if a collision is detected between a sphere and a box
//bool PhysicsManager::spBoxCheck(PhysicsComponent* sphere, PhysicsComponent* box, Matrix4x4* m_base) {
//	Plane* planes = box->returnPlanes();
//	Vector3 center = sphere->getCenter();
//
// 	for (int i = 0; i < 6; ++i) {
//		if (!pointColl(center, planes[i], m_base)) {
//			return false;
//		}
//	}
//
//	return true;
//}



// Component 3 is the car
// Check a physics object against all other known objects for collisions
// Assuming this will only be called on spheres
// Returns true if a collision was detected
bool PhysicsManager::fullCheck(PhysicsComponent* phys)
{
	bool collision = false;

	for (int i = 0; i < objectArr.size(); ++i) {
		if (objectArr[i]->label != phys->label) {
			if (phys->type.compare("sphere") == 0 && objectArr[i]->type.compare("box") == 0) {
				collision = spBoxCheck(phys, objectArr[i], phys->m_base);
			}
			else if (phys->type.compare("box") == 0 && objectArr[i]->type.compare("sphere") == 0) {
				collision = spBoxCheck(objectArr[i], phys, phys->m_base);
			}
			else {
				continue;
			}
		}
	}

	return collision;
}

void PhysicsManager::addComponent(PhysicsComponent* p) {
	p->label = PhysicsManager::objectArr.size();
	//objectArr[0] = p;
	PhysicsManager::objectArr.push_back(p);
}


Vector3 PhysicsManager::collAdjust(PhysicsComponent) {
	return Vector3();
}
//	}
//}