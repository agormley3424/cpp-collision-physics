#include "Plane.h"
#include "PrimeEngine/Math/Vector3.h"

// Points should be given in order of two parallel pairs
Plane::Plane(Vector3 vec1, Vector3 vec2, Vector3 vec3, Vector3 vec4) {

	Vector3 newVec1 = vec1 - vec2;
	Vector3 newVec2 = vec3 - vec2;

	normal = newVec1.crossProduct(newVec2);
	normal = normal * -1;
	normal.normalize();


	points[0] = vec1;
	points[1] = vec2;
	points[2] = vec3;
	points[3] = vec4;
}
const Vector3* Plane::getPoints() {
	return points;
}
const Vector3& Plane::getNormal() {
	return normal;
}

Plane* Plane::transform(Matrix4x4& m) {
	Vector3 vec1 = m * points[0];
	Vector3 vec2 = m * points[1];
	Vector3 vec3 = m * points[2];
	Vector3 vec4 = m * points[3];

	return new Plane(vec1, vec2, vec3, vec4);
}
