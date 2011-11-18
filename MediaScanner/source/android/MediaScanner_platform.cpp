/*
 * android-specific implementation of the MediaScanner extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "MediaScanner_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_Scan;

s3eResult MediaScannerInit_platform()
{
    //Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    //Get the extension class
    jclass cls = s3eEdkAndroidFindClass("MediaScanner");
    if (!cls)
        goto fail;

    //Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    //Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    //Get all the extension methods
    g_Scan = env->GetMethodID(cls, "Scan", "(Ljava/lang/String;Ljava/lang/String;)V");
    if (!g_Scan)
        goto fail;



    IwTrace(MEDIASCANNER, ("MEDIASCANNER init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteLocalRef(cls);
    
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
    
fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(MediaScanner, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void MediaScannerTerminate_platform()
{
    // Add any platform-specific termination code here
}

void Scan_platform(const char* filepath, const char* mime_type)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring filepath_jstr = env->NewStringUTF(filepath);
    jstring mime_type_jstr = env->NewStringUTF(mime_type);
    env->CallVoidMethod(g_Obj, g_Scan, filepath_jstr, mime_type_jstr);
}
