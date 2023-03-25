#include "functions.h"
#include <kipr/wombat.h>
#define threshold 1935

void slowServo(int servo, int endAngle, int speed) 
{    
  if (get_servo_position(servo) > endAngle)
  {
	   enable_servo(servo);
     while (get_servo_position(servo) > endAngle)
		   {

  			set_servo_position(servo, get_servo_position(servo)-2);
  			msleep(speed);


		   }
	  ao();
  }
  else if (get_servo_position(servo) < endAngle)
    {
	   enable_servo(servo);
     while (get_servo_position(servo) < endAngle)
		   {

  			set_servo_position(servo, get_servo_position(servo)+2);
  			msleep(speed);


		    }
	   ao();
    }
}


void line_follow(int miliseconds)
{
    while((get_create_lbump() == 0) && (get_create_rbump() == 0))
    {
        if(get_create_lfcliff_amt()<threshold)
        {
            create_drive_direct(0,100);
            msleep(miliseconds);
        }
		else
        {
            create_drive_direct(100,0);
            msleep(miliseconds);
        }
    }
}

void turnDegrees(int deg)
{
    set_create_total_angle(0);
    if (deg>0)
    {
        while (get_create_total_angle() > deg)
        {
            create_drive_direct(100,-100);
        }
   	create_drive_direct(0,0);
    }
    else if (deg<0)
    {
        while (get_create_total_angle() > deg)
        {
            create_drive_direct(-100,100);
        }
        create_drive_direct(0,0);
    }
}

void drive_until_black()
{
    while(get_create_rfcliff_amt() > 1935)
    {
        create_drive_direct(100,100);
    }
}
void drive_until_bump_left()
{
    while(get_create_lbump() == 0)
    {
        create_drive_direct(100,100);
        create_drive_direct(0,0);
    }
}
void startup()
{
  wait_for_light(1);
  shut_down_in(115);
}