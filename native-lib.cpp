#include <jni.h>
#include <string>
#include <android/log.h>
#include <dlfcn.h>
#include "Dobby/includes/dobby.h"

#define LOG_TAG "Xz-log"
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG  , LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__))




int Csfun(int a,int b,int c){
    a = a + 8;
    b = b + c;
    return a + b + c;
}
int hookfun(int a,int b,int c){
    LOGD("DobbyHook");
    return 666;
}



extern "C" JNIEXPORT jstring
JNICALL
Java_com_xz_reservance_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    int a = 1;
    int b = 2;
    int c = a + b;
    int d = Csfun(a,b,c);
    LOGD("原始函数调用后，c的值:%d",d);
    // 当前函数地址
    void* addr = (void*)&Java_com_xz_reservance_MainActivity_stringFromJNI;
    //实现Dobby Hook
    void *dobby_hook = dlsym(RTLD_DEFAULT,"DobbyHook");
    if(!dobby_hook){
        LOGE("无法获取dobby_hook函数指针");
    }
    void *orig_fun = (void *)Csfun;
    void *hook_fun = (void *)hookfun;
    LOGD("原函数指针:%p, hook函数指针:%p",orig_fun,hook_fun);
    LOGD("不添加void*的原函数指针:%p, hook函数指针:%p", Csfun,hook_fun);
    int res = DobbyHook(orig_fun,hook_fun, nullptr);
    if(res == 0){
        LOGD("DobbyHook succeed 成功替换");
    }
    d = Csfun(a,b,c);
    LOGD("HOOK后返回结果为%d",d);
    // 通过 dladdr 获取符号信息
    Dl_info info;
    if (dladdr(addr, &info)) {
        LOGD("函数所在so文件: %s", info.dli_fname);
        LOGD("so加载基址: %p", info.dli_fbase);
        LOGD("当前函数地址: %p", addr);
        LOGD("符号名称: %s", info.dli_sname ? info.dli_sname : "(null)");
    } else {
        LOGD("dladdr 获取信息失败");
    }
    LOGD("c的值: %d", c);
    return env->NewStringUTF(hello.c_str());
}


