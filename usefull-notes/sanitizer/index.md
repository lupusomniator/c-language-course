# Санитайзеры

Существует три вида санитайзеров:
- [address](#адрес-санитайзер)
- [undefined](#undefined-санитайзер)
- thread (В статье не рассмотрен)

**Важно**: не все санитайзеры друг с другом совместимы.) Хотите
проверить всеми - придётся пересобрать и запустить.) 

## Адрес-санитайзер

Адрес-санитайзер помогает находить такие ошибки при работе с памятью как [missing free](#missing-free) [use-afer-free](#use-after-free) и [переполнение](#heap-overflow).

Инструкцию по использованию санитайзера при компиляции Вы можете найти в документации к вашему компилятору. Вот так, к примеру, это делается на gcc:

```bash
gcc file.c -fsanitize=address
```

### Missing free
```c
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int *data = (int *) malloc(sizeof(int));
    data[0] = 0;
    return 0;
}
```
При запуске получим ошибку от санитайзера:
```
==11810==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 4 byte(s) in 1 object(s) allocated from:
    #0 0x7f2ac6abfa89 in __interceptor_malloc /usr/src/debug/gcc/gcc/libsanitizer/asan/asan_malloc_linux.cpp:69
    #1 0x557a1f6b817a in main (/home/bigcubecat/Projects/NSU/c-language-course/usefull-notes/a.out+0x117a)
    #2 0x7f2ac683c78f  (/usr/lib/libc.so.6+0x2378f)

SUMMARY: AddressSanitizer: 4 byte(s) leaked in 1 allocation(s).
```

### Use after free

Возникает при использовании очищеной памяти.
Пример:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc, const char *argv[]) {
    char *s = (char *)malloc(sizeof(char) * 128);
    free(s);
    strcpy(s, "Hello world!");
    printf("string is: %s\n", s);
    return 0; 
}
```
Результат:
```
=================================================================
==12337==ERROR: AddressSanitizer: heap-use-after-free on address 0x60c000000040 at pc 0x7f11a825f427 bp 0x7ffcf00f0f50 sp 0x7ffcf00f06f8
WRITE of size 13 at 0x60c000000040 thread T0
    #0 0x7f11a825f426 in __interceptor_memcpy /usr/src/debug/gcc/gcc/libsanitizer/sanitizer_common/sanitizer_common_interceptors.inc:827
    #1 0x564ca721f1ec in main (/home/bigcubecat/Projects/NSU/c-language-course/usefull-notes/a.out+0x11ec)
    #2 0x7f11a803c78f  (/usr/lib/libc.so.6+0x2378f)
    #3 0x7f11a803c849 in __libc_start_main (/usr/lib/libc.so.6+0x23849)
    #4 0x564ca721f0d4 in _start (/home/bigcubecat/Projects/NSU/c-language-course/usefull-notes/a.out+0x10d4)

0x60c000000040 is located 0 bytes inside of 128-byte region [0x60c000000040,0x60c0000000c0)
freed by thread T0 here:
    #0 0x7f11a82be672 in __interceptor_free /usr/src/debug/gcc/gcc/libsanitizer/asan/asan_malloc_linux.cpp:52
    #1 0x564ca721f1d1 in main (/home/bigcubecat/Projects/NSU/c-language-course/usefull-notes/a.out+0x11d1)
    #2 0x7f11a803c78f  (/usr/lib/libc.so.6+0x2378f)

previously allocated by thread T0 here:
    #0 0x7f11a82bfa89 in __interceptor_malloc /usr/src/debug/gcc/gcc/libsanitizer/asan/asan_malloc_linux.cpp:69
    #1 0x564ca721f1c1 in main (/home/bigcubecat/Projects/NSU/c-language-course/usefull-notes/a.out+0x11c1)
    #2 0x7f11a803c78f  (/usr/lib/libc.so.6+0x2378f)

