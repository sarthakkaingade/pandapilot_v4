/****************************************************************************
 *
 *   Copyright (c) 2014 NavStik Development Team. All rights reserved.
 *   Copyright (C) 2012 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/*
 * @file pwm_output.c
 */

#include <nuttx/config.h>
#include <nuttx/arch.h>
#include <nuttx/irq.h>

#include <sys/types.h>
#include <stdbool.h>

#include <assert.h>
#include <debug.h>
#include <time.h>
#include <queue.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include <arch/board/board.h>
#include <drivers/drv_pwm_output.h>

#include <drivers/stm32/drv_pwm_servo.h>
#include <chip.h>
#include <up_internal.h>
#include <up_arch.h>

#include <stm32.h>
#include <stm32_gpio.h>
#include <stm32_tim.h>


/* PWM
*
*
* The Navstik has six PWM outputs
* The mapping are as follows :
* PB5        Servo 1 Timer 3 Channel 2 (AF2)
* PA10        Servo 2 Timer 1 channel 3 (AF1)
* PC8        Servo 3 Timer 3 Channel 3 (AF2)
* PB11        Servo 4 Timer 2 Channel 4 (AF1)
* PB1        Servo 5 Timer 3 Channel 4 (AF2)
* PB0        Servo 6 Timer 1 Channel 2 (AF1)
*
*/


__EXPORT int pwm_output_main(int argc, char *argv[]);

int        pwm_output_main(int argc, char *argv[])
{
   uint16_t value[6] = {1000,1200,1500,1700,1800,2000};
   int t=0,n=0;
   n = up_pwm_servo_init(0x3F) ; // initialising pwm
   
   up_pwm_servo_arm(1);//arming servos
 
  n = up_pwm_servo_set_rate(50); // setting update rate
   
   if (n==-ERANGE)
   printf("Rate not set \n");
   
  for (unsigned i = 0; i < PWM_SERVO_MAX_CHANNELS; i++)
      {
            
            n = up_pwm_servo_set(i,1000);
            
            if (n==-1)
            printf("Servo Not Set for RC%d \n",i+1);
            
            //value[i] = up_pwm_servo_get(i);
      }
        usleep(3000000);
         up_pwm_servo_deinit() ; // disabling pwm  
}
