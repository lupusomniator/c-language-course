# Массивы в языке Си
Нередко возникает необходимость работы не с одиночными данными, а с наборами данных. И для этого в языке Си применяются *массивы*. В этой статье мы рассмотрим основные аспекты работы с массивами, включая многомерные массивы, индексацию, распределение памяти, связь с указателями и инициализаторы массивов.
## Определение
**Массив** — это непрерывный участок памяти, содержащий последовательность объектов одинакового типа, обозначаемый одним именем. Объявление массива выглядит следующим образом:
```
// тип_переменной название_массива [длина_массива]

int cake [4]; /* массив из 4 значений типа int */
char cookies [12]; /* массив из 12 значений типа char */
float candies [50]; /* массив из 50 значений типа float */
```
Квадратные скобки ([ ]) свидетельствуют о том, что cake и другие такие же структуры данных являются массивами, а число, заключенное в квадратные скобки, задает количество элементов в массиве. 
## Многомерные массивы
Наряду с одномерными, существуют и *многомерные массивы*. Они представляют собой массивы, содержащие другие массивы в качестве элементов. Они позволяют организовать данные в виде таблицы или матрицы. Например, двумерный массив может использоваться для представления шоколадки, где каждая ячейка содержит информацию о кусочке на данной позиции. Размерность массива может быть и больше: трёхмерные, четырёхмерные и т.д. Синтаксис остаётся прежним, добавляется только новая размерность:
```
// тип_переменной название_массива [размерность 1] [размерность 2] … ;
int chocolate [5][3]; 
```
## Индексация многомерных массивов 
Чтобы получить доступ к элементам массива, вы должны указать отдельный элемент, используя для этой цели его номер, который также называется *индексом*. В качестве индекса может использоваться любое выражение, выдающее значение целого типа: char, short, int, long. Индексы элементов массива начинаются с 0 (а не с 1) и индекс последнего элемента из length элементов – это length-1 (а не length). Следовательно, `cookies [0]` — это первый элемент массива, а `cookies [11]` - 12-й, он же последний, элемент массива.

*Индексация* в многомерных массивах осуществляется путем указания значения каждого измерения в квадратных скобках. Например, для доступа к элементу двумерного массива по координатам (x, y) используется следующий синтаксис: `chocolates [x][y]`.
## Распределение памяти в многомерных массивах 
Для хранения многомерного массива выделяется единый блок памяти необходимого размера: 
```
// размерность_1 * размерность_2 * ... * размерность_N * sizeof (тип_элемента_массива)
```
Значения элементов массива хранятся в памяти друг за другом в порядке возрастания индексов. Например, для двумерного массива элементы располагаются в следующем порядке:
```
chocolates [0][0], chocolates [0][1], chocolates [0][2], chocolates [1][0], chocolates [1][1], chocolates [1][2] и т.д.
```
Для трехмерного массива элементы располагаются в порядке следования индексов i, j, k.
## Связь понятия указателя и массива 
Массивы и указатели тесно связаны друг с другом. Фактически, имя массива может рассматриваться как указатель на его первый элемент. Например, если у нас есть массив ``candies, то `candies` можно рассматривать как указатель на `candies [0]`. 
Также возможно получить указатель на элемент массива по индексу. Например, для двумерного массива ``chocolates можно объявить указатель на первый элемент следующим образом: 
```
int *p = & chocolates [0][0].
```
Это связано с тем, что элементы массива располагаются в памяти последовательно.
## Инициализаторы массивов
**Инициализаторы массивов** — это способ задания начальных значений для элементов массива при его объявлении. Они представляют собой список значений, заключенных в фигурные скобки и разделенных запятыми.
Например, для объявления одномерного массива cake размером 4 и его инициализации можно использовать следующий код: 
```
int cake [4] = {1, 2, 3, 4};
```
Для двумерного массива chocolates размером 5 на 3:
```
int chocolates [5][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}};
```
Если количество элементов в инициализаторе меньше, чем размер массива, оставшиеся элементы будут инициализированы нулевыми значениями. Если же количество элементов превышает размер массива, компилятор выдаст ошибку.

В заключение можно сказать, что многомерные массивы – это мощный инструмент в программировании. Они позволяют хранить и обрабатывать большие объемы данных. При работе с многомерными массивами необходимо учитывать особенности индексации и распределения памяти. Также полезно знать о связи понятия указателя и массива и использовании инициализаторов массивов.