/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */

#include "s3eExt.h"
#include "IwDebug.h"

#include "CustomURLHandler.h"

/**
 * Definitions for functions types passed to/from s3eExt interface
 */
typedef       void(*CustomURLHandlerRegister_t)(CustomURLHandlerCallback fn);
typedef const char*(*CustomURLHandlerGetURL_t)();

/**
 * struct that gets filled in by CustomURLHandlerRegister
 */
typedef struct CustomURLHandlerFuncs
{
    CustomURLHandlerRegister_t m_CustomURLHandlerRegister;
    CustomURLHandlerGetURL_t m_CustomURLHandlerGetURL;
} CustomURLHandlerFuncs;

static CustomURLHandlerFuncs g_Ext;
static bool g_GotExt = false;
static bool g_TriedExt = false;
static bool g_TriedNoMsgExt = false;

static bool _extLoad()
{
    if (!g_GotExt && !g_TriedExt)
    {
        s3eResult res = s3eExtGetHash(0x40d7e8d1, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        else
            s3eDebugAssertShow(S3E_MESSAGE_CONTINUE_STOP_IGNORE, "error loading extension: CustomURLHandler");
        g_TriedExt = true;
        g_TriedNoMsgExt = true;
    }

    return g_GotExt;
}

static bool _extLoadNoMsg()
{
    if (!g_GotExt && !g_TriedNoMsgExt)
    {
        s3eResult res = s3eExtGetHash(0x40d7e8d1, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        g_TriedNoMsgExt = true;
        if (g_TriedExt)
            g_TriedExt = true;
    }

    return g_GotExt;
}

s3eBool CustomURLHandlerAvailable()
{
    _extLoadNoMsg();
    return g_GotExt ? S3E_TRUE : S3E_FALSE;
}

void CustomURLHandlerRegister(CustomURLHandlerCallback fn)
{
    IwTrace(CUSTOMURLHANDLER_VERBOSE, ("calling CustomURLHandler[0] func: CustomURLHandlerRegister"));

    if (!_extLoad())
        return;

    g_Ext.m_CustomURLHandlerRegister(fn);
}

const char* CustomURLHandlerGetURL()
{
    IwTrace(CUSTOMURLHANDLER_VERBOSE, ("calling CustomURLHandler[1] func: CustomURLHandlerGetURL"));

    if (!_extLoad())
        return S3E_RESULT_ERROR;

    return g_Ext.m_CustomURLHandlerGetURL();
}
