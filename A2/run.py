import m5
from m5.objects import *
import sys

print(type(sys.argv))
print('The command line arguments are:')
list = sys.argv[1:]
arg = ""
for i in list:
    arg = arg + i + " "


root = Root(full_system = False)

root.h = VectorOperations(parameter = arg)
m5.instantiate()

print("Beginning simulation!")
exit_event = m5.simulate()
print('Exiting @ tick {} because {}'
          .format(m5.curTick(), exit_event.getCause()))


