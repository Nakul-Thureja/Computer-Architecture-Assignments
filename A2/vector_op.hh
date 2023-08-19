#ifndef __A2_VECTOR_OP_HH__
#define __A2_VECTOR_OP_HH__

#include "params/VectorOperations.hh"
#include "sim/sim_object.hh"

namespace gem5{

class VectorOperations : public SimObject
{
	  public:
	    VectorOperations(const VectorOperationsParams &p);
	    void startup();

	  private:
	    void processEvent1();
	    void processEvent2();
	    void processEvent3();   
    	    
	    EventFunctionWrapper event1;
	    EventFunctionWrapper event2;
	    EventFunctionWrapper event3;
	    
	    const std::string vectors;
	    
	 
};

}
#endif 
