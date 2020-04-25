#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "revert_string.h"

int main(int argc, char *argv[])
{
    //Проверка числа аргуметов командной строки (включая имя программы)
	if (argc != 2)
	{
		printf("Usage: %s string_to_revert\n", argv[0]);  //Печать имени файла
       
		return -1;//Завершение работы программы
	}

	char *reverted_str = malloc(sizeof(char) * (strlen(argv[1]) + 1)); // выдеоение памяти размером "число символов в строке" + 1)
	strcpy(reverted_str, argv[1]); //крпмрование строки

	RevertString(reverted_str);//вызов функции, которая "переворачивает" слово

	printf("Reverted: %s\n", reverted_str); //Печать результирующей строки
	free(reverted_str);//очищение памяти
	return 0;
}

