# optimization_engine

### The Optimization Engine

A solution written in C++ that creates a Constraint Programming (CP) problem based on the input in the form of a dual-core embedded system application.
The optimization engine then attempts to find a schedule for the embedded systems application with minimized inter-core data-propagation delays.
The application is complete with a synthetic test generator.

### Setup

The solution utilises the very powerful IBM ILOG CP Optimizer CP solver to efficiently find the schedules for the input embedded system application.
To run the CPLEX CP Optimizer has to be set up on the machine: https://www.ibm.com/analytics/cplex-cp-optimizer.
