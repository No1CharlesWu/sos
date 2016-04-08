#ifndef	_TYPE_H_
#define	_TYPE_H_

#ifndef NULL
    #define NULL 0
#endif

#ifndef TRUE
    #define TRUE    1
    #define FALSE   0
#endif
typedef  	 int		size_t; 

/* Represents true-or-false values */
typedef int bool;

/* Explicitly-sized versions of integer types */
typedef          char       int8_t;
typedef unsigned char       uint8_t;
typedef          short      int16_t;
typedef unsigned short      uint16_t;
typedef          int        int32_t;
typedef unsigned int        uint32_t;

#endif
