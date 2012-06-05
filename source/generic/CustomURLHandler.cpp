/*
Generic implementation of the CustomURLHandler extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "CustomURLHandler_internal.h"
s3eResult CustomURLHandlerInit()
{
    //Add any generic initialisation code here
    return CustomURLHandlerInit_platform();
}

void CustomURLHandlerTerminate()
{
    //Add any generic termination code here
    CustomURLHandlerTerminate_platform();
}

void CustomURLHandlerRegister(CustomURLHandlerCallback fn)
{
	CustomURLHandlerRegister_platform(fn);
}

const char* CustomURLHandlerGetURL()
{
    return CustomURLHandlerGetURL_platform();
}
