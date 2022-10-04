#ifndef PLANE
#define PLANE

#include "PrimeEngine/Math/Vector3.h"

class Plane {
public:
	Plane(Vector3 vec1, Vector3 vec2, Vector3 vec3, Vector3 vec4);
	const Vector3* getPoints();
	const Vector3& getNormal();


	Vector3* points;
	Vector3 normal;
};


#endif