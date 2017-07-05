# Push Box 0.0.2
## Author: Raymond.Lx
It's a windows console game without graphics but char.
However,it may be funny i think.

Note that,it has used a lib which provides the function about windows console and which was written by me as well XD.
Although it's not very high-tech but that's all I can do(I don't even know what I'm saying).

So,enjoy it or improve it whatever you like (or dislike...)

-----Raymond.Lx 2017.7.3

#How to make a level?
Firstly,create a txt file and write with
4 ----- means that the level number is 4
60000 ------ means that the level has only 60000ms to finished
XXXXXXXXXXXXXXX
X             X
X  O    # #   X
X       @O@O  X
X @     ###  TX
XXXXXXXXXXXXXXX

'X' stands for the edge of map
' ' stands for none
'O' stands for target
'@' stands for box
'#' stands for wall
'T' stands for spawn point

Once you have done this,then drag the file into push_box_level_maker.exe which is in res/levels 
And it would produce a .json file.
In the end,you need to change the option in res/game_cfg.json "max_level" to the number your level is.

Enjoy it! :)
-------Raymond.Lx 2017.7.6
