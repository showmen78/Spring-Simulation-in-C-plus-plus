#include "raylib.h"    // Include Raylib for graphics and input
#include "raymath.h"   // Include Raymath for vector math operations
#include <vector>      // Include the vector library for dynamic arrays
#include <cmath>       // Include the cmath library for mathematical functions
#include <stdio.h>     // Include the stdio library for input/output

// Define the Particle class
class Particle {
public:
    Vector2 pos, velocity;  // Position and velocity of the particle
    bool isfixed;           // Whether the particle is fixed (cannot move)

    // Constructor to initialize a Particle with position and fixed status
    Particle(Vector2 pos, bool isfixed)
        : pos(pos), velocity({ 0, 0 }), isfixed(isfixed) {
    }

};

// Define the Spring class
class Spring {
public:
    int particleno;                 // Number of particles in the spring
    float k, restlen;               // Spring constant (stiffness) and rest length
    std::vector<Particle> particles; // Collection of particles forming the spring

    // Constructor to initialize the Spring with particle count, rest length, and spring constant
    Spring(int particleno, float restlen, float k)
        : particleno(particleno), restlen(restlen), k(k), particles(particles) {
        // Populate the particles vector
        for (int i = 0; i < particleno; i++) {
            particles.emplace_back(Particle({ 300, 100 + i * 1.0f }, false)); // Place particles vertically spaced
        }
    }

    // Update method to calculate physics for all particles
    void update(float deltatime, float damping) {
        // Iterate through particles to apply spring force and update positions
        for (int i = 1; i < particles.size(); i++) {
            // Calculate the direction and displacement between two consecutive particles
            Vector2 end2startdirection = Vector2Subtract(particles[i - 1].pos, particles[i].pos);
            float currentlen = Vector2Length(end2startdirection); // Current length of the spring segment
            float displacement = currentlen - restlen;           // Difference from rest length
            float force = k * displacement * deltatime;          // Spring force (scaled by delta time)

            // Normalize the direction and apply the force
            end2startdirection = Vector2Normalize(end2startdirection);
            particles[i].velocity = Vector2Add(particles[i].velocity, Vector2Scale(end2startdirection, force * deltatime));

            // Apply damping to reduce velocity over time
            particles[i].velocity = Vector2Scale(particles[i].velocity, damping);

            // Add gravity to simulate downward force
            particles[i].velocity.y += 10 * deltatime;

            // Update the particle's position
            particles[i].pos = Vector2Add(particles[i].pos, particles[i].velocity);

            // Apply equal and opposite force to the previous particle (if not the first)
            if (i != 1) {
                particles[i - 1].velocity = Vector2Add(particles[i - 1].velocity, Vector2Scale(end2startdirection, -force * deltatime));
                particles[i - 1].velocity = Vector2Scale(particles[i - 1].velocity, damping);
                particles[i - 1].velocity.y += 10 * deltatime;
                particles[i - 1].pos = Vector2Add(particles[i - 1].pos, particles[i - 1].velocity);
            }
        }
    }

    // Draw method to render the spring and particles
    void draw() {
        DrawCircleV(particles[0].pos, 3, WHITE); // Draw the first particle
        // Draw lines connecting particles and the particles themselves
        for (int i = 1; i < particles.size(); i++) {
            DrawCircleV(particles[i].pos, 3, WHITE);               // Draw each particle as a circle
            DrawLineEx(particles[i].pos, particles[i - 1].pos, 2, GREEN); // Draw lines between particles
        }
    }
};

// Main function
int main() {
    // Initialize the Raylib window
    InitWindow(800, 600, "Spring Simulation with Constraints");
    SetTargetFPS(60); // Set the desired frame rate

    // Create a Spring object with 20 particles, rest length of 1.0, and spring constant 500
    Spring spring = Spring(20, 1.0f, 500);
    float damping = 0.95f; // Set damping factor to reduce velocity over time

    // Main game loop
    while (!WindowShouldClose()) { // Loop until the user closes the window
        float deltaTime = GetFrameTime(); // Get the time elapsed since the last frame

        // Check for mouse input
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousepos = GetMousePosition();   // Get the current mouse position
            spring.particles.back().pos = mousepos; // Set the position of the last particle to the mouse position
        }

        spring.update(deltaTime, damping); // Update the spring simulation

        // Start drawing
        BeginDrawing();
        ClearBackground(BLACK); // Clear the screen with a black background

        spring.draw(); // Draw the spring and particles

        EndDrawing(); // End the drawing
    }

    CloseWindow(); // Close the Raylib window
    return 0;
}
