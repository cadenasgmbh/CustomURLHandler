/*
 * iphone-specific implementation of the CustomURLHandler extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "CustomURLHandler_internal.h"

s3eResult CustomURLHandlerInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void CustomURLHandlerTerminate_platform()
{
    // Add any platform-specific termination code here
}

void CustomURLHandlerRegister_platform(CustomURLHandlerCallback fn, void* userData)
{
}
