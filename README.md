# philosophers
Projet 42 multi threading (tourne sous VM - Linux Ubuntu)

### Compiler
puis exécuter les commandes sous les répertoires respectifs :
- ./philo_one 5 800 200 200 [10] (nb de philo, time to die, time to eat, time to sleep, [nb de repas par philo])
- ./philo_two 5 800 200 200 [10]
- ./philo_three 5 800 200 200 [10]

### Compiler avec gdb :
- mettre -g3 dans les flags du make file
- compiler
- executer avec la cmd suivante :
```gdb --args ./philo_one 3 5000 300 300 4```
```run```
- en cas de problème, taper :
```backtrace```

### Lancer avec valgrind :
```valgrind --leak-check=yes ./philo_one 3 500 300 300 4```