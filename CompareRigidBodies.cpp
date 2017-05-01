#include "CompareRigidBodies.h"
#include "RigidBody.h"

CompareRigidBodies::CompareRigidBodies()
{}

CompareRigidBodies::~CompareRigidBodies()
{}

int CompareRigidBodies::compare(std::string* compound_shape_id, RigidBody* compound_shape)
{
   std::string* compound_shape_str = compound_shape->getKey();
   return compound_shape_id->compare(*compound_shape_str);
}

int CompareRigidBodies::compare(RigidBody* compound_shape_1, RigidBody* compound_shape_2)
{
   std::string* compound_shape_id = compound_shape_1->getKey();
   return compare(compound_shape_id, compound_shape_2);
}
