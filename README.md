
# CS:GO Reverse Engineering

Reverse engineering of Counter-Strike: Global offensive and external memory modification.




## Features

- Bunnyhop
- Triggerbot



## TO-DO

- [ ]   Add better console logger (colors, output types, timestamps) 
- [ ]   Use ReadProcessMemory sub-function (NtRVM) to improve speed (by 5.56%) 
- [ ]   Read entire player struct once per loop instead of reading each variable individually
- [ ]   Sync loop execution with game engine tick updates (run code once per tick)
- [ ]   Remove WriteProcessMemory (emulate keyboard and mouse input)
- [ ]   Impliment polymorphism
