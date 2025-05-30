/**
 * @file        module_name.h
 * @author      Your Name
 * @brief       Description of what this module does.
 * @version     1.0.0
 * @date        2025-05-31
 */

#ifndef MODULE_NAME_H
#define MODULE_NAME_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* Types ---------------------------------------------------------------------*/

/**
 * @brief Structure to hold module data.
 */
typedef struct
{
    uint16_t exampleValue;
    float    exampleRate;
    bool     isEnabled;
} ModuleName_Data_t;

/**
 * @brief Enum for module status.
 */
typedef enum
{
    ModuleName_Status_Idle = 0,
    ModuleName_Status_Active,
    ModuleName_Status_Error,
} ModuleName_Status_e;

/* Function Prototypes -------------------------------------------------------*/

/**
 * @brief Initialize the module.
 * @return true if initialization succeeds, false otherwise
 */
bool moduleName_init(void);

/**
 * @brief Set parameters of the module.
 * @param[in] data Pointer to input data structure
 * @return true if parameters are set successfully, false otherwise
 */
bool moduleName_setParameters(const ModuleName_Data_t *ptrData);

/**
 * @brief Get module status.
 * @return Current module status
 */
ModuleName_Status_e moduleName_getStatus(void);

/* Callback Prototypes -------------------------------------------------------*/

/**
 * @brief Callback called when data is updated.
 */
void cbModuleName_onUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* MODULE_NAME_H */
