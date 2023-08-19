import m5
from m5.objects import *
m5.util.addToPath('../../')
from caches_2020528 import *

#Benchmark Path
benchmark="configs/A1/qsort_small"
benchmark_args="configs/A1/input_small.dat"

#Passing the arguements
args = sys.argv[1:]

#Creating the system
system = System()

#Setting clock frequency
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = '1GHz'
system.clk_domain.voltage_domain = VoltageDomain()

#Declaring 512MB RAM
system.mem_mode = 'timing'               
system.mem_ranges = [AddrRange('512MB')] 

#Creating CPU
system.cpu = TimingSimpleCPU()

#Creating L1 Cache
system.cpu.icache = L1ICache()
system.cpu.dcache = L1DCache()

#Creating a Bus
system.l2bus = L2XBar()

#Connecting L1 Cache to the CPU
system.cpu.icache.connectCPU(system.cpu)
system.cpu.dcache.connectCPU(system.cpu)

#Creating a Memory Bus
system.membus = SystemXBar()

#Connecting L1 to l2bus
system.cpu.icache.connectBus(system.l2bus)
system.cpu.dcache.connectBus(system.l2bus)

#Creating L2 Cache
system.l2cache = L2Cache(args[0],args[1])

#Connecting L2 to l2bus and membus
system.l2cache.connectCPUSideBus(system.l2bus)
system.l2cache.connectMemSideBus(system.membus)

#Creating interrupt controller
system.cpu.createInterruptController()
if m5.defines.buildEnv['TARGET_ISA'] == "x86":
    system.cpu.interrupts[0].pio = system.membus.mem_side_ports
    system.cpu.interrupts[0].int_requestor = system.membus.cpu_side_ports
    system.cpu.interrupts[0].int_responder = system.membus.mem_side_ports

system.system_port = system.membus.cpu_side_ports

#Setting Primary Memory
system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR3_1600_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.mem_side_ports

#Creating a process
system.workload = SEWorkload.init_compatible(benchmark)
process = Process()
process.cmd = [benchmark]+ [benchmark_args]
system.cpu.workload = process
system.cpu.createThreads()

#Setting up Root System
root = Root(full_system = False, system = system)
m5.instantiate()

#Starting Simulation
print("Beginning simulation!")
exit_event = m5.simulate()
print('Exiting @ tick %i because %s' % (m5.curTick(), exit_event.getCause()))
