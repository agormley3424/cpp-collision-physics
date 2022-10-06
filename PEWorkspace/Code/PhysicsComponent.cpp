#include "PhysicsComponent.h"
#include "PrimeEngine/Math/Vector3.h"

#include "PrimeEngine/Scene/Mesh.h"
#include "PrimeEngine/Scene/MeshInstance.h"

#define POSINFINITY std::numeric_limits<PrimitiveTypes::Float32>::max()
#define NEGINFINITY std::numeric_limits<PrimitiveTypes::Float32>::min()

//namespace PE {
//	namespace Components {

		Plane* PhysicsComponent::maxPoints(PE::Components::Mesh* m) {
			PositionBufferCPU* p = (PositionBufferCPU*)m->m_hPositionBufferCPU.getObject();
			PrimitiveTypes::Float32* verts = p->m_values.getFirstPtr();

			//PrimitiveTypes::Float32 maxVert[3] = { NEGINFINITY, NEGINFINITY, NEGINFINITY };
			//PrimitiveTypes::Float32 minVert[3] = { POSINFINITY, POSINFINITY, POSINFINITY };

			PrimitiveTypes::Float32 maxVert[3] = { verts[0], verts[0], verts[0] };
			PrimitiveTypes::Float32 minVert[3] = { verts[0], verts[0], verts[0] };

			PrimitiveTypes::UInt32 numVerts = p->m_values.m_size; // how much is stored at the moment

			assert(numVerts > 0);

			for (int i = 0; i < numVerts; i += 3) {
				maxVert[0] = max(maxVert[0], verts[i]);
				maxVert[1] = max(maxVert[1], verts[i + 1]);
				maxVert[2] = max(maxVert[2], verts[i + 2]);

				minVert[0] = min(minVert[0], verts[i]);
				minVert[1] = min(minVert[1], verts[i + 1]);
				minVert[2] = min(minVert[2], verts[i + 2]);
			}

			Vector3 topForwardLeft = { minVert[0], maxVert[1], minVert[2] };
			Vector3 topForwardRight = { maxVert[0], maxVert[1], minVert[2] };
			Vector3 topBackLeft = { minVert[0], maxVert[1],maxVert[2] };
			Vector3 topBackRight = { maxVert[0], maxVert[1],maxVert[2] };

			Vector3 bottomForwardLeft = { minVert[0], minVert[1],minVert[2] };
			Vector3 bottomForwardRight = { maxVert[0], minVert[1],minVert[2] };
			Vector3 bottomBackLeft = { minVert[0], minVert[1],maxVert[2] };
			Vector3 bottomBackRight = { maxVert[0], minVert[1],maxVert[2] };


			/*
			Vector3 topForwardLeft = (*m_base) * topForwardLeft;
			Vector3 topForwardRight = (*m_base) * topForwardRight;
			Vector3 topBackLeft = (*m_base) * topBackLeft;
			Vector3 topBackRight = (*m_base) * topBackRight;

			Vector3 bottomForwardLeft = (*m_base) * bottomForwardLeft;
			Vector3 bottomForwardRight = (*m_base) * bottomForwardRight;
			Vector3 bottomBackLeft = (*m_base) * bottomBackLeft;
			Vector3 bottomBackRight = (*m_base) * bottomBackRight;*/


			Plane* planeList = (Plane*) calloc(6, sizeof(Plane));

			//planeList[0] = { topForwardLeft, bottomForwardLeft, topForwardRight, bottomForwardRight };
			//planeList[1] = { topBackLeft, bottomBackLeft, topForwardLeft, bottomForwardLeft };
			//planeList[2] = { topForwardRight, bottomForwardRight, topBackRight, bottomBackRight };
			//planeList[3] = { topBackRight, bottomBackRight, topBackLeft, bottomBackLeft };
			//planeList[4] = { topForwardLeft, topForwardRight, topBackLeft, topBackRight };
			//planeList[5] = { bottomForwardLeft, bottomForwardRight, bottomBackLeft, bottomBackRight };


			// Front face
			planeList[0] = { topForwardLeft, topForwardRight, bottomForwardRight, bottomForwardLeft };

			// Left face
			planeList[1] = { topBackLeft, topForwardLeft, bottomForwardLeft, bottomBackLeft };

			// Right face
			planeList[2] = { topForwardRight, topBackRight, bottomBackRight, bottomForwardRight };

			// Back face
			planeList[3] = { topBackRight, topBackLeft, bottomBackLeft, bottomBackRight };

			// Top face
			planeList[4] = { topBackLeft, topBackRight, topForwardRight, topForwardLeft };

			// Bottom face
			planeList[5] = { bottomForwardLeft, bottomForwardRight, bottomBackRight, bottomBackLeft};

			return planeList;
		}


		PhysicsComponent::PhysicsComponent(Matrix4x4* in_base, Matrix4x4* in_worldTransform, PE::Components::Mesh* inputM, PE::Components::MeshInstance* inputMI, std::string intype) {
			//PhysicsManager::addComponent(this);
			mesh = inputM;
			meshInstance = inputMI;
			m_base = in_base;
			m_worldTransform = in_worldTransform;
			PhysicsComponent::type = intype;

			if (type.compare("sphere") == 0) {
				center = in_base->getPos();
				radius = 50;
			}
			else if (type.compare("box") == 0) {
				box = maxPoints(mesh);
			}
			else {
				throw "PhysicsComponent Error: Invalid collider type specified";
			}
		}

		Plane* PhysicsComponent::returnPlanes() {
			Plane* transformedPlanes = (Plane*) calloc(6, sizeof(Plane));

			for (int i = 0; i < 6; ++i) {
				transformedPlanes[i] = *(box[i].transform(*m_base));
			}

			return transformedPlanes;
		}

		bool PhysicsComponent::checkCollision(Vector3& planeVec1, Vector3& planeVec2) {
			return false;
		}

		Vector3 PhysicsComponent::vecCollision(Vector3& planeVec1, Vector3& planeVec2) {
			return Vector3();
		}


		PhysicsComponent::~PhysicsComponent() {
			free(box);
		}

		Vector3  PhysicsComponent::getCenter() {
			return (*m_base) * center;
		}
//	}
//}