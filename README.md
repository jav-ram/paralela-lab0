# paralela-lab0
Para compilar el código:

Este ejecuta el código serial con el paralelo e imprime sus tiempos.
```zsh
$ g++ -o parallel parallel.cpp -lpthread -fpermissive

$ ./parallel
```

Este ejecuta el paralelo de N = 0 hasta N = 10 para hacer las pruebas
```zsh
$ g++ -o main main.cpp -lpthread -fpermissive
$ ./main
```