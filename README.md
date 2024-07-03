# Embedded_Coding_Style
## The Important Rule

Let's start with the quote from GNOME developer site.

The single most important rule when writing code is this: check the surrounding code and try to imitate it.

As a maintainer it is dismaying to receive a patch that is obviously in a different coding style to the surrounding code. This is disrespectful, like someone tromping into a spotlessly-clean house with muddy shoes.

So, whatever this document recommends, if there is already written code and you are patching it, keep its current style consistent even if it is not your favorite style.

## General rules for code writing & aesthetic maintenance

Here are listed most important general rules for C/C++ code writing. 
- Use `C11` standard
- Do not use tabs, use spaces instead
- Use `4` spaces per indent level
- Use `1` space between keyword and opening bracket
- Do not use values in between code(magic numbers) try to declare them globally and use alias name for it.
- Do not use underscore `_` in the name of .c/.h file. Also use camelCase for file names with first letter also to be capital.

```c
/* OK */
if (condition)
while (condition)
for (init; condition; step)
do {} while (condition)

/* Wrong */
if(condition)
while(condition)
for(init;condition;step)
do {} while(condition)
```
- Do not use space between function name and opening bracket
```c
int32_t a = sum(4, 3);              /* OK */
int32_t a = sum (4, 3);             /* Wrong */
```
- Never use `__` or `_` at the start for a variables/functions/macros/types. This is usually used by internal C/C++ or embedded C/C++ library variables/functions/macros/types.
- Prefer `_private` at the end of the variables/functions for strictly module-private (static) variables/functions.
- Use camelCase writing for global & static variables/functions/types with **optional** underscore `_`.
- Use lowercase writing for local variables/functions/types with **optional** underscore `_`.
- Use Uppercase writing for constant variables with **optional** underscore `_`. Suggested to write all constant variable with `#define` pre-processor directive. In case, if needed, can use `const` keyword too.
```c
int my_Name = 0;
void my_Function_For_Demo(void)
{
  int my_variable_for_demo = 0;
  static my_Demo_Static_Variables_private = 0;
}
static int my_Static_Function_private(void)
```
- Opening curly bracket is always at the next line for maintaining the indentations(for, while, do, switch, if, ...),functions etc.
```c
size_t i;
for (i = 0; i < 5; ++i)             /* OK */
{
}
for (i = 0; i < 5; ++i) {           /* Wrong */
}
for (i = 0; i < 5; ++i){            /* Wrong */
}
```
- Use single space before and after comparison and assignment operators
```c
int32_t a;
a = 3 + 4;              /* OK */
for (a = 0; a < 5; ++a) /* OK */
a=3+4;                  /* Wrong */
a = 3+4;                /* Wrong */
for (a=0;a<5;++a)       /* Wrong */
```
- Do initialize global/local/static variables to default `0` value (or NULL), if REQUIRED, please initialise variables with default values using init function seperately.
```c
static int32_t a;        /* Wrong */
int32_t b = 4;           /* Wrong */
char myArray[10] = {4,5,6};/* Wrong */
static int32_t a = 0;    /* OK */
int32_t b = 0;           /* OK */
char myArray[10] = { };  /* OK */
```
>In embedded systems, it is very common that RAM memories are scattered across different memory locations in the system. It quickly becomes tricky to handle all the cases,
>especially when user declares custom RAM sections. Startup script is in-charge to set default values (.data and .bss) while other custom sections may not be filled with default values,
>which leads to variables with init value won't have any effect.
>To be independent of such problem, create init function for each module and use it to set default values for all of your variables, like so:
```c
static int32_t a = 0;       /* OK */
static int32_t b = 4;   /* Wrong - this value may not be set at zero 
                            if linker script&startup files are not properly handled */
void my_ModuleInit(void)
{
    a = 5;
    b = 4;
}
```
- Declare all local variables of the same type in the same line
```c
void my_Func(void)
{
    /* 1 */
    char a;             /* OK */
    
    /* 2 */
    char a, b;          /* OK */
    
    /* 3 */
    char a;
    char b;             /* Wrong, variable with char type already exists */
}
```
-Declare local variables in following order
  - Custom structures and enumerations
  - Integer types, wider unsigned type first
  - Single/Double floating point
