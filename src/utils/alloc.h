#ifndef _ALLOC_H
    #define _ALLOC_H

    #include <stdio.h>
    #include <stdlib.h>

    #if defined( ESP32 ) && defined( BOARD_HAS_PSRAM )
            #include <stddef.h>
            #include <stdbool.h>
            #include <esp32-hal-psram.h>

            #define MALLOC         ps_malloc            /** @brief malloac from PSRAM */
            #define CALLOC         ps_calloc            /** @brief calloc from PSRAM */
            #define REALLOC        ps_realloc           /** @brief realloc from PSRAM */
        
            #define     ASSERT( test, message, ... ) do { if( !(test) ) { log_e( message, ##__VA_ARGS__); while( true ); } } while ( 0 )
    #else
            #include "logging.h"
            
            #define MALLOC         malloc               /** @brief malloac from normal heap */
            #define CALLOC         calloc               /** @brief calloc from normal heap */
            #define REALLOC        realloc              /** @brief realloc from normal heap */

            #define     ASSERT( test, message, ... ) do { if( !(test) ) { log_e( message, ##__VA_ARGS__); exit( 1 ); } } while ( 0 )
    #endif

    #define     MALLOC_ASSERT( size, message, ... ) ( { void *p = (void*)MALLOC( size ); ASSERT( p, message, ##__VA_ARGS__ ); p; } ) 
    #define     CALLOC_ASSERT( nmemb, size, message, ... ) ( { void *p = (void*)CALLOC( nmemb, size ); ASSERT( p, message, ##__VA_ARGS__ ); p; } ) 
    #define     REALLOC_ASSERT( ptr, size, message, ... ) ( { void *p = (void*)REALLOC( ptr, size ); ASSERT( p, message, ##__VA_ARGS__ ); p; } ) 

#endif // _ALLOC_H
