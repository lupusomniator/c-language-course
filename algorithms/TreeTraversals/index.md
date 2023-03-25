# **Обходы дерева (Tree traversals)**

***Обход дерева*** — вид обхода графа, обусловливающий процесс посещения каждого узла структуры дерева данных ровно один раз.
Обход дерева используется для оптимального поиска необходимого элемента в дереве.
Для этого нужно обойти все элементы этого дерева. 

В отличие от графа, дерево не содержит циклов. Число рёбер в дереве на единицу меньше числа вершин, а между любыми парами вершин имеется один и только один путь.

____

*Узел дерева можно описать как структуру:*
```
struct TNode {
    struct TNode* Left;
    struct TNode* Right;
    int Value;
};
```
## **Обход дерева в глубину (Depth-first search, DFS)**

Существует три способа обхода дерева в глубину, различающихся порядком посещения вершины и ее сыновей. Они производятся рекурсивно либо с использованием стека.
____

#### **1. Префиксный обход (Обход в прямом порядке или Pre-order Traversal)**

Является одним из наиболее часто используемых алгоритмов обхода дерева. Такой обход производится сверху вниз. 
Это тип обхода, при котором сначала посещается корневой узел, затем левое поддерево, а затем правое поддерево.


В качестве примера рассмотрим вот такое дерево: 

![Tree](https://github.com/lyttiii/c-language-course/blob/main/Дерево.png)

На выходе мы должны получить последовательность вида:  *20 9 7 11 25 22 31*

 
Реализация через **стек** выглядит следующим образом:
 
```
// Определение структуры для стека
struct Stack {
    struct TNode** array;
    int top;
    int capacity;
};
```
```
// Создание нового стека
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (struct TNode**)malloc(capacity * sizeof(struct TNode*));
    return stack;
}
```
```
// Добавление элемента в стек
void push(struct Stack* stack, struct TNode* node) {
    stack->array[++stack->top] = node;
}
```
```
// Извлечение элемента из стека
struct TNode* pop(struct Stack* stack) {
    return stack->array[stack->top--];
}
```
```
// Проверка, пуст ли стек
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}
```
```
// Обход дерева
void preOrder(struct TNode* root) {
    if (root == NULL) {
        return;
    }

    struct Stack* stack = createStack(100);
    push(stack, root);

    while (!isEmpty(stack)) {
        struct TNode* currentNode = pop(stack);
        printf("%d ", currentNode->Value);

        if (currentNode->Right != NULL) {
            push(stack, currentNode->Right);
        }

        if (currentNode->Left != NULL) {
            push(stack, currentNode->Left);
        }
    }
}
```
```
// Создание нового узла
struct TNode* createNode(int value) {
    struct TNode* node = (struct TNode*)malloc(sizeof(struct TNode));
    node->Value = value;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}
```
```
int main() {
    // Создание дерева
    struct TNode* root = createNode(20);
    root->Left = createNode(9);
    root->Right = createNode(25);
    root->Left->Left = createNode(7);
    root->Left->Right = createNode(11);
    root->Right->Left = createNode(22);
    root->Right->Right = createNode(31);

    printf("\nThe Preorder traversal -\n");
    preOrder(root);

    return 0;
}
```

**Рекурсивный спуск:** 

```
void printPreorder(struct TNode* node) {
    if (node != NULL) { // Проверяем, не является ли текущий узел пустым.
        printf("%d ", node->Value); // Показываем поле данных корня (или текущего узла).
        printPreorder(node->Left); // Обходим левое поддерево рекурсивно, вызвав функцию прямого обхода.
        printPreorder(node->Right); // Обходим правое поддерево рекурсивно, вызвав функцию прямого обхода.
    }
}
```

#### **2. Инфиксный обход (Симметричный обход или InOrder Traversal)**
 
 Такой обход производится слева направо. Сначала посещается левое поддерево, затем корневой узел и, наконец, правое поддерево. 
 Инфиксный обход можно использовать для решения многих задач, таких как поиск k-го элемента в дереве или печать всех элементов дерева в отсортированном порядке.
 Рассмотрим все то же дерево: 
 
 ![Tree](https://github.com/lyttiii/c-language-course/blob/main/Дерево.png)

 
Мы получаем такую последовательность: *7 9 11 20 22 25 31*


**Рекурсивный спуск:**

```
void printInOrder(struct TNode* node) {
    if (node != NULL) { // Проверяем, не является ли текущий узел пустым.
        printInOrder(node->Left); // Обходим левое поддерево рекурсивно, вызвав функцию симметричного обхода.
        printf("%d ", node->Value); // Показываем поле данных корня (или текущего узла).
        printInOrder(node->Right); // Обходим правое поддерево рекурсивно, вызвав функцию симметричного обхода.
    }
}
```
 
#### **3. Постфиксный обход (Обход в обратном порядке или Post-order traversal)**
Такой обход производится снизу вверх. Корень дерева посещается после его поддеревьев. 
Сначала посещается левое поддерево, затем правое поддерево, а после корневой узел. Может использоваться для удаления дерева.

![Tree](https://github.com/lyttiii/c-language-course/blob/main/Дерево.png)

После такого обхода мы получим: *7 11 9 22 31 25 20*

**Рекурсивный спуск:**

```
void printPostOrder(struct TNode* node) {
    if (node != NULL) { // Проверяем, не является ли текущий узел пустым.
        printPostOrder(node->Left); // Обходим левое поддерево рекурсивно, вызвав функцию обратного обхода.
        printPostOrder(node->Right); // Обходим правое поддерево рекурсивно, вызвав функцию обратного обхода.
        printf("%d ", node->Value); // Показываем поле данных корня (или текущего узла).
    }
}
```

## **Обход дерева в ширину (Breadth-first search, BFS)**
Обход в ширину подразумевает, что сначала мы посещаем корень, затем, слева направо, все ветви первого уровня, затем все ветви второго уровня и т.д.
Такой обход производится с помощью очереди.

![Tree](https://github.com/lyttiii/c-language-course/blob/main/Дерево1.png)

Получаем: *20 9 25 7 11 22 31*

*Рассмотрим, как работает очередь:*

Сначала посетим корень. Сейчас он находится в очереди
![Tree](https://github.com/lyttiii/c-language-course/blob/main/Queue1.jpg)

Печатаем 20, и, так как этот корень имеет детей, поместим их в очередь (9 и 25 соответственно). Важно, что мы сначала рассматриваем первый уровень, и не спускаемся ниже!
Когда узел находится в начале очереди, мы должны проверить, есть ли у него правый и левый потомки. Если такие имеются, то добавляем их в очередь.
![Tree](https://github.com/lyttiii/c-language-course/blob/main/Queue3.jpg)

У 9 есть потомки 7 и 11, и мы поместили их в очередь:

![Tree](https://github.com/lyttiii/c-language-course/blob/main/Queue4.jpg)

У 25 есть потомки 22 и 31, добавим их :)

![Tree](https://github.com/lyttiii/c-language-course/blob/main/Queue5.jpg)

7, 11, 22 и 31 являются листьями нашего дерева (у них нет потомков), поэтому мы просто последовательно выводим их:

![Tree](https://github.com/lyttiii/c-language-course/blob/main/Queue6.jpg)

![Tree](https://github.com/lyttiii/c-language-course/blob/main/Queue7.jpg)






