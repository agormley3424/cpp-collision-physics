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
bool PhysicsManager::pointColl(Vector3 point, Plane* plane) {
	float d = plane->normal.dotProduct(plane->points[0]);
	float e = point.dotProduct(plane->normal);

	return (e + d) < 0 ? true : false;
}


// Extends the center the distance of its radius along the orthogonal path to the plane
// Then checks whether it's "behind" the plane or not
// If I run this on every single plane, and they all come back as collisions, this should work, even though it's using infinite plane equations (I think)
bool PhysicsManager::projectPoint(Vector3* center, float radius, Plane* plane) {
	//assert(plane->normal.length() >= 0.99 && plane->normal.length() <= 1);
	
	Vector3 planeDir = plane->normal * -1;

	planeDir *= radius;

	Vector3 projectedPoint = (*center) + planeDir;

	return pointColl(projectedPoint, plane);
	/*
	float dMag = norman.dotProduct(plane->points[0]);
	Vector3 dVec = dMag * norman;
	float eMag = norman.dotProduct(*center);
	Vector3 eVec = e*/
}

// Collision logic:
// Compare phys to every component that is not itself
// For checking a sphere against a box, first check if the center intersects,
// If that fails, find the orthogonal distance between the plane and the center, normalize this vector, and project the center along it with the magnitude of the radius
// For checking a sphere against a sphere, 
// For checking a box against a box, 



// Check a collision between a sphere and a box
// Returns true on a collision, false otherwise 
bool PhysicsManager::spBoxCheck(PhysicsComponent* sphere, PhysicsComponent* box) {
	assert(sphere->type.compare("sphere") == 0 && box->type.compare("box") == 0);
	Plane* planes = box->returnPlanes();
	Vector3 center = sphere->getCenter();
	float radius = sphere->radius;


	for (int i = 0; i < 6; ++i) {
		if (!projectPoint(&center, radius, &planes[i])) {
			return false;
		}
	}

	return true;
}


// Check a physics object against all other known objects for collisions
// Assuming this will only be called on spheres
bool PhysicsManager::fullCheck(PhysicsComponent* phys)
{
	bool collision = false;;

	for (int i = 0; i < objectArr.size(); ++i) {
		if (objectArr[i]->label != phys->label) {
			if (phys->type.compare("sphere") == 0 && objectArr[i]->type.compare("box") == 0) {
				collision = spBoxCheck(phys, objectArr[i]);
			}
			else if (phys->type.compare("box") == 0 && objectArr[i]->type.compare("sphere") == 0) {
				collision = spBoxCheck(objectArr[i], phys);
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