```c
int my_Func(void)
{
    /* 1 */
    my_Struct my;     /* First custom structures */
    my_Struct_Ptr* p; /* Pointers too */
    /* ... */

    /* 2 */
    uint32_t a;
    int32_t b;
    uint16_t c;
    int16_t g;
    char h;
    /* ... */

    /* 3 */
    double d;
    float f;
    /* ... */
}
```
- Always declare local variables at the beginning of the block, before first executable statement
- Declare counter variables in `for` loop. OK to declare at the beginning of the block, if you need counter variable later.
```c
/* OK */
for (size_t i = 0; i < 10; ++i)

/* OK, if you need counter variable later */
size_t i;
for (i = 0; i < 10; ++i)
{
    if (...)
    {
        break;
    }
}
if (i == 10)
{

}

/* Wrong */
size_t i;
for (i = 0; i < 10; ++i) ...
/* If you are not using i variable again */
```
- Always add trailing comma in the last element of structure (or its children) initialization (this helps clang-format to properly format structures).
```c
typedef struct
{
  int a, b;
} str;

str s =
{
    .a = 1,
    .b = 2,   /* Comma here */
}

/* Examples of "complex" structure, with or with missing several trailing commas, after clang-format runs the formatting */
static const my_Struct myVar_1 =
{
    .type = TYPE1,
    .type_data =
        {
            .type1 =
                {
                    .par1 = 0,
                    .par2 = 1, /* Trailing comma here */
                }, /* Trailing comma here */
        },  /* Trailing comma here */
};

static const my_Struct myVar =
{
    .type = TYPE2,
    .type_data =
        {
          .type2 =
              {
                 .par1 = 0,
                 .par2 = 1,
              },
}};    /* Missing comma here & curly brraces closed wrongly */
static const my_Struct_t myVar_3 =
{
  .type = TYPE3,
  .type_data =
      {
        .type3 =
          {
            .par1 = 0,
            .par2 = 1,
}}}; /* Missing 2 commas here & curly brraces closed wrongly */
```
- Avoid variable assignment with function call in declaration, except for single variables
```c
void a(void)
{
    /* Avoid function calls when declaring variable */
    int32_t a, b = sum(1, 2);

    /* Use this if variable are local*/
    int32_t a, b;
    b = sum(1, 2);

    /* This is ok if variable are local */
    uint8_t a = 3, b = 4;
}
```
- Except char, float or double, always use types declared in stdint.h library, eg. uint8_t for unsigned 8-bit, etc.
- Avoid using stdbool.h library. Use 1 or 0 for true or false respectively As it is not available yet for all possible compilers.
```c
/* OK */
uint8_t status;
status = 0;

/* Wrong */
#include <stdbool.h>
bool status = true;
```
- Never compare against true or 1, eg. `if (check_func() == 1)`, use `if (check_func()) { ... }`.
- Always compare pointers against `NULL` value
```c
void* ptr;
/* ... */
/* OK, compare against NULL by any one statement*/
if (ptr == NULL || ptr != NULL)
{

}
/* Wrong */
if (ptr || !ptr)
{

}
```
- Always use `size_t` for length or size variables but please note:

> size_t is a type that can hold any array index.Depending on the implementation, it can be any of:
> - unsigned char
> - unsigned short
> - unsigned int
> - unsigned long
> - unsigned long long
> 
>Here's how size_t is defined in stddef.h of my machine:
> typedef unsigned long size_t;
>
> **size_t is an unsigned type. So, it cannot represent any negative values(<0). You use it when you are counting something, and are sure that it cannot be negative.**

- Always use const for pointer if function should not modify memory pointed to by pointer
- Always use const for function parameter or variable, if it should not be modified
- When function may accept pointer of any type, always use void *, do not use uint8_t *
  - Function MUST take care of proper casting in implementation
```c
/* When d could be modified, data pointed to by d could not be modified */
void my_Func(const void* d)
{

}
/* When d and data pointed to by d both could not be modified */
void myFunc(const void* const d)
{

}
/* Not REQUIRED, it is advised */
void myFunc(const size_t len)
{

}
/* When d should not be modified inside function, only data pointed to by d could be modified */
void my_Func(void* const d) {

}
/*
 * To send data, function should not modify memory pointed to by `data` variable
 * thus `const` keyword is important
 *
 * To send generic data (or to write them to file)
 * any type may be passed for data,
 * thus use `void *`
 */
/* OK example */
void sendData(const void* data, size_t len)
{ 
    /* Do not cast `void *` or `const void *` */
    const uint8_t* d = data;/* Function handles proper type for internal usage */
}
```
- Never use Variable Length Array (VLA). Use dynamic memory allocation instead with standard C malloc and free functions or if library/project provides custom memory allocation, use its implementation
```c
void my_Func(size_t size)
{
    /* Wrong */    
    int32_t arr[size];  /* Wrong, do not use VLA */

    /* OK */
    int32_t* arr;
    arr = malloc(sizeof(*arr) * n); /* OK, Allocate memory */
    if (arr == NULL) {
        /* FAIL, no memory */
    }

    /* ... */
    free(arr);  /* Free memory after usage */
}
```
- Always compare variable against proper constants, except if it is treated as boolean type
- Never compare boolean-treated variables against zero or one. Use use `NOT (!)` instead
```c
size_t length = 5;  /* Counter variable */
uint8_t ok = 0;  /* Boolean-treated variable */
if (length)         /* Wrong, length is not treated as boolean */
if (length > 0)     /* OK, length is treated as counter variable containing multi values, not only 0 or 1 */
if (length == 0)    /* OK, length is treated as counter variable containing multi values, not only 0 or 1 */

if (ok)          /* OK, variable is treated as boolean */
if (!ok)         /* OK, -||- */
if (ok == 1)     /* Wrong, never compare boolean variable against 1! */
if (ok == 0)     /* Wrong, use ! for negative check */
```
- Always include check for C++ with extern keyword in header file
- Use English names/text for functions, variables, comments
- Never cast function returning void *, eg. uint8_t* ptr = (uint8_t *)func_returning_void_ptr(); as void * is safely promoted to any other pointer type
  - Use uint8_t* ptr = func_returning_void_ptr(); instead
- Always use < and > for C Standard Library include files, eg. #include <stdlib.h>
- Always use "" for custom libraries, eg. #include "MyLibrary.h"
- When casting to pointer type, always align asterisk to type, eg. uint8_t* t = (uint8_t*)var_width_diff_type
- Always respect code style already used in project or library
















