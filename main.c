/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/******************************************************************************
 * MSP432 Empty Project
 *
 * Description: An empty project that uses DriverLib
 *
 *                MSP432P401
 *             ------------------
 *         /|\|                  |
 *          | |                  |
 *          --|RST               |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 * Author: 
*******************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "main.h"


/* Ensure variable is static */
enum states curr_state;
uint32_t* curr_addr = MACHINE_START_ADDR;


int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();
    
    curr_state = START_STATE;
    /* Holds number of entries in that tag block */
    uint16_t numEntries;

    while(1)
    {
        /* Define the state machine */
        switch (curr_state) {
            case START_STATE:
                /* Print checksum value */
                printf("%08x\n", *curr_addr);

                /* Increment curr_addr by 4 bytes*/
                curr_addr++;

                /* If value at location not magic number go to TAG_STATE, else END_STATE */
                if ((*curr_addr) != TLV_END_WORD) 
                    curr_state = TAG_STATE;
                else 
                    curr_state = END_STATE;

            break;

            case TAG_STATE:
                /* Print tag info number*/
                printf("%08x ", *curr_addr);
                
                /* Increment by four bytes */
                curr_addr++;

                curr_state = LENGTH_STATE; 
            break;

            case LENGTH_STATE:
                /* Store number of entries */
                numEntries = *curr_addr;

                /* print length in hex */
                printf("%x ", *curr_addr);

                /* Increment by four bytes */
                curr_addr++;

                curr_state = DATA_STATE;


            break;

            case DATA_STATE:
                /* As long as numEntries > 0 print entry and increment*/
                while (numEntries > 0) {
                    /* print out data entry */
                    printf("%08x ", *curr_addr);

                    /* Decrement numEnries and go to next address*/
                    numEntries--;
                    curr_addr++;
                }

                /*Flush buffer*/
                printf("\n");

                /* If value at location not magic number go to TAG_STATE, else END_STATE */
                if ((*curr_addr) != TLV_END_WORD) 
                    curr_state = TAG_STATE;
                else 
                    curr_state = END_STATE;


            break;
            
            case END_STATE:
                /* Print out the ma*/
                printf("%08x ", *curr_addr);

                return 0;


            default:
                /* Raise exception*/
                return -1;
        }
    }
}
     
