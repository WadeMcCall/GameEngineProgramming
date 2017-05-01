#include "PhysicsManager.h"
#include "RenderManager.h"
#include "BulletSceneNodeMotionState.h"
#include "BulletDebugDrawer.h"
#include "RigidBody.h"
#include "CompoundShape.h"
#include "CompareRigidBodies.h"
#include "CompareCompoundShapes.h"

#include <iostream>

void PhysicsManager::stepPhysicsSimulation(float time_incr){
	btScalar time_step(time_incr);
	updateRigidBodies();
	updateRigidBodyVelocity(time_incr);
	dynamics_world->stepSimulation(time_step, 10, .01667);
	dynamics_world->debugDrawWorld();
}

void PhysicsManager::updateRigidBodyVelocity(float time_incr){
	AVLTreeIterator<RigidBody>* rigid_body_iter = rigid_bodies->tableIterator();
	while(rigid_body_iter->hasNext()){
		RigidBody* rb = rigid_body_iter->next();
		rb->incrementCustomVelocity(time_incr);
	}
	delete rigid_body_iter;
}

void PhysicsManager::setGravity(float* g){
	dynamics_world->setGravity(btVector3(g[0],g[1],g[2]));
}

void PhysicsManager::getGravity(float* g){
	btVector3 gravity = dynamics_world->getGravity();
	g[0] = gravity.x();
	g[1] = gravity.y();
	g[2] = gravity.z();
}

void PhysicsManager::getLinearVelocity(std::string rigid_body_name, float* v){
	RigidBody* rb = rigid_bodies->tableRetrieve(&rigid_body_name);
	
	if(rb){
		btRigidBody* bt_rb = rb->getRigidBody();
		btVector3 linear_velocity = bt_rb->getLinearVelocity();
		v[0] = linear_velocity.x();
		v[1] = linear_velocity.y();
		v[2] = linear_velocity.z();
	}
}

void PhysicsManager::setRigidBodyVelocity(std::string rigid_body_name, float end_time, float* a){
	RigidBody* rb = rigid_bodies->tableRetrieve(&rigid_body_name);
	rb->setCustomVelocity(end_time, a);
}

void PhysicsManager::applyTorqueImpusle(std::string rigid_body_name, float pitch, float yaw, float roll){
	RigidBody* rb_torque = rigid_bodies->tableRetrieve(&rigid_body_name);
	if(rb_torque){
		btRigidBody* bt_rb_torque = rb_torque->getRigidBody();
		bt_rb_torque->applyTorqueImpulse(btVector3(pitch, yaw, roll));
	}
}

PhysicsManager::PhysicsManager(RenderManager* rm){
	CompareRigidBodies* compare_rigid_bodies = new CompareRigidBodies();
	rigid_bodies = new TableAVL<RigidBody, std::string>(compare_rigid_bodies);
	CompareCompoundShapes* compare_compound_shapes = new CompareCompoundShapes();
	compound_shapes = new TableAVL<CompoundShape, std::string>(compare_compound_shapes);
	
	render_manager = rm;
	init();
	
	BulletDebugDrawer* debug_drawer = new BulletDebugDrawer(rm);
	dynamics_world->setDebugDrawer(debug_drawer);
	dynamics_world->getDebugDrawer()->setDebugMode(1);
	
	float* gravity = new float[3];
	gravity[0] = 0;
	gravity[1] = -9.8;
	gravity[2] = 0;
	setGravity(gravity);
	delete[] gravity;
}

PhysicsManager::~PhysicsManager(){
	AVLTreeIterator<CompoundShape>* compound_shape_iter = compound_shapes->tableIterator();
	while(compound_shape_iter->hasNext()){
		CompoundShape* cs = compound_shape_iter->next();
		delete cs;
	}
	delete compound_shape_iter;
	delete compound_shapes;
	
	int num_collision_objects = dynamics_world->getNumCollisionObjects();
	btAlignedObjectArray<btCollisionObject*> rigid_bodies_array = dynamics_world->getCollisionObjectArray();
	
	for(int i = num_collision_objects - 1; i >= 0; i++){
		btRigidBody* rigid_body = btRigidBody::upcast(rigid_bodies_array[i]);
		dynamics_world->removeCollisionObject(rigid_body);
		delete rigid_body->getMotionState();
		delete rigid_body->getCollisionShape();
	}
	AVLTreeIterator<RigidBody>* rigid_body_iter = rigid_bodies->tableIterator();
	while(rigid_body_iter->hasNext()){
		RigidBody* rgb = rigid_body_iter->next();
		delete rgb;
	}
	delete rigid_body_iter;
	delete rigid_bodies;
	
	BulletDebugDrawer* debug_drawer = (BulletDebugDrawer*) dynamics_world->getDebugDrawer();
	delete debug_drawer;
	
	delete dynamics_world;
	delete solver;
	delete dispatcher;
	delete collision_configuration;
	delete overlapping_pair_cache;
	
	render_manager = NULL;
}

