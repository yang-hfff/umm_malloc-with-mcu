#ifndef __LOGS_H
#define __LOGS_H


/*
 * @author YangHaifeng
 * @brief this file is used to print log information with various of device and mode
 *  1. it can turn off and turn on the functiion of log prinnt by set the macro USE_LOG to 0 or 1
 *  2. it support color mode(if you serial assistance support) and normal(without color) mode.
 *  3. it can use different device to print by chang the marco **LOG_PRINT**
 * @note here are some thing that you should pay close attention
 *  1. the type of function which LOG_PRINT support must be int (*)(const char *,...)
 *  2. USE_COLR_MODE set 1 have real effect only on the case of print device support
 */


/*------config area start------*/

#define USE_LOG         1

#define USE_COLR_MODE   0

#define LOG_PRINT       printf

/*------config area end------*/





#if USE_COLR_MODE
    #define COLR_SET(dis_mode,fwd_clor,bak_clor) printf("\033["#dis_mode";"#fwd_clor";"#bak_clor"m")
#else 
    #define COLR_SET(dis_mode,fwd_clor,bak_clor) (void)0
#endif

#if USE_LOG == 1  
    /*---general log---*/
    #define LOG_E(fmt,...)  COLR_SET(0,31,40),\
                            LOG_PRINT("[ERROR ][%s:%d][%s]"fmt,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__),\
                            COLR_SET(0,0,0)
    #define LOG_W(fmt,...)  COLR_SET(0,33,40),\
                            LOG_PRINT("[WARN  ][%s:%d][%s]"fmt,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__),\
                            COLR_SET(0,0,0)
    #define LOG_I(fmt,...)  COLR_SET(0,36,40),\
                            LOG_PRINT("[INFO  ][%s:%d][%s]"fmt,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__),\
                            COLR_SET(0,0,0)
    #define LOG_D(fmt,...)  COLR_SET(0,32,40),\
                            LOG_PRINT("[DEBUG ][%s:%d][%s]"fmt,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__),\
                            COLR_SET(0,0,0)
                            
                            
    /*---expanded log---*/
    #define LOG_F(fmt,...)  COLR_SET(0,35,40),\
                            LOG_PRINT("[FATAL ][%s:%d][%s]"fmt,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__),\
                            COLR_SET(0,0,0)
    #define LOG_V(fmt,...)  COLR_SET(0,34,40),\
                            LOG_PRINT("[VERBO ][%s:%d][%s]"fmt,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__),\
                            COLR_SET(0,0,0)                       
#else
    #define LOG_E(fmt,...)  (void)0    
    #define LOG_W(fmt,...)  (void)0    
    #define LOG_I(fmt,...)  (void)0   
    #define LOG_D(fmt,...)  (void)0        
    #define LOG_F(fmt,...)  (void)0   
    #define LOG_V(fmt,...)  (void)0    
#endif



#endif /*__LOGS_H*/




