#include "Plane.h"
#include "PrimeEngine/Math/Vector3.h"

// Points should be given in order of two parallel pairs
Plane::Plane(Vector3 vec1, Vector3 vec2, Vector3 vec3, Vector3 vec4) {

	Vector3 newVec1 = vec1 - vec2;
	Vector3 newVec2 = vec3 - vec4;

	normal = vec1.crossProduct(vec2);
}
const Vector3* Plane::getPoints() {
	return points;
}
const Vector3& Plane::getNormal() {
	return normal;
}
