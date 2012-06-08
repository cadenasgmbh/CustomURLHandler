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


static char* g_RetStr;
static int g_RetStrLen = 16384;

static jobject g_Obj;
static jmethodID g_CustomURLHandlerRegister;
static jmethodID g_CustomURLHandlerGetURL;

struct JavaString
{
    jstring _Ref;

    JavaString ( const char *Buffer )
    {
        //IwTrace(CUSTOMURLHANDLER, ("CTOR: const char *Buffer"));
        JNIEnv *env = s3eEdkJNIGetEnv();
        _Ref = env->NewStringUTF ( Buffer );
    }

    JavaString ( jstring Ref )
    {
        //IwTrace(CUSTOMURLHANDLER, ("CTOR: jstring Ref"));
        _Ref = Ref;
    }

    ~JavaString()
    {
        //IwTrace(CUSTOMURLHANDLER, ("DTOR"));
        JNIEnv *env = s3eEdkJNIGetEnv();
        env->DeleteLocalRef ( _Ref );
    }

    operator jstring()
    {
        //IwTrace(CUSTOMURLHANDLER, ("Operator"));
        return _Ref;
    }
};

const char* getCString(jstring str)
{
    //IwTrace(CUSTOMURLHANDLER, ("getCString"));
    JNIEnv* env = s3eEdkJNIGetEnv();
    if (!str)
        return NULL;
    //IwTrace(CUSTOMURLHANDLER, ("valid string"));
    jboolean free;
    const char* res = env->GetStringUTFChars(str, &free);
    //IwTrace(CUSTOMURLHANDLER, ("GetStringUTFChars"));
    g_RetStrLen = strlen(res);
    //IwTrace(CUSTOMURLHANDLER, ("strlen=%d", g_RetStrLen));
    s3eEdkReallocOS(g_RetStr, g_RetStrLen+1);
    g_RetStr[g_RetStrLen] = '\0';
    //IwTrace(CUSTOMURLHANDLER, ("s3eEdkReallocOS"));
    //IwTrace(CUSTOMURLHANDLER, ("cpy '%s'", res));
    strncpy(g_RetStr, res, g_RetStrLen);    
    //IwTrace(CUSTOMURLHANDLER, ("strncpy"));
    env->ReleaseStringUTFChars(str, res);
    //IwTrace(CUSTOMURLHANDLER, ("ReleaseStringUTFChars"));
    return g_RetStr;
}


s3eResult CustomURLHandlerInit_platform()
{
    //Alloc buffer for returning strings
    g_RetStr = (char*)s3eEdkMallocOS(g_RetStrLen);
    
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
    g_CustomURLHandlerGetURL = env->GetMethodID(cls, "CustomURLHandlerGetURL", "()Ljava/lang/String;");
    if (!g_CustomURLHandlerGetURL)
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
    s3eEdkFreeOS(g_RetStr);
    g_RetStr = NULL;
}

void CustomURLHandlerRegister_platform(CustomURLHandlerCallback fn)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_CustomURLHandlerRegister);
}

const char* CustomURLHandlerGetURL_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    //IwTrace(CUSTOMURLHANDLER, ("BEFORE_CALL"));
    JavaString str((jstring)env->CallObjectMethod(g_Obj, g_CustomURLHandlerGetURL));
    //IwTrace(CUSTOMURLHANDLER, ("AFTER_CALL"));
    return getCString((jstring)str);
}
