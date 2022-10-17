# ROS_STM32

We are implementing **serial communication between ROS and STM32** using USART periph.
Please consider checking this tuto which i find for the moment instrtucting and clear : 
**https://www.youtube.com/watch?v=cq0HmKrIOt8&t=692s**

**To be completed with further .IOC file configs**
~on **13.50** : THe old version takes nor argument related to the generated library path however when i tried it it asked for a path.
 the solution fot this is to mention the **output path** for **Inc folder inside Documents/STM32**.~ 
 
 Never mind the path issue just put on a '.' after the command ENJOY ;)
 
 on **15.00** He copied the stm32 geerated file to a shared folder between linux and windows cuz he is using a VM.
 I think it is not necessary if you are working on dual boot or if you install the CUBEIDE on ubuntu.

### Working with CubeIDE :
  If it is your first time working with the IDE you might face some issues such as **arm-none-eabi-gcc: not found** and **unresolved inclusion : stdint**
  the solution is to install the ide from the official st site.
  One other problem I faced : arm-none-eabi-gdb: error while loading shared libraries: libncurses.so.5: cannot open shared object file: No such file or directory.
     **The Solution ** is to run  `sudo apt-get install libncurses5`

## compatibility wela nra ech esmha : 
He is using STM32F446E mcu I am now seeking if there is some hardware dependency or we can use another board.(will be updated soon)
**Quick update** : ~The project was not working on my f410 I thought about some hardaware depedency, I am now tryin on the F411RE (you will be updated very soon about the outcome)~ **the project works fine on my f410**

### checking the **STM32Hardware.h** 
I found that there is a hardawre dependecy but for F4 / F7 / F3 families so i should be fine with my stm32f410 ..(to be verfied) ==> checked !! 

## Working on the project : 
Please consider targetting the project to CPP
     
You have first to put the path for **Inc** inside Documents/STM32 in your stm project.
    
 ~The explicit #include "ros.h" and other .h file wont happen in our main.c however we are calling them on our main.cpp and then calling the functions in main.c~
     
One last thing is to set some __file types__ so please consider following these steps :
       *Project propreties : c/c++ general : file types :
       *check use project type file
       *add *.h and set their type to c++ header files
       *One more last thing if you are actually reading my shit and not wondering about some insta post is that you lust change main.c to main.cpp.
~The code is old so there might be some old HAL API so i ll be checking that also~

One thing we must do is to enable debug to Serial wire

![image](https://user-images.githubusercontent.com/100140668/193890082-99cca3c8-a372-4b45-b42a-0bd2968829a8.png)

We must also set the HSE and LSE to Crystal/Cermaic Resonsator

![image](https://user-images.githubusercontent.com/100140668/193891166-8c50d54f-e393-4a69-98ab-30817e94f2c8.png)

Whe have to add this peace of code to **stm32f4xx_it.h** :
  /* USER CODE BEGIN 0 */
  
  #include "my_main.h"
  
  #ifdef __cplusplus
  
  extern "C" {
  
  #endif
  
  
  
  void USART2_IRQHandler(void)

{

/* USER CODE BEGIN USART2_IRQn 0 */

USART_RX_Callback();

/* USER CODE END USART2_IRQn 0 */

HAL_UART_IRQHandler(&huart2);

/* USER CODE BEGIN USART2_IRQn 1 */

/* USER CODE END USART2_IRQn 1 */

}

/* USER CODE BEGIN 1 */

#ifdef __cplusplus

}


#endif

     
### PATHS and inclusion :
    We have to add the path for Inc Folder of the generated Librairies after running the **make_libraires.py** command.
    
    I am now copying the files as they are from a project i cloned from github : https://github.com/oussemajelassi/rosserial_stm32_NucleoF411
    if it doesn't work i will copy the generated files.
    
    I have a doubt that the port have a mode issue so it cannot be acceced ( will ask sam3oun about it)
    
    
     
## Serial communication :
  In our **Node Handle** we can set input and output buffer size.

## Working on ROS :
  First check which USB PORT is connected which can be done by :
  
  `dmesg | grep tty`
  
  Then clone the ros drivers library by this command : 
  
  `git clone https://github.com/ros-drivers/rosserial.git`
  
  Now copy the rosserial/rosserial_python from the cloned repo to YOUR_WORKSPACE/Src
  
  
  now `catkin_make` in YOUR_WORKSPACE
  
  now we should source the devel/setup.bash : 
  
  `source devel/setup.bash`
 
 Finally we init the communication : 
 
 `rosrun rosserial_python serial_node.py /dev/ttyACM0`
I faced an issue : Unable to sync with device; possible link problem or link software version mismatch such as hydro rosserial_python with groovy Arduino

Most of the answers are talking about cross checkinh the baudrate that did not solve the issue, I am now trying to lower baudrate : 9600

## troubleshooting :
I found this tuto i will follow it i dunno what went wrong :

https://sudonull.com/post/31955-Rosserial-STM32

There is one problem I faced is that rosrun wont rechon rosserial_stm32 as a package so the solution for that is to `source ~/catkin_ws/devel/setup.bash` after compiling the package.
