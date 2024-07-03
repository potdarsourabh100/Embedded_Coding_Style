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


