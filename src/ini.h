/**
 ******************************************************************************
 * @file       ini.h
 * @brief      API include file of ini.h.
 * @details    This file including all API functions's declare of ini.h.
 * @copyright
 *
 ******************************************************************************
 */
#ifndef INI_H_
#define INI_H_

#ifdef __cplusplus             /* Maintain C++ compatibility */
extern "C" {
#endif /* __cplusplus */
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include "config.h"

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
#define MAX_FILE_NAME_LEN   64

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
typedef struct
{
    char filename[MAX_FILE_NAME_LEN];
    int filemaxsize;
} file_t;

typedef struct
{
    int files;
    int blank;
    int islog;
    char outfile[MAX_FILE_NAME_LEN];
    char logfile[MAX_FILE_NAME_LEN];
    file_t file[DEFAULT_MAX_FILE];
} filejoint_ini_t;

/*-----------------------------------------------------------------------------
 Section: Globals
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Prototypes
 ----------------------------------------------------------------------------*/
extern int
ini_get_info(filejoint_ini_t *pinfo);

#ifdef __cplusplus      /* Maintain C++ compatibility */
}
#endif /* __cplusplus */
#endif /* INI_H_ */
/*--------------------------End of ini.h-----------------------------*/