SUMMARY: AddressSanitizer: heap-use-after-free /usr/src/debug/gcc/gcc/libsanitizer/sanitizer_common/sanitizer_common_interceptors.inc:827 in __interceptor_memcpy
Shadow bytes around the buggy address:
  0x0c187fff7fb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c187fff7fc0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c187fff7fd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c187fff7fe0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c187fff7ff0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0c187fff8000: fa fa fa fa fa fa fa fa[fd]fd fd fd fd fd fd fd
  0x0c187fff8010: fd fd fd fd fd fd fd fd fa fa fa fa fa fa fa fa
  0x0c187fff8020: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c187fff8030: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c187fff8040: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c187fff8050: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==12337==ABORTING
```

### Heap overflow

Буквально - переполнение. Эта ошибка появляется, когда выделено не достаточно памяти:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    char *s = malloc(sizeof(char));
    strcpy(s, "Hello world!");
    printf("string is: %s\n", s);
    free(s);
    return 0;
}
```

```
=================================================================
==13445==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000000011 at pc 0x7f92f705f427 bp 0x7ffde3ee26d0 sp 0x7ffde3ee1e78
WRITE of size 13 at 0x602000000011 thread T0
    #0 0x7f92f705f426 in __interceptor_memcpy /usr/src/debug/gcc/gcc/libsanitizer/sanitizer_common/sanitizer_common_interceptors.inc:827
    #1 0x5652f989f1d9 in main (/home/bigcubecat/Projects/NSU/c-language-course/usefull-notes/a.out+0x11d9)
    #2 0x7f92f6e3c78f  (/usr/lib/libc.so.6+0x2378f)
    #3 0x7f92f6e3c849 in __libc_start_main (/usr/lib/libc.so.6+0x23849)
    #4 0x5652f989f0d4 in _start (/home/bigcubecat/Projects/NSU/c-language-course/usefull-notes/a.out+0x10d4)

0x602000000011 is located 0 bytes to the right of 1-byte region [0x602000000010,0x602000000011)
allocated by thread T0 here:
    #0 0x7f92f70bfa89 in __interceptor_malloc /usr/src/debug/gcc/gcc/libsanitizer/asan/asan_malloc_linux.cpp:69
    #1 0x5652f989f1ba in main (/home/bigcubecat/Projects/NSU/c-language-course/usefull-notes/a.out+0x11ba)
    #2 0x7f92f6e3c78f  (/usr/lib/libc.so.6+0x2378f)

SUMMARY: AddressSanitizer: heap-buffer-overflow /usr/src/debug/gcc/gcc/libsanitizer/sanitizer_common/sanitizer_common_interceptors.inc:827 in __interceptor_memcpy
Shadow bytes around the buggy address:
  0x0c047fff7fb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c047fff7fc0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c047fff7fd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c047fff7fe0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c047fff7ff0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0c047fff8000: fa fa[01]fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8010: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8020: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8030: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8040: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8050: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==13445==ABORTING
```

## Undefined-санитайзер

Undefined-санитайзер способен обнаруживать различные формы неопределенного поведения (UB). Это помогает как определить, почему приложение ведет себя неправильно, так и предотвратить проблемы в будущем. Средство очистки неопределенного поведения включено с флагом компилятора `-fsanitize=undefined`.

Код:
```c
#include <stdio.h>

int main() {
    /* Overflows an unsigned integer by shifting it 32 times */
    printf("%d", 1u >> 32);
}
```
Вывод: (обратите внимание на то, как запускается a.out)
```
➜  usefull-notes git:(main) ✗ UBSAN_OPTIONS="print_stacktrace=1:halt_on_error=1" ./a.out 
sanitizer/undef.c:5:21: runtime error: shift exponent 32 is too large for 32-bit type 'unsigned int'
    #0 0x561a73299165 in main (/home/bigcubecat/Projects/NSU/c-language-course/usefull-notes/a.out+0x1165)
    #1 0x7f22d623c78f  (/usr/lib/libc.so.6+0x2378f)
    #2 0x7f22d623c849 in __libc_start_main (/usr/lib/libc.so.6+0x23849)
    #3 0x561a73299074 in _start (/home/bigcubecat/Projects/NSU/c-language-course/usefull-notes/a.out+0x1074)
```