# Лабораторная работа №7

## Задание 1

### Необходимые знания

1. Компиляция программ на языке С.
>>Расмотренно в предыдущих лабах
2. Аргументы командной строки.
>>Расмотренно в предыдущих лабах
3. Протокол TCP.
>>Расмотренно в предыдущих лабах
4. Протокол UDP.
>>Расмотренно в предыдущих лабах
В этой лабораторной работе вам предстоит потрогать два клиент-серверных приложения. Первое использует проткол TCP, второй UDP. Вам необходимо:

* Скомпилировать все четыре программы.
* Вынести все константы (объявленные через `#define`) в аргументы командной строки.
* Скомпилировать оба приложения через makefile.

## Задание 2

Ответить на следующие вопросы:

1. Что делают оба приложения?

>tcp-версия отправляет на сервер сообщение, которое сервер выводит в консоль

>udp-версия отправляет сообщение на сервер, сервер выводит его в консоль и отправляет этот же текст клиенту


2. Что произойдет, если tcpclient отправит сообщение незапущенному серверу?

> Не установлено соединение. tcpclient не сможет отправить незапущенному. 

3. Что произойдет, если udpclient отправит сообщение незапущенному серверу? 

>Клиент будет ждать ответ

4. Что произойдет, если tcpclient отвалится во время работы с сервером?

>Сервер продолжит работу

5. Что произойдет, если udpclient отвалится во время работы с сервером?

>Сервер продолжит работу

6. Что произойдет, если udpclient отправит сообщение на несуществующий / выключенный сервер?

>Клиент будет ждать ответ

7. Что произойдет, если tcpclient отправит сообщение на несуществующий / выключенный сервер?

> Не установлено соединение. tcpclient не сможет отправить несуществующему / выключенному серверу, 


8. В чем отличия UDP и TCP протколов?
>>Расмотренно в предыдущих лабах (lab6)

## Перед тем, как сдавать

Залейте ваш код в ваш репозиторий на GitHub. Убедитесь, что вы не добавляете в репозиторий бинарные файлы (программы, утилиты, библиотеки и т.д.).
