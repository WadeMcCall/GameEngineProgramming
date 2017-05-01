#if !defined PHYSICS_MANAGER
#define PHYSICS_MANAGER

#include "btBulletDynamicsCommon.h"
#include "CSC2110/TableAVL.h"

class RigidBody;
class CompoundShape;
class RenderManager;
struct SceneNodeMotion;

class PhysicsManager{
	private:
		RenderManager* render_manager;
		TableAVL<RigidBody, std::string>* rigid_bodies;
		TableAVL<CompoundShape, std::string>* compound_shapes;
		
		btBroadphaseInterface* overlapping_pair_cache;
		btDefaultCollisionConfiguration* collision_configuration;
		btCollisionDispatcher* dispatcher;
		
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamics_world;
		
		void init();
		
	public:
		PhysicsManager(RenderManager* rm);
		~PhysicsManager();
		void stepPhysicsSimulation(float time_incr);
		void updateRigidBodyVelocity(float time_incr);
		void setGravity(float* g);
		void getGravity(float* g);
		void getLinearVelocity(std::string rigid_body_name, float* v);
		void setRigidBodyVelocity(std::string rigid_body_name, float end_time, float* a);
		void applyTorqueImpusle(std::string rigid_body_name, float pitch, float yaw, float roll);
		void createRigidBodies();
		void createCollisionShape(std::string& compound_shape_id, std::string& collision_shape, float* params, float mass, float* translation, float* rotation);
		void updateRigidBodies();
		void applyImpulse(std::string rigid_body_name, float ns, float ew, float force);
		void clearForces();
};
#endif