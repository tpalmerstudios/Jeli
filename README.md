# Jeli
A first-person game engine for the beginning developer

## Installation
0. Clone this repository
1. Download SDL2 for your system.
2. Clone https://github.com/nothings/stb into the empty stb directory
3. make

Based on ssloy/tinyraycaster. I probably should've forked it or something, but at this point the code is drastically changed. In addition while it says initial commit, this is by no means the first changes I've done.I've been steadily working through his tutorial and recently have actually been adding features. My goal is to make it able to draw several shapes. Circle, Triangle, Cubes, and maybe ovals. In addition I want to rework the map system to allow for higher pov or lower. And possibly every single item having an altitude variable as well as an angle. I have started by adding a horizon variable that is used instead of just splitting the screen in half.My next step will probably be adding a jump action that will respond to SPACE. And lower the horizon 10% of screen height. This is not a great readme, but it allows me to figure out what I need to do next.

***Step 1 - Shape rendering***  
	~Rectangle~  
	~Circle~  
	Triangle (got the outline down, now to fill it) and then create a converter func that does basic trig. 2 sides and angle, etc.  
	Cubes (not sure what exactly to do here)  
	ovals (again how do expand one side, must research)  

***Step 2 - Overlay rework***  
	Render function should not do anything except call functions  
		(drawSky (); drawGrass (); drawBuilding (); drawActors (); drawMap (); drawPauseMenu ();)  
	~Make my cool sprite color editor game wide in a overlay function~

***Step 3 - Add altitude***  
	Every item gets altitude float  
	Every texture gets a x, y, and z column. My ray caster will have to be reworked  
	Horizon can move (someday allow for angles.) Horizon height and angle if head is tilted  
	This is a huge! overhaul. Jumping might be easy. But adding in z columns is big  
	And the logic behind it could be rather complex. This is what takes a 2D game to 3D  

***Step 4 - Actor rework***  
	Actors (monsters or players) should be 3D. They should have an angle and an altitude.  
	Textures need to be redone, but probably with this work, I'll have to go with a totally new way of doing these textures

***Step 5 - Map rework***  
	I will need to store all of this data somehwere in a concise manner. Each object can be responsible for its own x, y, z, angle but the map will need to be searched for the closest 20 squares or something  
	Render the minimap based on that with trees and and water and whatever else is in the map.
	Then render the ground up to the horizon adding on water and trees based on distance (3D formula for distance now) first then altitude
	Each individual object is painted with texture after base shape is made then move to the next closest one

***Step 6 - Movement rework***
	Nuf said. This is like a year a way at the soonest lol