void PhysicsManager::init(){
	overlapping_pair_cache = new btDbvtBroadphase();
	collision_configuration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collision_configuration);
	solver = new btSequentialImpulseConstraintSolver();
	dynamics_world = new btDiscreteDynamicsWorld(dispatcher, overlapping_pair_cache, solver, collision_configuration);
	
}

void PhysicsManager::createRigidBodies(){
	AVLTreeIterator<CompoundShape>* it = compound_shapes->tableIterator();
	btCompoundShape* com_shape = 0;
	while(it->hasNext()){
		CompoundShape* cs = it->next();
		SceneNodeMotion* snm = render_manager->createSceneNodeMotion(*(cs->getKey()));
		string mstr = "snm";
		string* motion_state_str = &mstr;
		
		BulletSceneNodeMotionState* ms = new BulletSceneNodeMotionState(motion_state_str, snm, render_manager);
		btScalar* m = new btScalar(cs->getMass());
		com_shape = cs->getCompoundShape();
		btVector3* li = new btVector3(0,0,0);
		com_shape->calculateLocalInertia(*m, *li);
		btRigidBody::btRigidBodyConstructionInfo* rbci = new btRigidBody::btRigidBodyConstructionInfo(*m, ms, com_shape);
		btRigidBody* btrb = new btRigidBody(*rbci);
		btrb->setDamping(-1,1);
		btrb->setActivationState(DISABLE_DEACTIVATION);
		RigidBody* rb = new RigidBody(*(cs->getKey()), btrb);
		rigid_bodies->tableInsert(rb);
		
		dynamics_world->addRigidBody(btrb);
	}
	delete it;
}

void PhysicsManager::createCollisionShape(std::string& compound_shape_id, std::string& collision_shape, float* collision_shape_params, float mass, float* translation, float* rotation){
	btCollisionShape* col_shape = NULL;
	if(collision_shape == "sphere")
		col_shape = new btSphereShape(btScalar(collision_shape_params[0]));
	else if(collision_shape == "cylinder_y"){
		cout << "here cylinder_y";
		col_shape = new btCylinderShape(btVector3(collision_shape_params[0], collision_shape[1], collision_shape[2]));
	}
	else if(collision_shape == "cylinder_z")
		col_shape = new btCylinderShapeZ(btVector3(collision_shape_params[0], collision_shape_params[1], collision_shape[2]));
	else
		col_shape = new btBoxShape(btVector3(collision_shape_params[0], collision_shape_params[1], collision_shape_params[2]));
	btTransform* tr = new btTransform();
	tr->setIdentity();
	tr->setOrigin(btVector3(translation[0], translation[1], translation[2]));
	tr->setRotation(btQuaternion(rotation[0], rotation[1], rotation[2], rotation[3]));
	
	CompoundShape* cs = compound_shapes->tableRetrieve(&compound_shape_id);
	
	if(cs == NULL){
		compound_shapes->tableInsert(new CompoundShape(compound_shape_id, new btCompoundShape));
		cs = compound_shapes->tableRetrieve(&compound_shape_id);
	}
	
	cs->addChildShape(tr, col_shape, mass);
}

void PhysicsManager::updateRigidBodies(){
	int num_collision_objects = dynamics_world->getNumCollisionObjects();
	btAlignedObjectArray<btCollisionObject*> rigid_bodies = dynamics_world->getCollisionObjectArray();
	
	for(int i = num_collision_objects -1; i >= 0; i--){
		btRigidBody* rigid_body = btRigidBody::upcast(rigid_bodies[i]);
		BulletSceneNodeMotionState* motion_state = (BulletSceneNodeMotionState*) rigid_body;
		
		if(rigid_body && rigid_body->getMotionState()){
			btTransform current_transform;
			rigid_body->getMotionState()->getWorldTransform(current_transform);
			//motion_state->copyNodeTransformIntoBulletTransform();
			void *userPointer = rigid_body->getUserPointer();
			if(userPointer){
				cout << "here update" <<endl;
				btQuaternion orientation = current_transform.getRotation();
				Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode*>(userPointer);
				sceneNode->setPosition(Ogre::Vector3(current_transform.getOrigin().getX(), current_transform.getOrigin().getY(), current_transform.getOrigin().getZ()));
				sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
			}
		}
	}
}