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
- Do not use underscore `_` in the name of .c/.h file. Also use camelCase for file names with first letter also to be capitalwith **optional** `_` underscore.
- When casting to pointer type, always align asterisk to type, eg. uint8_t* t = (uint8_t*)var_width_diff_type
- Always respect code style already used in project or library

## Comments

- For Single line comments please use following idea
```c
//This is comment
```
- For multi-line comments use /**/ and please use `space+asterisk` for every line
```c
/*
 * This is multi-line comments,
 * written in 2 lines (ok)
 */

/**
 * if required then only, use double-asterisk for doxygen documentation
 */
```
- Use 12 indents (each indent being 4 spaces) offset when commenting. If statement is larger than 12 indents, make comment 4-spaces aligned (examples below) to next available indent
```c
void myFunction(void)
{
    char a, b;

    a = callFunctionReturning_Char_a(a);             // This is comment with 12*4 spaces indent from beginning of line 
    b = callFunctionReturningCharaButFunction_Name_Is_Very_Long(a);    // This is comment, aligned to 4-spaces indent 
}
```

## Libraries and General Modularity

- The idea behind these principles is to move towards using libraries with common functions and classes that are often used in different projects. The classes must be designed so that they can freely operate independently from each other. Keep in mind that modifying the hardware files is all that really should be essential when moving one platform/project into another.

- The operating system is a simple, fixed time, round-robin scheduler, set in motion by a fixed period timer monitored in the background main loop. When flagged that a certain periodic time has passed, the scheduler executes calling a sequence of methods that perform the intended functionality of the code and returns when the list is completed.

- The other way around is using real RTOS such as FreeRTOS for application with advanced functionalities such as mutex, semaphore etc. to minimize the entire complexity if required. 

- Or we can follow a UML class structure to work in state machine for which prior method is to use quantum leaps software for code generattion and UML chart generation.

- The every given module has a one structture that defined using `C typedef struct {}` which contains all public variables which are intended to be used globally in all the modules for which the actual declaration will in UserMain.c and extern is defined at the actual module file. Make sure Do not use any static or private definations in this structure.
```c

typedef struct
{
// Public Variables
uint8_t State;
uint16_t Speed;
uint16_t Current;

// Public Methods
// void    (* Init)(void *);
// uint8_t (* Run)(void *);
// uint8_t (* Stop)(void *);
// uint8_t (* PutSpeed)(void *);
} Motor;

// Public methods
extern void Mortor_Init(Motor *);
extern byte Mortor_Run(Motor *);
extern byte Mortor_Stop(Motor *);
extern byte Mortor_PutSpeed(Motor *);
```
- The structure including pointer to function that has the advantage of more closely matching the public items of the Class Structure Drawing, specifically the instance variables and methods. It also looks more like real OOP languages when the methods are called using an object.methodPointer format. This will also give advantages just like a Arduino compilers.
- The given structure is only way we can access module functions and variables otherwise none of the things should be accessable outside. 

## Functions

- Never use `__` or `_` at the start for a variables/functions/macros/types. This is usually used by internal C/C++ or embedded C/C++ library variables/functions/macros/types.
- Prefer `_private` at the end of the variables/functions for strictly module-private (static) variables/functions.
- Use camelCase writing for global & static variables/functions/types with **optional** underscore `_`.
```c
/* OK */
void my_Func(void);
void myFunc(void);

/* Wrong */
void MYFunc(void);
void myfunc();
void my_func();
```
- When function returns pointer, align asterisk to return type
```c
/* OK */
const char* my_Func(void);
my_struct_t* my_Func(int32_t a, int32_t b);

/* Wrong */
const char *my_func(void);
my_struct_t * my_func(void);
```
- Align all function prototypes (with the same/similar functionality) for better readability
- The five parts of the naming convention are:
1. the pin or resource name
2. the type of pin or resource and direction
3. and “_” character
4. the action the method performs.
5. Parentheses with any parameters that are passed.
- The below table lists the recommended action liist for naming.
  
