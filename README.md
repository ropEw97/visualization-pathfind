This project covers the characteristics of different pathfinding algorithms.
The user can design a map (which includes adding obstacles, start and end points) and 
then observe how a given algorithm constructs a path.




## Running the application:

1. Make sure you have Qt Creator v5.0 (or greater) installed.

2. Clone this project.

3. Go to the project root folder, find .pro file and open it with Qt Creator.

4. Click the big green button in the lower left corner of the screen that says "Run".




## Usage:

- First add start and target marks by clicking the appropriate buttons.

- You can move start and target marks around the map by dragging them.

- After start and target marks are added, you can add obstacles by selecting the
desired type from the drop down menu and clicking (or holding) left mouse button on the map.

- The obstacles can be deleted by double clicking on them.

- You can also generate a maze using one of the available algorithms.

- It is possible to save the map to a file (you can save it as .txt), and later load it from that file.

- After the map is set (at least start and target) you can start one of the pathfinding algorithms.

- After the algorithm has finished, first the sequence of nodes in order in which the algorithm 
processed them and then the final path (if found) is drawn.

- You can save the image of the found path **(just be sure to save it as .png file)**.

- Before you can do anything to the map, you must clear the path that is drawn (or the entire map).
# visualization-pathfind
