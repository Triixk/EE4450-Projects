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
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
 

void random_4digit(int n, int *digits);
int numbers(int *digits);
bool check_victory(int *digits);
void blink(int number);

int main(void)
{
    uint16_t    count = 0;
    bool preState;
    bool curState;
    
    int number;
    int dig[4];
    
    //Initial value for preState
    preState = 1;
    
    CyGlobalIntEnable; /* Enable global interrupts. */
 
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LED_Init();
    LED_Enable();
    LED_Write7SegNumberDec(0, 0, 4, LED_ZERO_PAD);
 
    for(;;)
    {
        random_4digit(0,dig);
        number = numbers(dig);
        LED_Write7SegNumberDec(number, 0, 4, LED_ZERO_PAD); // Display a number from com0 for 4 digits
        CyDelay(100);
        
        //Read current switch state
        curState = nSW_Read();
        
        //Detect when switch pushed
        if ( (preState == 1) && (curState == 0)){
            //Stop randomize one number at a time with 2 second interval
            for (int i = 1;i<4;i++){
                count = 20;
                while(count--){
                    random_4digit(i,dig);
                    number = numbers(dig);
                    LED_Write7SegNumberDec(number, 0, 4, LED_ZERO_PAD); // Display a number from com0 for 4 digits
                    CyDelay(100); 
                }
            }
            //Check for winning number
            if (check_victory(dig)){
                while(nSW_Read()){      //Blink while button not pushed, button press will restart program
                    blink(number);   
                }
                while(!nSW_Read());
            }
            else{                       //Do nothing while button not pushed, button press will restart program
                while(nSW_Read());
                while(!nSW_Read());
            }
        }
        //Update the curState to preState
        preState = curState;
        
        
    }
}

//Function to randomize 4 digits and save it in digits
void random_4digit(int n, int *digits){
    for(int i = n;i<4;i++){
        digits[i] = rand() % 10;
        }
}

//Function that turns 4 digit into a single number and return it
int numbers(int *digits){
    return digits[0]*1000+digits[1]*100+digits[2]*10+digits[3];
}
//Function to check if final number contais a 7 or are 4 identical numbers
bool check_victory(int *digits){
    for (int i=0;i<4;i++){
        if (digits[i] == 7)
            return true;        
    }
    int count = 1;
    for (int i=1;i<4;i++){
        if (digits[i] == digits[i-1])
            count++;        
    }
    return count == 4;
}

//Function to blink the display with given number
void blink(int number){
     for(int i = 0;i<4;i++){
            LED_ClearDisplay(i);
        }
        CyDelay(100);
        LED_Write7SegNumberDec(number, 0, 4, LED_ZERO_PAD);
        CyDelay(100);
}

/* [] END OF FILE */
