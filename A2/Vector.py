
from m5.params import *
from m5.SimObject import SimObject

class VectorOperations(SimObject):
        type = 'VectorOperations'
        cxx_header = "A2/vector_op.hh"
        cxx_class = "gem5::VectorOperations"
        
        parameter = Param.String("Enter integer n followed by 2*n integers and followed by 3 ticks")
    
