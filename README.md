# My Embedded C Coding Style

This document describes C code style used by EmbSysTech in his projects and libraries.

## Table of Contents

- [Recommended C style and coding rules](#my-embedded-c-coding-style)
    - [Table of Contents](#table-of-contents)
    - [A single request](#a-single-request)
    - [C standard Libraries](#c-standard-libraries)
    - [General rules for Code Formating](#general-rules-for-code-formating)
    - [Variables](#variables)

## A single request

I encourage everyone to adhere to our embedded C coding guidelines to ensure consistency and readability across our projects. Following these guidelines will help maintain clarity and facilitate collaboration among everyone. Please take the time to study our existing libraries as examples of best practices. Imitating the style, including proper whitespace usage, function declarations, and commenting conventions, will enhance both the quality of our code and our collective understanding. Let's commit to writing clean, maintainable code that reflects our team's standards and professionalism. Your cooperation is greatly appreciated!

As a developer & contineous learner even sometimes I forget these rules & make mistakes. Please if you find any such mistakes rectify as well as comment & indicate so that these mistakes can be removed.

## C Standard Libraries

- Standard C file selection for operation. There are many C Standard libraries that you can use instead of writing code from scratch. The following are the most common standard libraries:
- **<stdio.h>** Input/output
- **<string.h>** String handling library
- **<stdbool.h>** Boolean type
- **<stdint.h>** Fixed-width integer types
- **<stdarg.h>** Variable arguments capture
- **<math.h>** Common mathematics functions
- **<complex.h>** Complex number arithmetic
- **<ctype.h>** Character types checking
- **<limits.h>** Sizes of basic types
- **<stdlib.h>** General utilities such as: Memory, program, string conversions, random and algorithms
- **<time.h>** Time and date utilities

## General Rules For Code Formating

- Use `C11` standard
- Do not use tabs, use spaces instead
- Use `4` spaces per indent level
- Use none space between keyword and opening bracket.
- Use Indent statements within **function** body
- Use Indent statements within **block**
- Use Indent statements within **switch** body
- Use Indent statements within **case** body
- Always use /* comment */ for comments, even for single-line comment
- Always include check for C++ with extern keyword in header file
- Every function MUST include doxygen-enabled comment, even if function is static
- Use English names/text for functions, variables, comments
- Always use < and > for C Standard Library include files, eg. #include <stdlib.h>
- Always use "" for custom libraries, eg. #include "my_library.h"
```c
/* Wrong */
if (condition)
while (condition)
for (init; condition; step)
do {} while (condition)
/* OK */
if(condition)
while(condition)
for(init; condition; step)
do{}while(condition)

```
- Brace on the **next line** for **function** declaration
- Brace on the **next line** for **blocks**
- Brace on the **next line** for **blocks in case** statements
- Brace on the **next line** for **switch** statement(e.g. `for`, `while`, `do`, `switch`, `if`, ...)
- Brace on the **next line** for **linkage** (e.g. extern)
```c
/* WRONG */
void myFunction(int param) {
    // Function body
}
if (condition) {
    // Code block
}
else 
   // Another block

/* OK */
for (int i = 0; i < 10; i++)
{
    // Loop body
}

while (condition)
{
    // Loop body
}

do
{
    // Loop body
} while (condition);

if (condition)
{
    // If block
} else {
    // Else block
}

switch (value)
{
    case 1:
        // Case block
        break;
    default:
        // Default case
        break;
}

```
- Add white space for **Declarator list** after comma
- For **functions**, add a white space after every argument & comma
- Add a white space after semicolon in **for-loop** parameters
- Add a white space after comma in **function arguments**
- Add a white space before and after **assignment and binary operators**
- Add a white space after comma in **Initializer list**
```c
/* WRONG */
int* ptrA, * ptrB, * ptrC;
float* pValue, * pTemp;

char* getString (int index);
void processData (int value,float factor);

for (int i = 0;i < 10;i++) {
    sum += i;
}
/* OK */
int *ptrA, *ptrB, *ptrC;
float *pValue, *pTemp;

int numbers[] = { 1, 2, 3, 4, 5 };
float values[] = { 10.5, 20.8, 30.2 };

char* getString(int index);
void processData(int value, float factor);

for (int i = 0; i < 10; i++)
{
    sum += i;
}
int result = a + b * c;
x = y - z;
sum = num1 + num2;
count += 5;
```
**Line Wrapping**
- A maximum line width of 120 characters is recommended.
- Indent wrapped line 2 indentation levels
- For wrapped functions, wrap all elements on a new line
- Enum list always wrapped regardless of line width
- For wrapped expressions, wrap only necessary parts
- For wrapped initializer list, wrap only necessary parts

## Variables
- Use camelCase naming convention for all trypes of variables. First word starts with a lower case and all following words start with upper case
```c
    int16_t initialTempurature;
    float gpsLatitude;
```
– Use clear and descriptive names & do not use short names
- Avoid using abbreviations
- Make the variable name as short as possible, yet clear.
```c
/* WRONG */
int16_t avgTemp;
/* OK */          
int16_t averageTempurature; 
```
– Declare variables in separate lines this generally improves readability.
- It reduces future potential bugs related to multiple variables in a single line, like delete or comment out.
- Declare all local variables of the same type in the same line
```c
   /* OK */
    char a;             
    char a, b;          
    
    /* WRONG */
    char a;
    char b;             /* Wrong, variable with char type already exists */
```
- Align variable names and values for a group of declarations, for better readability, as follows:
```c
uint16_t avarageTempurature = 15;
uint16_t totalRPM           = 17;
float    avarageSpeed       = 12.56f;
```
– For Pointer variables, use the letter 'ptr' as a prefix:
```c
char *ptrEmployeeName;
```
For Double Pointer variables, use "pp" as a prefix
```c
char **ppWifiNames;
```
- For Global variables, use the letter 'glb' as a prefix
```c
uint8_t glbNextIndex;
```
– When a variable is both Global and Pointer, use 'gptr' as a prefix
```c
char *gptrLastName;
```
- Notes:
    - Local scope: Referring to when a variable is declared within a function
    - Global scope: Referring to when a variable is declared globally in a source file, or a more special case is when declared as static within a function.
- Static Keyword:
    - Use 'static' keyword when a variable or function is to be visible only within a single source file.
    - It is recommended to keep variables within a source file static if they are not meant to be visible by other files.
    - **However, it is not recommended to define a static variable within a function**, this can make your code less readable and more susceptible to bugs.
    
- When a variable is used by interrupt routine or is a memory-mapped pointer, it must be declared as volatile.
- Tick counters are incremented in an Interrupt routine, thus volatile
- Memory-mapped pointers values are volatile since a register can be changed by hardware.
```c
volatile uintmax_t glbCounterTicks = 0;

volatile uint8_t *ptrInputSwitch = (uint8_t*)(GPIOA->IDR);
```
- Declare local variables in order
    i. Custom structures and enumerations
    ii. Global Integer types, unsigned type 
    iii. Global Single/Double floating point
    iv. local Integer types, unsigned type 
    v. local Single/Double floating point
- Always declare local variables at the beginning of the block, before first executable statement
- Except char, float or double, always use types declared in stdint.h library, eg. uint8_t for unsigned 8-bit, etc.
- Always compare pointers against NULL value.
- Always use size_t for length or size variables.
- Always use uintmax_t_t for max length or size variables.
- Always use uintptr_t* or void* for length or size pointers.
- Always use const for pointer if function should not modify memory pointed to by pointer.
- Always use const for function parameter or variable, if it should not be modified.











































































