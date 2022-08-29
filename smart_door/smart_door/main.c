/*
 * smart_door.c
 *
 * Created: 8/26/2022 1:50:03 PM
 * Author : mohye
 */ 

#include "APPLICATION/APP_INTERFACE.h"
int main(void)
{
	/*initializing the app*/
	 INITIALIZE_ALL();

    while (1) 
    {
		/*implementing the app*/
		AppWorking();
    }
}

