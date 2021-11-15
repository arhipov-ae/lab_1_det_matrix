# Лабораторная работа №1 Архипов А.Е.
Инструкция к запуску узла
Терминал 1:
```
  catkin_make
  roscore
```
Терминал 2:
```
  source devel/setup.bash
  rosrun calculate_determinant server
```
Терминал 3:
```
  source devel/setup.bash
  rosservice call /calcelate_det "matrix: '5 -4 13 16 25 -17 18 -52 -2'" 
```
Терминал 4:
```
  source devel/setup.bash
  rostopic echo topic_det
```
