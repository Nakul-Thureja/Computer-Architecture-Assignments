Name: Nakul Thureja
Roll No: 2020528
Assignment 2

This assignment asked us to Create and Simulate our own Simobject that performs:

1. addition of two vectors
2. dot product of two vectors
3. normalize vectors

and also to create four debug flags

1. VECTOR: display the vectors
2. ADDRESULT: display the resultant vector from VectorAddition
3. DOTRESULT: display the resultant value from VectorDotProduct
4. NORMALIZ: display the resultant vectors from NormalizeVector

Debug Flags: are provided by gem5 to have a better debugging experience
flags can allow to have many debug print statements and we can enable different
debug file and only the debug flags enabled will print out the statements.

Attached files are:

1. Sconsript
   We define a SConscript for the files to be compiled by the build system.
   I imported all the files and add debug flags here, I added the four flags
   VECTOR, ADDRESULT, DOTRESULT, NORMALIZE

2. vector_op.cc
   Declared global vectors A,B with given size

   Declared the functions to perform actions on vectors

   1. ADDRESULT: ProcessEvent1()
      float sum[size];
      for (i = 0; i < size; i++)
      {
      sum[i] = A[i] + B[i];
      cout << sum[i] << " ";
      }

   2. DOTRESULT: ProcessEvent2()
      float dot = 0;
      for (i = 0; i < size; i++)
      dot = dot + A[i] \* B[i];

   3. NORMALIZ: ProcessEvent3()
      float sum1 = 0;
      float sum2 = 0;

      for (i = 0; i < size; i++)
      {
      sum1 += A[i] _ A[i];
      sum2 += B[i] _ B[i];
      }
      sum1 = sqrt(sum1);
      sum2 = sqrt(sum2);

      for (i = 0; i < size; i++)
      {
      A[i] = A[i] / sum1;
      B[i] = B[i] / sum2;
      }

3. vector_op.hh
   private: I declared the functions "processEvent1()","processEvent2()","processEvent3()"
   along with three "EventFunctionWrapper" event1,event2,event3.
   public: I declared SimObject "VectorOperations" and "startup()"

4. Vector.py
   python file to instantiate our Simobject. Imports all the
   sim objects from m5.objects and then instantiates our root object.
   makes VectorOperations sim object as the child of the root object
   and instantiates it.

5. run.py
   python script used to instantiate and simulate the VectorOperations SimObject using root.

Bonus:
I also pass the command line arguement as
arg1 is n, the size of the vector
followed by 2\*n numbers n for vector1 and vector2
followed by the three ticks to schedule event1,event2 and event3

How to run the script:

1. Place all the files except run.py in a folder in gem5/src
2. Place the file run.py in folder gem5/configs
3. Build the gem5 by running the command "scons build/X86/gem5.opt"
4. Run the simulation by running the command
   "build/X86/gem5.opt configs/run.py 4 1 2 3 4 5 6 7 8 100 500 1000"

Explaination:
configs/run.py: path to run file
4: size of vectors
1 2 3 4: vector 1
5 6 7 8: vector 2
100: tick1
500: tick2
1000: tick3
