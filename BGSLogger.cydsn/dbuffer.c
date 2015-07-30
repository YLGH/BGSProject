/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <dbuffer.h>

uint16 dbuffer[DBUFFER_SIZE];
uint16 dbufwriteptr = 0;
uint16 dbufreadptr = 0;

uint16 dbufsize(){
    if(dbufwriteptr<dbufreadptr){
        return (dbufwriteptr+DBUFFER_SIZE) - dbufreadptr;
    }else{
        return dbufwriteptr - dbufreadptr;
    }
}

uint16 dbufread(){
    if(dbufreadptr == dbufwriteptr) return -1; // buffer empty
    uint16 retval = dbuffer[dbufreadptr];
    dbufreadptr += 1;
    if(dbufreadptr>=DBUFFER_SIZE) dbufreadptr = 0;
    return retval;
}

uint8 dbufwrite(uint16 val){
    if ((dbufwriteptr+1) % DBUFFER_SIZE == dbufreadptr) return 0; // buffer full
    dbuffer[dbufwriteptr] = val;
    dbufwriteptr += 1;
    if(dbufwriteptr>=DBUFFER_SIZE) dbufwriteptr = 0;
    return 1;
}

/* [] END OF FILE */
