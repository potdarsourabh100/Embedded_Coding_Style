# Embedded C Style Guide – Quick Reference  

✅ **Formatting**  
- Standard: `C11`  
- Indent: 4 spaces (no tabs)  
- Max line: 120 chars  
- Braces: always on next line  
- Space after `, ; = + - * /`  

✅ **Variables**  
- Naming: `camelCase`  
- Descriptive, no abbreviations  
- One per line, align groups  
- Prefixes: `ptr`, `pp`, `glb`, `gptr`  
- `volatile` for ISR/shared registers  

✅ **Constants**  
- Prefer `const` over `#define`  
- Use `const void *ptr` for unmodifiable pointers  

✅ **Structures**  
- `typedef` with PascalCase + `_t`  
- Init with C99 style (`.field = value`)  

✅ **Enums**  
- `typedef` with PascalCase + `_e`  
- Members prefixed with `EnumName_`  

✅ **Conditional Flow**  
- Always use braces `{}`  
- Constant first in comparisons: `if(0 == var)`  
- Use enums in switches  
- No magic numbers → use `#define`  

✅ **Macros**  
- ALL_CAPS with `_`  
- Double underscore `__` for groups  
- Wrap operations/params in parentheses  

✅ **Functions**  
- Naming: `camelCase`  
- Prefix with module name (`adc_init`)  
- Boolean: start with `is...`  
- Callback: start with `cb...`  
- Document with Doxygen  

✅ **Files**  
- Filenames: lowercase, descriptive  
- Header: comment → guard → includes → types → prototypes  
- Source: comment → includes → defines → vars → privates → publics → callbacks  

✅ **Comments**  
- English only  
- `//` inline, `/*...*/` sections  
- Use `TODO:` for pending work  
- Doxygen for functions  
