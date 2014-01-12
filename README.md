CatchMe
=======

Can you catch Oussama ? I wish I could.

To run the game correctly, you must be in the same directory ("./CatchMe") as the conf.xml.

This project requires the following dependencies to be installed on your system:
libboost-all-dev

A simple apt-get install should suffice, provided that you are running on a Debian-like distribution.

Due to the broken computer setups that you might be working on (-> IUT), you'll need to download the cmake .tgz file from CMake official site, the GCC package from Casali's website and use the parameters found for GCC in the 'alias' file to setup GCC in CMakeLists at the root of the project.
Should this not work for you, feel free to contact me at florandara@gmail.com for further information.
For information, I did manage to have it build and run on a computer at the IUT.

We processed to test our code by trying to identify all the corner cases. We then wrote them down and etablished a procedure to test each of them for each commit. Two persons who hadn't worked on the commit would test the changes in all the possible ways they could.

Features
========

- Menu system
- Modular game mode system, allowing creation of new different game modes easily
- Classic game mode containing:
  - Free for All starting from 1 (vs bot) player up to 4 players.
  - Teams (2v2)
  - Endurance trial (3v1 with 4 rounds, rotating single player, player with most turns alive win)
  - Obstacles (loaded from file)
- Survivor (Tron-like) game mode type, offering the same possiblities as the Classic game mode but squares that have already been walked on are now unusable.
- Map editor, allowing to position the obstacles for each map size and saving them.
- Non-canonical timed input (using TermCap and poll)
- XML Configuration file
- C++11 features (lambdas, foreach, function pointers)
 
Learning log
============

- Github account creation, mastering basic github operations such as pull, commit, add, push, reset
- std::function, function pointers C++11 style, used for modular game modes
- std::map, associative container
- this_thread::sleep and std::chrono, for error display times...
- Structs (C style, not OOP)
- Strongly-typed enums
- static_cast
- operator << overload (console colors)
- C++11 lambda functions for menu callbacks
- KDevelop IDE (Find usages, go to definition etc) and CMake
- Terminal manipulation via TermiOS/TermCAP for non-canonical input
- Terminal manipulation VT100 for colors and clear screen
- Terminal manipulation via ioctl for term size
- poll for timed out blocking input
- A* (simplified) pathing algorithm
- std::set


  
