
## Список как линейная структура данных
Список - структура данных (СД), представляющая собой связную цепочку блоков, каждый из которых хранит в себе полезную нагрузку и каким-либо образом ссылается на следующий блок. Наглядная бытовая иллюстрация списка - поезд. В каждом вагончике едут пассажиры - полезная нагрузка, - каждый вагончик связан с другим (в данном случае получается двусвязный список, так как из каждого вагона, кроме хвостового и головного, возможно двигаться в обе стороны). А алгоритм проверки билетов у пассажиров в точности соответствует обходу списка - от головы к следующему, пока не найдётся безбилетник или пока состав не кончится. 
<p align="center">
<img src="images/train.jpg" alt="Аналогия устройства списка" title="Паровозик из Ромашкова">
</p>

Примерный код, иллюстрирующий вышесказанное:
```c++
#incldue <stdio.h>
#incldue <stdlib.h>

struct TCostomContent {
	// TODO: Imp
}
typedef struct TCustomContent TCustomContent;

struct TListNode {
	TCostomContent Content;
	struct TListNode* Next;
}
typedef struct TListNode TListNode;

struct TList {
	TListNode* Head;
}
typedef struct TList TList;
```

В данном случае работа со структурой разделяется на интерфейсы взаимодействия с целым списком и с узлом списка в отдельности. Таким образом мы защищаем нашу структуру от доступа к произвольному месту списка (АХАХА, безопасность в Си, АХАХА). То есть функции доступа к списку определены только для головы списка, что почти всегда гарантирует упрощение кода. 
Основные операции над односвязным списком: 
1. Инициализация списка
2. Добавление  узла
3.  Поиск узла по значению
4. Удаление узла
Представляю Вашему вниманию реализацию этих операций для нашей структуры:

```c++
TList* InitList() {
	/*
	Инициализация осуществляется за O(1)
	*/
	TList* newList = calloc(1, sizeof(TList));
	assert(newList);
	return newList;
}

void Append(TList* list, TCustomContent content) {
	/*
	Вставка осуществляется за O(n)
	*/
	assert(list);
	// Реализацию функции InitListNode предоставляю читателю
	// в качестве несложного упражнения
	TListNode* newNode = InitListNode(content);
	if (!list->Head) {
		list->Head = newNode;
		return;
	}
	TListNode* currNode = list->Head;
	while (currNode && currNode->Next) {
		currNode = currNode->Next;
	}	
	currNode->Next = newNode;
}

TListNode* Find(TList list, TCustomContent content, 
		  int(*IsEqual)(TCustomContent content1, TCustomContent content2)) {
	/*
	Поиск осуществляется за O(n)
	*/
	TListNode* ret = NULL;
	if (list.Head) {
		TListNode* currNode = list.Head;
		while (currNode) {
			if (IsEqual(currNode->Content, content)) {
				ret = currNode;
				break;
			}
			currNode = currNode->Next;
		}
	}
	return ret;
}

int Delete(TList* list, TCustomContent content,  
		   int(*IsEqual)(TCustomContent content1, TCustomContent content2)) {
	/*
	Удаление осуществляется за O(n)
	*/
	int ret = EXIT_FAILURE;
	assert(list);
	TListNode* toDel = NULL;
	if (list->Head) {
		if (IsEqual(list->Head->Content, content)) {
			ret = EXIT_SUCCESS;
			toDel = list->Head;
			list->Head = list->Head->Next;
		}
		TListNode* currNode = list.Head;
		while (currNode && currNode->Next) {
			if (IsEqual(currNode->Next->Content, content)) {
				toDel = currNode->Next;
				currNode->Next = currNode->Next->Next;
				ret = EXIT_SUCCESS;
				break;
			}
			currNode = currNode->Next;
		}
	}
	if (toDel) {
		// Чистим пользовательский контент в узле, мало ли что там хранится 
		FreeListNode(toDel);
		free(toDel);
	}
	return ret;
}
```

В глаза сразу бросается ряд неудобностей - итерироваться по списку можно только в одном направлении, произвольного доступа по индексу или значению за O(1) или хотя бы за O(log(n)) не предусмотрено производителем, и вообще, что Вы хотите, список - линейная СД. Но есть пару фишечек для ускорения работы. Так, например, вместе с "головой" списка допустимо хранить указатель на конец (почти очередь получается), тогда вставка будет происходить за O(1). Если же в каждом узле помимо указателя на следующий узел хранить указатель на предыдущий, то есть на родителя, то код функции удаления засчёт переиспользования функции поиска укорачивается до 15 строк и становится внятнее:

```c++
int Delete(TList* list, TCustomContent content,
           int(*IsEqual)(TCustomContent content1, TCustomContent content2)) {
	int ret = EXIT_FAILURE;
	assert(list);
	TListNode* toDel = Find(list, content, IsEqual);
	if (toDel) {
		ret = EXIT_SUCCESS;
		if (toDel->Parent) {
			toDel->Parent->Next = toDel->Next; 
		}
		if (toDel->Next) {
			toDel->Next->Parent = toDel->Parent;
		}
		FreeListNode(toDel);
		free(toDel);
	}
	return ret;	
}
```

Конечно, асимптотическая сложность в точности совпадает со сложностью функции поиска, а она до сих пор O(n). Короче, тлен. Да и в целом данная СД пригодна к осмысленному использованию только как вспомогательный инструмент для реализации действительно годных СД - очередей и стеков (про них в следующей части). А ещё список может быть (а может и не быть) неплохим решением проблем, связанных с невозможностью выделения непрерывного большого (реально большого) куска памяти под массив. В таком случае тот же самый массив выделяется не непрерывным куском, а маленькими частями, которые связываются между собой посредством указателей. Так что кладем списки в копилочку полезностей и идем дальше.