|Verb	           | Use                                              |
|----------------|--------------------------------------------------|
|Adjust	         |Adjusting a value                                 |
|DigIn           |Digital Input                                     |
|DigOut          |Digital Output                                    |
|Toggle          |Toggling the pin                                  |
|AngIn           |Analog Input                                      |
|AngOut          |Analog Output                                     |
|Apply	         |Assigning (applying) a new value                  |
|Calc	           |Executing an algorithm, calculating data          |
|Check	         |Checking a value                                  |
|Clear	         |Resetting (clearing) a signal (a message)         |
|Ctrl	           |Performing a controlling activity                 |
|Convert	       |Converting data                                   |
|Decrment        |Decrementing                                      |
|Increment       |Incrementing                                      |
|Get	           |Getting (importing) data from another module      |
|Init	           |Initializing data                                 |  
|Lookup	         |Retrieving (looking up) a value, data from a table|
|Manage	         |Triggering other activities                       |
|Service	       |Servicing interrupt                               | 
|Reset	         |Resetting data or states                          |
|Set	           |Setting data in another module                    |
|Start	         |Starting a process (for example, a timer)         |
|Stop	           |Stopping a process                                |
|Test	           |Performing a test                                 |
|Update	         |Updating data                                     |
|Is	             |Polling a logic status                            |

## Variables

- Never use `__` or `_` at the start for a variables/functions/macros/types. This is usually used by internal C/C++ or embedded C/C++ library variables/functions/macros/types.
- Prefer `_private` at the end of the variables/functions for strictly module-private (static) variables/functions.
- Use camelCase writing for global & static variables/functions/types with **optional** underscore `_`.
- Use lowercase writing for local variables/functions/types with **optional** underscore `_`.
- Use Uppercase writing for constant variables with **optional** underscore `_`. Suggested to write all constant variable with `#define` pre-processor directive. In case, if needed, can use `const` keyword too.
- Do initialize global/local/static variables to default `0` value (or NULL), if REQUIRED, please initialise variables with default values using init function seperately.
```c
static int32_t a;        /* Wrong */
int32_t b = 4;           /* Wrong */
char myArray[10] = {4,5,6};/* Wrong */
static int32_t a = 0;    /* OK */
int32_t b = 0;           /* OK */
char myArray[10] = { };  /* OK */
```
- Group local variables together by type
```c
void myFunction(void)
{
    int32_t a, b;   /* OK */
    char a;
    char b;         /* Wrong, char type already exists */
}
```
- Do not declare variable after first executable statement
```c
void myFunction(void)
{
    int32_t a;   /* OK */
    a = bar();
    int32_t b;      /* Wrong, there is already executable statement */
}
```
- Declare all pointer variables with asterisk aligned to variable name
```c
/* OK */
char *p, *n;


/* Wrong */
char* a;
char * a;
```
## Structures, enumerations, typedefs

- Use camelCase writing for global & static variables/functions/types with **optional** underscore `_`.
- Use lowercase writing for local variables/functions/types with **optional** underscore `_`.
- Structure or enumeration may contain `typedef` keyword
- When initializing structure on declaration, use C99 initialization style
```c
/* OK */
a_t a = {
    .a = 4,
    .b = 5,
};

/* Wrong */
a_t a = {1, 2};
```
- When new typedef is introduced for function handles, use _fn suffix
```c
/* Function accepts 2 parameters and returns uint8_t */
/* Name of typedef has `_function` suffix */
typedef uint8_t (*my_Func_Typedef_function)(uint8_t p1, const char* p2);
```
## Compound statements

- Every compound statement MUST include opening and closing curly bracket, even if it includes only 1 nested statement
- Every compound statement MUST include single indent; when nesting statements, include 1 indent size for each nest
```c
/* OK */
if (c)
{
    do_a();
}
else
{
    do_b();
}

/* Wrong */
if (c)
    do_a();
else
    do_b();

/* Wrong */
if (c) do_a();
else do_b();
```
- In case of do-while statement, while part MUST be in the same line as closing bracket
```c
/* OK */
/* OK */
do
{
/* ... */
} while (checkTheValues());
/* Wrong */
do {
    int32_t a;
    a = do_A();
    do_B(a);
} while (checkTheValues());

/* Wrong */
do {
/* ... */
}
while (check());
```
- Indentation is REQUIRED for every opening bracket
- Compound statement MUST include curly brackets, even in the case of a single statement
- Empty while, do-while or for loops MUST include brackets
- Always prefer using loops in this order: for, do-while, while
- Avoid incrementing variables inside loop block if possible, see examples
```c
/* Not recommended */
int32_t a = 0;
while (a < 10) {
    .
    ..
    ...
    a++;
}

/* Better */
for (size_t a = 0; a < 10; a++) {

}

/* Better, if inc may not happen in every cycle */
for (size_t a = 0; a < 10; ) {
    if (...) {
        ++a;
    }
}
```
- Inline if statement MAY be used only for assignment or function call operations
```c
/* OK */
int a = condition ? if_yes : if_no; /* Assignment */
func_call(condition ? if_yes : if_no); /* Function call */
switch (condition ? if_yes : if_no) {...}   /* OK */

/* Wrong, this code is not well maintenable */
condition ? call_to_function_a() : call_to_function_b();

/* Rework to have better program flow */
if (condition) {
    call_to_function_a();
} else {
    call_to_function_b();
}
```
## Volatile keyword

