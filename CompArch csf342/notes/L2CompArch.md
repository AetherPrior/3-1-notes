# Lecture 2

## Single core Era

$\mathcal{P = ACV^2f + \tau AVI_{short} + VI_{leak}}$

$\mathcal{f}_{max}$ $\alpha$ $\mathcal{1/V}$

But, we can't just keep reducing the Voltage as:

$\mathcal{I_{leak}}$ $\alpha$ $\mathcal{1/V_{th}}$

### Dynamic Power consumption

power which is used to charge and discharge the capacitors

## Why did Single core era die

Transistor technology should support increasing frequency

Minimum voltage below which you can't reduce
Performance per watt grows exponentially, but there is a limit

- 40% of power consumption is due to leakage power
- Scientists kept reducing threshold voltage until power consumption of leakage power became significant
- Improved cooling techniques and it became too expensive

Since they weren't able to increase frequency and not decrease voltage or cool it, it became the end of single core era

## Multicore Era

ILP - Instruction Level Parallelism

Frequency has decreased now-a-days, as with reduced frequency has resulted in same throughput T

Amdahl's law: In computer architecture, Amdahl's law (or Amdahl's argument) is a formula which gives the theoretical speedup in latency of the execution of a task at fixed workload that can be expected of a system whose resources are improved.

due to limited number of pins - not all cores accessible

not all cores can be used at the same times

50% of cores turned off at 8nm -- 50% form _dark-silicon_

- end of multicore era

### Dark Silicon era

    - Heterogenous cores
    - some cores are faster than others
