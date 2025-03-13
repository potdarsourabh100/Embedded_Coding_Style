# My Embedded C Coding Style

This document describes C code style used by EmbSysTech in his projects and libraries.

## Table of Contents

- [Recommended C style and coding rules](#my-embedded-c-coding-style)
    - [Table of Contents](#table-of-contents)
    - [A single request](#a-single-request)
    - [C standard Libraries](#c-standard-libraries)
    - [General rules for Code Formating](#general-rules-for-code-formating)

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












































































