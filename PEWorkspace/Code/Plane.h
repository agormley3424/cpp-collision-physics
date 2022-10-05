#ifndef PLANE
#define PLANE

#include "PrimeEngine/Math/Vector3.h"
#include "PrimeEngine/Math/Matrix4x4.h"

class Plane {
public:
	Plane(Vector3 vec1, Vector3 vec2, Vector3 vec3, Vector3 vec4);
	const Vector3* getPoints();
	const Vector3& getNormal();
	Plane* transform(Matrix4x4& m);


	Vector3 points[4];
	Vector3 normal;
};


#endif