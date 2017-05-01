#if !defined COMPARE_RIGID_BODIES
#define COMPARE_RIGID_BODIES

#include "CSC2110/Comparator.h"
#include "GameHeader.h"

class RigidBody;

class CompareRigidBodies : public Comparator<RigidBody, std::string>
{ 
   private:

   public:
      CompareRigidBodies();
      virtual ~CompareRigidBodies();

      virtual int compare(RigidBody* compound_shape_1, RigidBody* compound_shape_2);
	  virtual int compare(std::string* compound_shape_id, RigidBody* compound_shape);
};

#endif
