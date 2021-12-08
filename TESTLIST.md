Test list for PMU
=================

+ It returns a percentage value of the remaining power.
+ It makes a device xx_sleep for a while when the remaining power is lower than 
  the minimum allowed power limit.
+ It registers a new device in a devices bus.
+ It gradually registers new devices while the sleeping mode of the registered
  ones is available.