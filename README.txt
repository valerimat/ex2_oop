================================== EX02-OOP ===================================

 (        )  (            (              )     )       (     
 )\ )  ( /(  )\ )         )\ )        ( /(  ( /(       )\ )  
(()/(  )\())(()/(   (    (()/(    (   )\()) )\()) (   (()/(  
 /(_))((_)\  /(_))  )\    /(_))   )\ ((_)\ ((_)\  )\   /(_)) 
(_))    ((_)(_))_  ((_)  (_))  _ ((_) _((_) _((_)((_) (_))   
| |    / _ \ |   \ | __| | _ \| | | || \| || \| || __|| _ \  
| |__ | (_) || |) || _|  |   /| |_| || .` || .` || _| |   /  
|____| \___/ |___/ |___| |_|_\ \___/ |_|\_||_|\_||___||_|_\  
                                                            

name: Valeri Materman
id: 321133324
name: David Yudin
id: 321893257

===============================================================================
In this exercise we were asked to implement Lode Runner inside the console with
the signs bellow:
enemy  - %
player - @
poles  - -
ladder - H
coins  - *
wall/floor - #
player on ladder - S

Movement:
You will be moving using the arrow key.
pressing esc will exit the game.

There is no jumping the only way to move up is by ladders!
if you will fall down you wont be able to move untill you reach pole/floor.

Lives:
You are starting with 3 hp each death will dercrease your hp by 1.
if you reach 0 hp you will loose the game.

Points:
each coin collected will up your score by 2*(LVL_NUMBER).
each completer level will give you 50*(LVL_NUMBER) points.

===============================================================================
More tehnical stuff:

classes and theyr uses:

---------main objets:
_________game_handler.cpp + .h_________
will run the game. you need to build this game object with a board.txt file 
then you can use Run_game function to run the game.
the game handler runs the game moves the enemy and player etc...

_________board.cpp + .h_________
will store bord. levels, and all the helping functions to handle them

---------game objects:

_________enemies.cpp + .h_________
stores the propreties of a given mosnter- 
where its located, what sign it ate before, its next step etc..

_________score.cpp + .h_________
stores the curr score and handels it

_________player.cpp + .h_________
stores player location, score, lives and handles them


_________coin.cpp + .h_________
store location of coins and handles them

---------helpers:
_________macros.cpp + .h_________
stores consts , enums etc

_________location.cpp + .h_________
stores the location of all wanted objects

_________io.cpp + .h_________
handels keypress

---------algorithms:
_________alphastar.cpp + .h_________
finds the fastests root to the player based on A* algoritm - explainde bellow

_________tiles.cpp + .h_________
helps the alphastar algo by deviding the map to tiles, each tile has its score
its char and its location

===============================================================================
Agoithms:
_________A*:
for enemy moves we use the A* algorithm for finding the shortes path to our player
also we implement smartness to enemy - a random number that sets after how many player
moves the algorith will calculate the path.

The algorithm for finding path:
1.we create two lists open and closed
2.at first the open lists contaions our curr location (from where we want to move)
3.we get all the possible moves around the moster

4.we calculate theyr score:
h_value= how far are they from the from position
g_value = how far are they from the to position (with manhattan algorithm ( x + y))
f_value = g + h.

5.we add them to open list
if a tile already in the open list we adjust theyr score and theyr father

6.we find the tile with the best score in the open list and move it to the closed list
if we have 2 tiles with same score we take the one recently added

7.we check if we reached our player
if yes we output a path based on the tile fathers (the tile it came form)
if no we return to step 3 this time with the last tile in the closed list.


enjoy the game :)


