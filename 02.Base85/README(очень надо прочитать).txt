# Base85 Encoder / Decoder

## Описание

Программа реализует кодирование и декодирование данных в формате Base85.

Поддерживаются два режима работы:
- `-e` — кодирование (encode)
- `-d` — декодирование (decode)


---

## Запуск

Программа запускается с аргументами:

- Кодирование:

base85.exe -e


- Декодирование:

base85.exe -d


Пример:

echo hello | base85.exe -e
echo Xk~0{Zv | base85.exe -d


---

## Тестирование

Проверяется:
- корректность encode/decode
- работа с пустыми данными
- работа с бинарными данными
- обработка ошибок
- round-trip тесты (encode → decode)

Все тесты успешно проходят:


[ PASSED ] 8 tests.


## Режимы сборки

В проекте есть два режима: запуск программы и запуск тестов.  
Они используют разные точки входа (`main`), поэтому не могут собираться одновременно.

### Режим программы

- `base85.cpp` — Include in Build  
- `base85ed.cpp` — Include in Build  
- `base85ed_test.cpp` — Exclude from Build  

Используется для запуска с аргументами `-e` и `-d`.


### Режим тестов

- `base85.cpp` — Exclude from Build  
- `base85ed.cpp` — Include in Build  
- `base85ed_test.cpp` — Include from Build  

Используется для запуска unit-тестов.

