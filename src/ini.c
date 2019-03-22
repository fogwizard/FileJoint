/**
 ******************************************************************************
 * @file      ini.c
 * @brief     C Source file of ini.c.
 * @details   This file including all API functions's
 *            implement of ini.c.
 *
 * @copyright
 ******************************************************************************
 */

/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "iniparser.h"
#include "ini.h"

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Global Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief   创建默认配置文件
 * @param[in]  None
 * @param[out] None
 * @retval     None
 ******************************************************************************
 */
static void
create_example_ini_file(void)
{
    FILE    *   ini ;

    ini = fopen(DEFAULT_INI_FILE, "w");
    fprintf(ini,
            "#文件拼接配置By LiuNing\n"
            "[cfg]\n"
            "#文件总数量(一般填2,最大5)\n"
            "Files = 2\n"
            "#空白填充数字(0~255,大于255直接为255)\n"
            "Blank = 255\n"
            "#是否记录日志(0:不记录1:记录)\n"
            "IsLog = 0\n"
            "#日志文件名\n"
            "LogFile = ./FileJoin.log\n"
            "#输出文件名\n"
            "OutFile = ./FLASH.bin\n"
            "\n"
            "#文件1\n"
            "#0x800-->32K\n"
            "[f1]\n"
            "FileName    = ./boot.bin\n"
            "FileMaxSize = 0x8000\n"
            "\n"
            "#文件2\n"
            "#0xf8000-->992K\n"
            "#0xb8000-->736K\n"
            "#0x7f800-->510K\n"
            "[f2]\n"
            "FileName    = ./sp5.bin\n"
            "FileMaxSize = 0xf8000\n");
    fclose(ini);
}

/**
 ******************************************************************************
 * @brief   从配置文件中获取文件合并信息
 * @param[out] *pinfo   : 返回info
 *
 * @retval     -1 失败
 * @retval      0 成功
 ******************************************************************************
 */
int
ini_get_info(filejoint_ini_t *pinfo)
{
    dictionary  *   ini ;
    char *pstr = NULL;
    char ftmp[32];
    int i;

    memset(pinfo, 0x00, sizeof(*pinfo));

    ini = iniparser_load(DEFAULT_INI_FILE);
    if (NULL == ini) {
        create_example_ini_file();
        ini = iniparser_load(DEFAULT_INI_FILE);
        if (ini == NULL) {
            return -1;
        }
    }

    iniparser_dump(ini, NULL);//stderr
    pinfo->files = iniparser_getint(ini, "cfg:Files", -1);
    if ((pinfo->files > DEFAULT_MAX_FILE) || (pinfo->files <= 0)) {
        iniparser_freedict(ini);
        return -1;
    }
    pinfo->blank = iniparser_getint(ini, "cfg:Blank", -1);
    if (pinfo->blank < 0) {
        iniparser_freedict(ini);
        return -1;
    }
    if (pinfo->blank > 255) {
        pinfo->blank = 255;
    }
    pinfo->islog = iniparser_getint(ini, "cfg:IsLog", -1);
    if (pinfo->islog == -1) {
        iniparser_freedict(ini);
        return -1;
    }
    pstr = iniparser_getstring(ini, "cfg:LogFile", NULL);
    if (pstr == NULL) {
        iniparser_freedict(ini);
        return -1;
    }
    strncpy(pinfo->logfile, pstr, sizeof(pinfo->logfile));

    pstr = iniparser_getstring(ini, "cfg:OutFile", NULL);
    if (pstr == NULL) {
        strncpy(pinfo->outfile, DEFAULT_DEST_FILE, sizeof(pinfo->outfile));
    } else {
        strncpy(pinfo->outfile, pstr, sizeof(pinfo->logfile));
    }

    /* 扫描所以文件 */
    for (i = 0; i < pinfo->files; i++) {
        sprintf(ftmp, "f%d:FileName", i + 1);
        pstr = iniparser_getstring(ini, ftmp, NULL);
        if (pstr == NULL) {
            iniparser_freedict(ini);
            return -1;
        }
        strncpy(pinfo->file[i].filename, pstr, sizeof(pinfo->file[i].filename));

        sprintf(ftmp, "f%d:FileMaxSize", i + 1);
        pinfo->file[i].filemaxsize = iniparser_getint(ini, ftmp, -1);
        if (pinfo->file[i].filemaxsize == -1) {
            iniparser_freedict(ini);
            return -1;
        }
    }

    iniparser_freedict(ini);

    return 0;
}
/*----------------------------ini.c--------------------------------*/
