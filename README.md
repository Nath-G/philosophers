# philosophers

### compiler avec gdb :
- mettre -g3 dans les flags du make file
- compiler
- executer avec la cmd suivante :
```gdb --args ./philo_one 3 5000 300 300 4```
```run```
- en cas de problème, taper :
```backtrace```
```valgrind --leak-check=yes ./philo_one 3 5000 300 300 4```

usleep( 5 * ((phi->id + 1) % 2));
