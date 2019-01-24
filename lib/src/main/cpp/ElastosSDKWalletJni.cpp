#include <jni.h>

extern int registerBlockChainNodeMethod(JNIEnv * env);
extern int registerDidMethod(JNIEnv * env);
extern int registerDidManagerMethod(JNIEnv * env);
extern int registerHDWalletMethod(JNIEnv * env);
extern int registerIdentityMethod(JNIEnv * env);
extern int registerIdentityManagerMethod(JNIEnv * env);
extern int registerTransactionMethod(JNIEnv * env);

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv * env;
    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    int ret;

    ret = registerBlockChainNodeMethod(env);
    if (ret < 0) return ret;
    ret = registerDidMethod(env);
    if (ret < 0) return ret;
    ret = registerDidManagerMethod(env);
    if (ret < 0) return ret;
    ret = registerHDWalletMethod(env);
    if (ret < 0) return ret;
    ret = registerIdentityMethod(env);
    if (ret < 0) return ret;
    ret = registerIdentityManagerMethod(env);
    if (ret < 0) return ret;
    ret = registerTransactionMethod(env);
    if (ret < 0) return ret;

    return JNI_VERSION_1_6;
};

