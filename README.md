# Лабораторная работа №1 Архипов А.Е.
Инструкция к запуску узла

Терминал 1: Сборка проекта и запуск сервера мастера
```
  catkin_make
  roscore
```
Терминал 2: Запуск узла server из пакета calculate_determinant
```
  source devel/setup.bash
  rosrun calculate_determinant server
```
Терминал 3: Вызов сервиса calcelate_det
```
  source devel/setup.bash
  rosservice call /calcelate_det "matrix: '5 -4 13 16 25 -17 18 -52 -2'" 
```
Терминал 4: Для просмотра сообщения в топике можно вызвать команды
```
  source devel/setup.bash
  rostopic echo topic_det
```
