/*
 * android-specific implementation of the CustomURLHandler extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "CustomURLHandler_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_CustomURLHandlerRegister;

s3eResult CustomURLHandlerInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("CustomURLHandler");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_CustomURLHandlerRegister = env->GetMethodID(cls, "CustomURLHandlerRegister", "()V");
    if (!g_CustomURLHandlerRegister)
        goto fail;



    IwTrace(CUSTOMURLHANDLER, ("CUSTOMURLHANDLER init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(CustomURLHandler, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void CustomURLHandlerTerminate_platform()
{
    // Add any platform-specific termination code here
}

void CustomURLHandlerRegister_platform(CustomURLHandlerCallback fn, void* userData)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_CustomURLHandlerRegister);
}
