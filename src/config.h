/**
 ******************************************************************************
 * @file       config.h
 * @brief      配置文件
 * @details    This file including all API functions's declare of config.h.
 * @copyright
 *
 ******************************************************************************
 */
#ifndef CONFIG_H_
#define CONFIG_H_ 

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
#define DEFAULT_MAX_FILE        (5u)                /**< 最大文件合并数量 */
#define DEFAULT_INI_FILE        "./FileJoint.ini"   /**< 默认配置文件 */
#define DEFAULT_DEST_FILE       "./FLASH.bin"       /**< 合并后文件 */
#define DEFAULT_BOOT_FILE       "./boot.bin"        /**< boot文件 */
#define DEFAULT_APP_FILE        "./sp5.bin"         /**< app文件 */
#define DEFAULT_BOOT_SIZE       (32 * 1024)         /**< boot大小 */
#define DEFAULT_APP_SIZE        ((1024 - 32) * 1024)/**< app大小 */

#define DEFAULT_LOG_ON          (1u)                /**< 默认打开日志记录 */
#define DEFAULT_LOG_FILE_NAME   "./FileJoint.log"   /**< 默认日志文件 */

#endif /* CONFIG_H_ */
/*-----------------------------End of config.h-------------------------------*/
