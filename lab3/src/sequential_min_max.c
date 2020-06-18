#include <stdio.h>
#include <stdlib.h>

#include "find_min_max.h"
#include "utils.h"

int main(int argc, char **argv) {
//проверка кол-ва аргументов 
  if (argc != 3) {
    printf("Usage: %s seed arraysize\n", argv[0]);
    return 1;
  }
//проверка для генерации пвседослучайного числа > 0
  int seed = atoi(argv[1]);
  if (seed <= 0) {
    printf("seed is a positive number\n");
    return 1;
  }
//проверка длины массива 
  int array_size = atoi(argv[2]);
  if (array_size <= 0) {
    printf("array_size is a positive number\n");
    return 1;
  }
//выделение памяти для массива
  int *array = malloc(array_size * sizeof(int));
//заполнение массива псевдослучайными числами 
  GenerateArray(array, array_size, seed);
//поиск min и max
  struct MinMax min_max = GetMinMax(array, 0, array_size);
//освобождение памяти 
  free(array);
//вывод результата
  printf("min: %d\n", min_max.min);
  printf("max: %d\n", min_max.max);

  return 0;
}