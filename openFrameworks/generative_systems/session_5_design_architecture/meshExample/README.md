# Generative Systems
Generative Systems for Art and Design course materials
 daniel buzzo 2020
 buzzo.com

## session 5

#Mesh, noise and perlin noise Example

Simple example to
• generate an openFrameworks (openframeworks.cc) mesh object
• use ofEasyCam to view our 3D scene
• populate it with vertices
• triangulate vertices and add indices to create triangle mesh
• use ofRandom() function to change the vertices z co-ordinates to distort the Mesh
• use 2 dimensional Perlin Noise() function to change the vertices z co-ordinates to distort the Mesh
 
##key controls
• f: toggle full screen 
• spacebar: random z-value in meshvertices
• w: draw wireframe or point cloud 
• p: use PerlinNoise for z-value in meshvertices
• Up-key Down-key: increase/decrease PerlinNoise input range 
• Right-key Left-key: increase/decrease amplitude of Perlin Noise distortion 
• click and drag in window to move camera


![screenshot](screenshotMeshExample.png)

