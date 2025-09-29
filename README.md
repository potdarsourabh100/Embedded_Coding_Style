# Embedded C Coding Style Guide  

This document defines the coding style and best practices used at **EmbSysTech** for all embedded C projects and libraries.  
Consistency and readability are our top priorities—following these guidelines ensures clean, maintainable, and professional code.

---

## 📑 Table of Contents  

1. [Introduction](#introduction)  
2. [C Standard Libraries](#c-standard-libraries)  
3. [Code Formatting Rules](#code-formatting-rules)  
4. [Variables](#variables)  
5. [Constants](#constants)  
6. [Structures](#structures)  
7. [Enums](#enums)  
8. [Conditional Flow](#conditional-flow)  
9. [Macros](#macros)  
10. [Functions](#functions)  
11. [Header & Source Files](#header--source-files)  
12. [Comments & Documentation](#comments--documentation)  

---

## 1. Introduction  

We encourage everyone to **strictly follow** this style guide to maintain:  
- **Clarity** → readable and self-explanatory code.  
- **Consistency** → uniform coding across all projects.  
- **Collaboration** → easier reviews, onboarding, and teamwork.  

Mistakes happen—even seasoned developers sometimes forget these rules.  
If you find deviations:  
- **Correct them**  
- **Leave a comment** (so others learn and avoid repeating the mistake)  

Our collective goal is **professional, maintainable code**.  

---

## 2. C Standard Libraries  

Use standard C libraries whenever possible instead of reinventing functionality.  
The most commonly used are:  

- `<stdio.h>` – Input/Output  
- `<string.h>` – String handling  
- `<stdbool.h>` – Boolean types  
- `<stdint.h>` – Fixed-width integers  
- `<stdarg.h>` – Variable argument handling  
- `<math.h>` – Mathematical functions  
- `<complex.h>` – Complex number arithmetic  
- `<ctype.h>` – Character classification  
- `<limits.h>` – Type limits  
- `<stdlib.h>` – General utilities (memory, conversion, random)  
- `<time.h>` – Time and date utilities  

---

## 3. Code Formatting Rules  

- **Standard:** Use `C11`  
- **Indentation:** 4 spaces (never tabs)  
- **Line length:** Max 120 characters  
- **Braces:** Always on the **next line** for functions, blocks, `if/else`, loops, `switch`, etc.  
- **Whitespace:**  
  - Space after `,`, `;` in for-loops, and around operators (`=`, `+`, `-`, `*`, etc.)  
  - No space between keywords and `(` → e.g., `if(condition)`  

✅ Example:  
```c
if(condition)
{
    for(int i = 0; i < 10; i++)
    {
        sum += i;
    }
}
```

❌ Wrong:  
```c
if ( condition ) {
   for(int i=0;i<10;i++){
     sum+=i;
   }}
```  

- **Line wrapping:**  
  - Indent wrapped lines 2 levels  
  - Always wrap enums  
  - Wrap long expressions and function arguments cleanly  

---

## 4. Variables  

- **Naming convention:** `camelCase`  
- **Descriptive, no abbreviations** (e.g., `averageTemperature`, not `avgTemp`)  
- **One declaration per line** for readability  
- **Alignment:** Align names and values when grouped  

```c
uint16_t averageTemperature = 15;
uint16_t totalRPM           = 17;
float    averageSpeed       = 12.56f;
```

- **Pointer notation:** `*` sticks to type, not variable  
  ```c
  int *ptrValue;      // ✅
  int* ptrValue;      // ❌
  ```
- **Prefixes:**  
  - `ptr` → pointer  
  - `pp`  → double pointer  
  - `glb` → global variable  
  - `gptr` → global pointer  

- **Volatile:** Always mark ISR-shared variables or memory-mapped registers as `volatile`.  

```c
volatile uint32_t glbTickCounter = 0;
volatile uint8_t *ptrGpioInput   = (uint8_t*)(GPIOA->IDR);
```

- **Declaration order (inside function):**  
  1. Custom structures/enums  
  2. Integers (global → local)  
  3. Floats/doubles (global → local)  

---

## 5. Constants  

- Always use `const` for unmodifiable values and pointer protection.  
- Prefer `const` over `#define` when possible.  

✅ Examples:  
```c
void processBuffer(const void *ptrBuffer, const size_t length);
const float piValue = 3.14159f;
```

---

## 6. Structures  

- Use `typedef` with **PascalCase + `_t` suffix**  
- Structure variables → `camelCase`  
- Use **C99 style initialization**  

```c
typedef struct
{
    float temperature;
    float humidity;
    float pressure;
} Sensor_Data_t;

Sensor_Data_t sensorData = {
    .temperature = 25.3f,
    .humidity    = 45.8f,
    .pressure    = 1013.25f,
};
```

---

## 7. Enums  

- Use `typedef` with **PascalCase + `_e` suffix**  
- Enum members prefixed with `<EnumName_>`  

```c
typedef enum
{
    Mpu6050_FullScale_2g = 0,
    Mpu6050_FullScale_4g,
    Mpu6050_FullScale_8g,
    Mpu6050_FullScale_16g,
} Mpu6050_FullScale_e;
```

---

## 8. Conditional Flow  

- Always use braces `{}` (even for single statements)  
- Constants first in comparisons: `if(0 == value)`  
- Switch on enums when possible  
- Add `default` in switch unless enum covers all cases  
- Use **named constants** instead of magic numbers  

```c
#define MAX_RETRIES   3

for(int i = 0; i < MAX_RETRIES; i++)
{
    // retry logic
}
```

---

## 9. Macros  

- Uppercase with `_` separator  
- Double underscore `__` for grouped sets  
- Always wrap expressions and parameters in parentheses  

```c
#define GPIO__PIN_0       (1 << 0)
#define LED__ON()         (PORTB |= GPIO__PIN_0)
#define DELAY__MS(x)      (_delay_ms((x)))
#define TIME__DOUBLE(t)   ((t) * 2)
```

---

## 10. Functions  

- Naming convention: `camelCase`  
- Use library/module prefix for clarity (e.g., `adc_init()`)  
- Boolean-returning → prefix `is`  
- Callback → prefix `cb`  
- Prefer single exit point (`return` at end)  
- Doxygen documentation required  

```c
/*****************************************************************************
 * @brief   Initializes the ADC module.
 * @param   channel     ADC channel number (0–15)
 * @param   resolution  ADC resolution (8/10/12 bits)
 * @return  0 on success, -1 on error
 *****************************************************************************/
int adc_init(uint8_t channel, uint8_t resolution);
```

---

## 11. Header & Source Files  

- **File names:** lowercase, short, descriptive  
- **Header guard:** `#ifndef FILE_H / #define FILE_H / #endif`  
- **Header content order:**  
  1. File comment  
  2. Include guard  
  3. Includes (minimal, prefer forward declarations)  
  4. Types (structs, enums)  
  5. Function prototypes  
  6. Callback prototypes  

- **Source content order:**  
  1. File comment  
  2. Includes  
  3. Macros / defines  
  4. Variables  
  5. Private prototypes  
  6. Private functions  
  7. Public functions  
  8. Callbacks  

---

## 12. Comments & Documentation  

- Use English always  
- Use `//` for short inline comments  
- Use `/* ... */` for section comments  
- Use `TODO:` for unfinished code  
- All public functions → documented with **Doxygen**  

✅ Example:  
```c
// Initialize system tick
// TODO: Add support for low-power mode
```
