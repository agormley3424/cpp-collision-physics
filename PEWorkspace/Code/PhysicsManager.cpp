#include "PhysicsManager.h"
#include "PhysicsComponent.h"
#include <vector>
#include <assert.h>
#include "PrimeEngine/Scene/SceneNode.h"

//namespace PE {
//	namespace Components {


		//bool PhysicsManager::collCheck(PhysicsComponent) {
		//	return false;
		//}

std::vector<PhysicsComponent*> PhysicsManager::objectArr = {};



// Returns true if pint is "inside" the given plane
bool PhysicsManager::pointColl(Vector3 point, Plane plane, Matrix4x4* m_base) {
	//point = { 0, 0, 0 };
	//Matrix4x4 inverseTranspose = ((*m_base).inverse()).transpose();
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
	//Vector3 center = sphere->getCenter();
	Vector3 center = m_base->getPos();
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
// Returns a vector of colliding objects that are colliding with the soldier, else a nullptr array
std::vector<PhysicsComponent*> PhysicsManager::fullCheck(PhysicsComponent* phys)
{
	std::vector<PhysicsComponent*> collList;

	for (int i = 0; i < objectArr.size(); ++i) {
		if (objectArr[i]->label != phys->label) {
			if (phys->type.compare("sphere") == 0 && objectArr[i]->type.compare("box") == 0) {
				if (spBoxCheck(phys, objectArr[i], phys->m_base)) {
					collList.push_back(objectArr[i]);
				}
			}
			else if (phys->type.compare("box") == 0 && objectArr[i]->type.compare("sphere") == 0) {
				if (spBoxCheck(objectArr[i], phys, phys->m_base)) {
					collList.push_back(objectArr[i]);
				}
			}
			else {
				continue;
			}
		}
	}

	return collList;
}

void PhysicsManager::addComponent(PhysicsComponent* p) {
	p->label = PhysicsManager::objectArr.size();
	//objectArr[0] = p;
	PhysicsManager::objectArr.push_back(p);
}


Vector3 PhysicsManager::collAdjust(PhysicsComponent) {
	return Vector3();
}

/*
// Compares the dot product of the forward vector with every plane's normal,
// returning the normal of the nearest plane or the average normals of all nearest planes
Vector3 PhysicsManager::nearestPlane(Plane* planeArr, Vector3 forwardVec) {
	float minVal = 10;
	std::vector<Plane> planeVec;
	Plane* minPlane;

	float allowedDiff = 3.0;

	for (int i = 0; i < 6; ++i) {
		float dotCompare = forwardVec.dotProduct(planeArr[i].getNormal());
		if (dotCompare < minVal) {
			minVal = dotCompare;
			minPlane = &planeArr[i];
		}
	}

	Vector3 normal = minPlane->getNormal();


	for (int i = 0; i < 6; ++i) {
		float dotCompare = forwardVec.dotProduct(planeArr[i].getNormal());
		if (dotCompare <= minVal - allowedDiff) {
			normal = planeArr[i].getNormal();
		}
			
	}

	normal.normalize();

	return normal;
}

*/


// Finds the nearest planes to the center and averages their normals
// I want to calculate the orthogonal distance from the center to the plane for every plane
Vector3 PhysicsManager::nearestPlane(Plane* planeArr, Vector3 forwardVec, Vector3 point) {
	PrimitiveTypes::Float32 minVal = -999999;
	Plane* minPlane;
	
	for (int i = 0; i < 6; ++i) {
		Plane plane = planeArr[i];
		Vector3 newNorm = plane.getNormal();
		PrimitiveTypes::Float32 d = newNorm.dotProduct(plane.getPoints()[0]) * -1;
		PrimitiveTypes::Float32 e = point.dotProduct(newNorm);
		PrimitiveTypes::Float32 c = e + d;


		if (c > minVal) {
			minPlane = &planeArr[i];
			minVal = c;
		}
	}

	return minPlane->getNormal();

}

void PhysicsManager::checkAndMove(Matrix4x4* m_base, PhysicsComponent* p, Vector3 curPos, Vector3 dir, float dist) {
	std::vector<PhysicsComponent*> collList = fullCheck(p);

	if (collList.size() > 0) {
		for (int i = 0; i < collList.size(); ++i) {
			Plane* planeList = collList[i]->returnPlanes();
			//Plane nearest = nearestPlane(planeList, dir);
			dir = dir + nearestPlane(planeList, dir, p->getCenter());
			dir.normalize();
		}
		//p->dir = dir;
		//p->constDir = true;

		
		Vector3 betterDir = Vector3(dir.getX(), 0, dir.getZ());
		
		//m_base->turnInDirection(dir, 3.1415f);
		m_base->setPos(curPos + betterDir * dist);
	}
	else {
		//p->constDir = false;
		//Vector3 subVec = { 0, p->dir.getY() - 1, 0 };
		//m_base->turnInDirection(dir, 3.1415f);
		//m_base->setPos((curPos + subVec) + dir * dist);
		m_base->setPos(curPos + dir * dist);
	}

	return;
}
//	}
//}