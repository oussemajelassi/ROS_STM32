# ROS_STM32

We are implementing **serial communication between ROS and STM32** using USART periph.
Please consider checking this tuto which i find for the moment instrtucting and clear : 
**https://www.youtube.com/watch?v=cq0HmKrIOt8&t=692s**


on **13.50** : THe old version takes nor argument related to the generated library path however when i tried it it asked for a path.
 the solution fot this is to mention the **output path** for **Inc folder inside Documents/STM32**. 
 
 Never mind the path issue just put on a '.' after the command ENJOY ;)
 
 on **15.00** He copied the stm32 geerated file to a shared folder between linux and windows cuz he is using a VM.
 I think it is not necessary if you are working on dual boot or if you install the CUBEIDE on ubuntu.

### Working with CubeIDE :
  If it is your first time working with the IDE you might face some issues such as **arm-none-eabi-gcc: not found** and **unresolved inclusion : stdint**

## compatibility wela nra ech esmha : 
He is using STM32F446E mcu I am now seeking if there is some hardware dependency or we can use another board.(will be updated soon)

### checking the **STM32Hardware.h** 
I found that there is a hardawre dependecy but for F4 / F7 / F3 families so i should be fine with my stm32f410 ..(to be verfied)

## Working on the project : 
Please consider targetting the project to CPP
     
You have first to put the path for **Inc** inside Documents/STM32 in your stm project.
    
 ~~ The explicit #include "ros.h" and other .h file wont happen in our main.c however we are calling them on our main.cpp and then calling the functions in main.c ~~ 
     
One last thing is to set some __file types__ so please consider following these steps :
       *Project propreties : c/c++ general : file types :
       *check use project type file
       *add *.h and set their type to c++ header files
       *One more last thing if you are actually reading my shit and not wondering about some insta post is that you lust change main.c to main.cpp.
     
### PATHS and inclusion :
    We have to add the path for Inc Folder of the generated Librairies after running the **make_libraires.py** command. 
     
## Serial communication :
  In our **Node Handle** we can set input and output buffer size.
