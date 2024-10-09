#include "base64.h"
#include <assert.h>
#include <stdlib.h>
#include <jni.h>

#define JNIREG_CLASS "com/setting/MySettings"

__attribute__((section (".appurl"))) JNICALL jstring getAppUrlC(JNIEnv *env, jclass obj) {
    jstring str = "fmitv_";
    (*env)-> DeleteLocalRef(env, str);
    char* url = "aHR0cDovLzExMS4yMjkuMjUzLjQwOjU1MQ==";
    char* urlstr = base64_decode(url, strlen(url));
    return (jstring)(*env)-> NewStringUTF(env, urlstr);
}

__attribute__((section (".appsign"))) JNICALL jstring getAppSignC(JNIEnv *env, jclass obj) {
    //^u%dFUQXi%7jwyS$wo4TfGQd!XGRibrL89nBt$xBBMPG&Dv*rAOV268SXG1%D7lF0kW1cyRzYTE8Qa3rqS#reaHXB3*&tJLm9fy@S6svg&etMqcbADqoovN3g0WKPk9&
    char* sign = "XnUlZEZVUVhpJTdqd3lTJHdvNFRmR1FkIVhHUmlickw4OW5CdCR4QkJNUEcmRHYqckFPVjI2OFNYRzElRDdsRjBrVzFjeVJ6WVRFOFFhM3JxUyNyZWFIWEIzKiZ0SkxtOWZ5QFM2c3ZnJmV0TXFjYkFEcW9vdk4zZzBXS1BrOSY=";
    char* signstr = base64_decode(sign, strlen(sign));
    return (jstring)(*env)-> NewStringUTF(env, signstr);
}

__attribute__((section (".appkey"))) JNICALL jstring getAppKeyC(JNIEnv *env, jclass obj) {
    char* appkey = "ISNmbWl0diMyODI4OCMh";
    char* appkeystr = base64_decode(appkey, strlen(appkey));
    return (jstring)(*env)-> NewStringUTF(env, appkeystr);
}

static JNINativeMethod gMethods[] = {
        { "getAppUrl", "()Ljava/lang/String;", (void*)getAppUrlC},
        { "getAppSign", "()Ljava/lang/String;", (void*)getAppSignC},
        { "getAppKey", "()Ljava/lang/String;", (void*)getAppKeyC},
};

static int registerNativeMethods(JNIEnv* env, const char* className,
                                 JNINativeMethod* gMethods, int numMethods)
{
    jclass clazz;
    clazz = (*env)->FindClass(env, className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

static int registerNatives(JNIEnv* env)
{
    if (!registerNativeMethods(env, JNIREG_CLASS, gMethods,
                               sizeof(gMethods) / sizeof(gMethods[0])))
        return JNI_FALSE;

    return JNI_TRUE;
}


jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);

    if (!registerNatives(env)) {
        return -1;
    }

    result = JNI_VERSION_1_4;

    return result;
}

