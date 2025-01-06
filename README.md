# Spring Simulation in C++ (By Showmen Dey)
## Overview
This project demonstrates a spring simulation using particles and physics constraints. The simulation showcases how particles connected by a spring interact with each other under the influence of spring forces, damping, and gravity. The user can manipulate the spring by dragging the last particle with the mouse.

The program is implemented using Raylib for rendering and input handling, and Raymath for vector operations. It leverages object-oriented programming to model particles and springs.

## Features
- Particle System: Represents particles with position, velocity, and constraints.
- Spring Mechanics: Implements spring physics including force calculation, damping, and gravity.
- User Interaction: Allows the user to drag the last particle with the mouse.
- Dynamic Rendering: Renders particles as circles and springs as lines connecting them in real-time.
## Requirements
To run the project, ensure the following tools and libraries are installed:

- Raylib: For graphics and input handling.
- Raymath: For vector mathematics.
- A C++ compiler supporting C++11 or later.


## Classes
### Particle Class:

- Represents an individual particle with attributes:
- pos: Current position.
- velocity: Current velocity.
- isfixed: Boolean flag to determine if the particle is fixed.
**Methods:**
- Constructor initializes particle attributes.


### Spring Class:
- Represents a spring composed of particles.
**Attributes:**
- particleno: Number of particles in the spring.
- k: Spring stiffness constant.
- restlen: Rest length of the spring segments.
- particles: A collection of Particle objects.
**Methods:**
- Constructor: Initializes the spring with particles spaced vertically.
- update: Updates particle positions and velocities based on spring forces, damping, and gravity.
- draw: Renders the particles and the spring connecting them.
```
F= k * displacement
```

- F=k×displacement; Applied to particles to restore their position to the rest length.
- Damping: Reduces the velocity of particles to simulate energy loss over time.
- Gravity: Adds a downward force to all particles except fixed ones.

- Mouse Input: Drag the last particle with the left mouse button to interact with the spring.
### Customization
You can modify the simulation by changing these parameters in the code:

- Number of Particles: Adjust particleno in the Spring class constructor.
- Spring Stiffness (k): Increase or decrease to make the spring more rigid or flexible.
- Damping Factor: Change the damping value to simulate more or less energy loss.
- Gravity: Modify the value added to particles[i].velocity.y in the update method to simulate different gravitational forces.
