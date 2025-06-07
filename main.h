#ifndef MAIN_H
#define MAIN_H

#define MACHINE_START_ADDR (0x00201000U)
#define TLV_END_WORD       (0x0BD0E11DU)


/**
 * Enum to hold all possible states of the machine
 */

 enum states {
    START_STATE = 0, //go to address of chechsum and print it out
    TAG_STATE,       //print out tag number
    LENGTH_STATE,    //print out number of entries of data and store that value
    DATA_STATE,      //print out uint32_t data until lenght is 0
    END_STATE,       //print out end code and terminate machine
 };


 













#endif
