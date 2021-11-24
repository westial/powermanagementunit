Test list for PMU
=================

+ It returns a percentage value of the remaining power.
- Percentage input value type is configurable.
- It makes a device sleep for a while when the remaining power is lower than 
  the minimum allowed power limit.
- It gradually registers new devices while the sleeping mode of the registered
  ones is available.