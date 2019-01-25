#include <jni.h>
#include <memory>
#include "Identity.h"
#include "WalletError.h"

using namespace elastos;

JNICALL jlong native_createSingleAddressWallet(JNIEnv* env, jobject jobj, jlong obj, jstring seed, long node) {
    if (!obj) return 0;

    std::shared_ptr<Identity>* identity = (std::shared_ptr<Identity>*)obj;

    std::shared_ptr<HDWallet>* wallet = new std::shared_ptr<HDWallet>();

    std::shared_ptr<BlockChainNode>* pNode = (std::shared_ptr<BlockChainNode>*)node;
    if (!pNode) return 0;

    const char* seedStr = env->GetStringUTFChars(seed, nullptr);
    int ret = (*identity)->CreateSingleAddressWallet(seedStr, *pNode, wallet);
    env->ReleaseStringUTFChars(seed, seedStr);
    if (ret != E_WALLET_C_OK) {
        delete wallet;
        return 0;
    }

    return (jlong)wallet;
}

JNICALL jlong native_createWallet(JNIEnv* env, jobject jobj, jlong obj, jstring seed, jint coinType, long node) {
    if (!obj) return 0;

    std::shared_ptr<Identity>* identity = (std::shared_ptr<Identity>*)obj;

    std::shared_ptr<HDWallet>* wallet = new std::shared_ptr<HDWallet>();

    std::shared_ptr<BlockChainNode>* pNode = (std::shared_ptr<BlockChainNode>*)node;
    if (!pNode) return 0;

    const char* seedStr = env->GetStringUTFChars(seed, nullptr);
    int ret = (*identity)->CreateWallet(seedStr, coinType, *pNode, wallet);
    env->ReleaseStringUTFChars(seed, seedStr);
    if (ret != E_WALLET_C_OK) {
        delete wallet;
        return 0;
    }

    return (jlong)wallet;
}

JNICALL jlong native_createDidManager(JNIEnv* env, jobject jobj, jlong obj, jstring seed) {
    if (!obj) return 0;

    std::shared_ptr<Identity>* identity = (std::shared_ptr<Identity>*)obj;

    std::shared_ptr<DidManager>* manager = new std::shared_ptr<DidManager>();

    const char* seedStr = env->GetStringUTFChars(seed, nullptr);
    int ret = (*identity)->CreateDidManager(seedStr, manager);
    env->ReleaseStringUTFChars(seed, seedStr);
    if (ret != E_WALLET_C_OK) {
        delete manager;
        return 0;
    }

    return (jlong)manager;
}


JNICALL void native_destroyIdentity(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return;

    std::shared_ptr<Identity>* identity = (std::shared_ptr<Identity>*)obj;
    identity->reset();
    delete identity;
}


static const JNINativeMethod gMethods[] = {
        {"native_createSingleAddressWallet", "(JLjava/lang/String;J)J", (void*)native_createSingleAddressWallet},
        {"native_createWallet", "(JLjava/lang/String;IJ)J", (void*)native_createWallet},
        {"native_createDidManager", "(JLjava/lang/String;)J", (void*)native_createDidManager},
        {"native_destroyIdentity", "(J)V", (void*)native_destroyIdentity},
};

int registerIdentityMethod(JNIEnv * env) {
    jclass clazz = env->FindClass("org/elastos/sdk/wallet/Identity");
    if (clazz == NULL) return JNI_FALSE;

    int ret = env->RegisterNatives(clazz, gMethods, sizeof(gMethods)/sizeof(JNINativeMethod));
    if (ret < 0) return ret;

    return JNI_TRUE;
};