The volatile keyword shall be used whenever appropriate. Proper use of volatile
eliminates a whole class of difficult-to-detect bugs by preventing compiler
optimizations that would eliminate requested reads or writes to variables or
registers.

Examples include:
- To declare a global variable accessible (by current use or scope) by any interrupt service routine
- To declare a global variable accessible (by current use or scope) by two or more threads

## Delay Loops

 - Delay loops should be used only if practical and necessary.

## Switch statement

- Add single indent for every case statement
- Use additional single indent for break statement in each case or default statement
```c
/* OK, every case has single indent */
/* OK, every break has additional indent */
switch (check())
{
    case 0:
        do_A();
        break;
    case 1:
        do_B();
        break;
    default:
        break;
}

/* Wrong, case indent missing */
switch (check()) {
case 0:
    do_A();
    break;
case 1:
    do_B();
    break;
default:
    break;
}

/* Wrong */
switch (check()) {
    case 0:
        do_A();
    break;      /* Wrong, break MUST have indent as it is under case */
    case 1:
    do_B();     /* Wrong, indent under case is missing */
    break;
    default:
        break;
}
```
- Always include default statement

## Macros and preprocessor directives

- Always use macros instead of literal constants, especially for numbers
- All macros MUST be fully uppercase, with optional underscore _ character, except if they are clearly marked as function which may be in the future replaced with regular function syntax
- Always protect input parameters with parentheses
```c
/* OK */
#define MIN(x, y)           ((x) < (y) ? (x) : (y))

/* Wrong */
#define MIN(x, y)           x < y ? x : y
```

- Always protect final macro evaluation with parenthesis
```c
/* Wrong */
#define MIN(x, y)           (x) < (y) ? (x) : (y)
#define SUM(x, y)           (x) + (y)

/* Imagine result of this equation using wrong SUM implementation */
int32_t x = 5 * SUM(3, 4);  /* Expected result is 5 * 7 = 35 */
int32_t x = 5 * (3) + (4);  /* It is evaluated to this, final result = 19 which is not what we expect */

/* Correct implementation */
#define MIN(x, y)           ((x) < (y) ? (x) : (y))
#define SUM(x, y)           ((x) + (y))
```
- Always document if/elif/else/endif statements
```c
/* OK */
#if defined(XYZ)
/* Do if XYZ defined */
#else /* defined(XYZ) */
/* Do if XYZ not defined */
#endif /* !defined(XYZ) */

/* Wrong */
#if defined(XYZ)
/* Do if XYZ defined */
#else
/* Do if XYZ not defined */
#endif
```
- Do not indent sub statements inside #if statement
```c
/* OK */
#if defined(XYZ)
#if defined(ABC)
/* do when ABC defined */
#endif /* defined(ABC) */
#else /* defined(XYZ) */
/* Do when XYZ not defined */
#endif /* !defined(XYZ) */

/* Wrong */
#if defined(XYZ)
    #if defined(ABC)
        /* do when ABC defined */
    #endif /* defined(ABC) */
#else /* defined(XYZ) */
    /* Do when XYZ not defined */
#endif /* !defined(XYZ) */
```
## Documentation

