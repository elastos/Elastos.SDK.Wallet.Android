#include <jni.h>
#include "DidManager.h"
#include "WalletError.h"

using namespace elastos;

JNICALL jlong native_createDid(JNIEnv* env, jobject jobj, jlong obj, jint index) {
    if (!obj) return 0;

    std::shared_ptr<DidManager>* manager = (std::shared_ptr<DidManager>*)obj;

    std::shared_ptr<Did>* did = new std::shared_ptr<Did>();

    int ret = (*manager)->CreateDid(index,  did);
    if (ret != E_WALLET_C_OK) {
        return 0;
    }

    return (jlong)did;
}

JNICALL void native_destroyDidManager(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return;

    std::shared_ptr<DidManager>* manager = (std::shared_ptr<DidManager>*)obj;
    manager->reset();
    delete manager;
}

static const JNINativeMethod gMethods[] = {
        {"native_createDid", "(JI)J", (void*)native_createDid},
        {"native_destroyDidManager", "(J)V", (void*)native_destroyDidManager},
};

int registerDidManagerMethod(JNIEnv * env) {
    jclass clazz = env->FindClass("org/elastos/sdk/wallet/DidManager");
    if (clazz == NULL) return JNI_FALSE;

    int ret = env->RegisterNatives(clazz, gMethods, sizeof(gMethods)/sizeof(JNINativeMethod));
    if (ret < 0) return ret;

    return JNI_TRUE;
};

