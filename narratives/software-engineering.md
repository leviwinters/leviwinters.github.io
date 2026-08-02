---
title: Software Design and Engineering
---

# Software Design and Engineering

**Artifact:** Investment client manager (`Project1.cpp`)
**Original course:** CS 410

## Description

This artifact is a C++ console application from my CS 410 course, a reverse engineering and low level programming class. The original assignment gave me a compiled binary with no source code, and I had to read through the disassembled instructions and reconstruct working C++ that matched the program's behavior. The result is a small investment company client management tool. It logs a user in, then lets them view a list of five clients and their selected service, or change a client's service selection. I built this artifact in that course, prior to CS 499.

## Justification and Enhancement

I chose this artifact because the original version was fairly rough, procedural code, which gave me a clear opportunity to demonstrate object oriented design and defensive programming. The original stored client data in five separate global variables for names and five more for service choices, used a five branch if/else chain to update a client, and had a bug where the new service value was never actually read from user input before being assigned. I replaced the parallel variables with a `Client` class and a vector, so one loop handles displaying and updating instead of repeating the same logic five times. I also fixed the input bug, added validation so non numeric input doesn't break the program, removed a confusing leftover login prompt, and replaced the hardcoded service numbers with named constants. These changes show I can take working but poorly structured code and make it organized and correct.

## Course Outcomes

I met both outcomes I planned for. Outcome three was addressed through the move from parallel variables to an object oriented `Client` class and vector, a design trade off I can explain and defend. Outcome four was addressed through the cleanup work, removing duplicated code, adding input validation, and fixing the service update bug. The one update is that I ended up doing more defensive programming than originally scoped, so outcome four is covered more thoroughly than expected.

## Reflection

This reminded me how easily a bug can hide when code looks like it should work. The missing input read in the original change service function compiled fine and looked complete, but never captured what the user typed. Tracing through it carefully taught me to be more skeptical of my own past code instead of trusting it just because it ran. The main challenge was deciding how far to take the class design without overengineering a small program, so I kept the `Client` class simple rather than adding structure it didn't need.