- Use doxygen-enabled documentation style for variables, functions and structures/enumerations
- Always use \ for doxygen, do not use @
- Always use 5x4 spaces (5 tabs) offset from beginning of line for text
```c
/**
 * \brief           Holds pointer to first entry in linked list
 *                  Beginning of this text is 5 tabs (20 spaces) from beginning of line
 */
```
- Every structure/enumeration member MUST include documentation
- Use 12x4 spaces offset for beginning of comment
```c
/**
 * \brief           This is point struct
 * \note            This structure is used to calculate all point
 *                      related stuff
 */
```
- Documentation for functions MUST be written in function implementation (source file usually)
- Function MUST include brief and all parameters documentation
- Every parameter MUST be noted if it is in or out for input and output respectively
- Function MUST include return parameter if it returns something. This does not apply for void functions
- Function can include other doxygen keywords, such as note or warning
- Use colon : between parameter name and its description
- \version is used to specify the version number of the file or function
```c
/**
 * \version         1.0.0
 * \brief           Sum `2` numbers
 * \param[in]       a: First number
 * \param[in]       b: Second number
 * \return          Sum of input values
 */
```
- Documentation for macros MUST include hideinitializer doxygen command
```c
/**
 * \version         1.0.0
 * \brief           Get minimal value between `x` and `y`
 * \param[in]       x: First value
 * \param[in]       y: Second value
 * \return          Minimal value between `x` and `y`
 * \hideinitializer
 */
```
## Header/source files

- Leave single empty line at the end of file
- Every file MUST include doxygen annotation for file and brief description followed by empty line (when using doxygen)
```c
/**
 * \file            Template.h
 * \brief           Template include file
 */
                    /* Here is empty line */
```
- Every file (header or source) MUST include license (opening comment includes single asterisk as this MUST be ignored by doxygen)
- Use the same license as already used by project/library
```c
/**
 * \file            template.h
 * \brief           Template include file
 */

/*
 * Copyright (c) year FirstName LASTNAME
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of library_name.
 *
 * \author          FirstName LASTNAME <optional_email@example.com>
 * \date            July 4, 2024    
 */
```
- Never include .c files in another .c file
- .c file should first include corresponding .h file, later others, unless otherwise explicitly necessary
- Do not include module private declarations in header file
- Header file example (no license for sake of an example)
- Header file MUST include guard #ifndef
- Header file MUST include C++ check
- Include external header files outside C++ check
```c
/* License comes here */
#ifndef TEMPLATE_HDR_H
#define TEMPLATE_HDR_H

/* Include headers */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* File content here */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TEMPLATE_HDR_H */
```

## Version.h file

- Every project should contain by default following file as this maintain versioning of the project And at the start if possible on serial/ any debug system should send out version no
- In this file semanting versioning is followed:
>Semantic versioning (often abbreviated as SemVer) is a versioning scheme for software that uses a three-part number format: **MAJOR.MINOR.PATCH** Each part has a specific meaning:

>MAJOR version: Major version change with entire function/hardware/system change.

>MINOR version: Minor version change with few existing function/hardware/system change.

>PATCH version: Increments when backward-compatible bug fixes or minor improvements are made.

>Semantic versioning aims to provide a clear and standardized way to convey the impact of updates to users and developers. By following SemVer, developers can understand the extent of changes in a release at a glance and make informed >decisions about when and how to upgrade their software dependencies. 

```c
/**
 * \file            Version.h
 * \brief           Version include file
 */

/*
 * Copyright (c) year Sourabh Potdar
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of Versioning of the project.
 *
 * \author          Sourabh Potdar 
 * \date            July 4, 2024    
 */
#ifndef VERSION_H_
#define VERSION_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define MAJOR           1
#define MINOR           0
#define PATCH           0

// To convert the parameter into string
#define _STRING(x)          #x
#define STRING(x)           _STRING(x)

#define VERSION_STRING      STRING(v.MAJOR.MINOR.PATCH)

/*
 * Update firmware version information here (not above) Latest information first.
 *
 *  Date          FirmWare  File Changed            File V/R    Programmer          Description
 * *-------------*---------*-----------------------*-----------*-------------------*---------------------------------------------------------------------------------------
*/


#endif /* VERSION_H_ */
```
## Hardware dependent file

- As we want a code not to be ot in the “Hardware Level” MUST BE hardware-independent. NO EXCEPTIONS.
- To resolve this issue we can have a specific files which can resolve this conflicts
  
|    File Names          |Description                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
|StdUtils.h              |This file contains special compiler build options for the specific processor andproject.|
|                        |This might include universal definitions and conditional compilation definitions.       | 
|HardToFirmTranslate.h/.c|contains all the macro definitions for virtual hardware to actual hardware translation. |
|Interrupts.c/.h         |This file will contain hardware and compiler-dependent code associated with interrupts  |
|                        |and should be limited as much as possible to hardware/compilerdependent lines. Any      |
|                        |significant processing should be handled in hardware independent code                   |














































































