#include <jni.h>
#include <memory>
#include <string>
#include "Did.h"
#include "HDWallet.h"
#include "WalletError.h"
#include "Log.hpp"
#include <codecvt>
#include <locale>

using namespace elastos;

JNICALL jstring native_getId(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return env->NewStringUTF("");

    std::shared_ptr<Did>* did = (std::shared_ptr<Did>*)obj;

    std::string id = (*did)->GetId();
    return env->NewStringUTF(id.c_str());
}

JNICALL jstring native_signInfo(JNIEnv* env, jobject jobj, jlong obj, jstring seed, jstring json) {
    if (!obj) return env->NewStringUTF("");

    std::shared_ptr<Did>* did = (std::shared_ptr<Did>*)obj;

    const char* seedStr = env->GetStringUTFChars(seed, nullptr);
    const char* jsonStr = env->GetStringUTFChars(json, nullptr);
    std::string signedInfo = (*did)->SignInfo(seedStr, std::string(jsonStr));
    env->ReleaseStringUTFChars(seed, seedStr);
    env->ReleaseStringUTFChars(json, jsonStr);

    return env->NewStringUTF(signedInfo.c_str());
}

JNICALL jstring native_setInfo(JNIEnv* env, jobject jobj, jlong obj, jstring seed, jstring json, jlong wallet) {
    if (!obj || !wallet) return env->NewStringUTF("");

    std::shared_ptr<Did>* did = (std::shared_ptr<Did>*)obj;
    std::shared_ptr<HDWallet>* hdWallet = (std::shared_ptr<HDWallet>*)wallet;


    const char* seedStr = env->GetStringUTFChars(seed, nullptr);
    const char* jsonStr = env->GetStringUTFChars(json, nullptr);
    std::string txid = (*did)->SetInfo(seedStr, jsonStr, *hdWallet);
    env->ReleaseStringUTFChars(seed, seedStr);
    env->ReleaseStringUTFChars(json, jsonStr);

    return env->NewStringUTF(txid.c_str());
}

JNICALL jint native_syncInfo(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return E_WALLET_C_INVALID_ARGUMENT;

    std::shared_ptr<Did>* did = (std::shared_ptr<Did>*)obj;
    return (*did)->SyncInfo();;
}

JNICALL jstring native_getInfo(JNIEnv* env, jobject jobj, jlong obj, jstring key) {
    if (!obj) return env->NewStringUTF("");

    std::shared_ptr<Did>* did = (std::shared_ptr<Did>*)obj;

    const char* keyStr = env->GetStringUTFChars(key, nullptr);
    std::string value = (*did)->GetInfo(keyStr);
    env->ReleaseStringUTFChars(key, keyStr);

    return env->NewStringUTF(value.c_str());
}

JNICALL void native_destroyDid(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return;

    std::shared_ptr<Did>* did = (std::shared_ptr<Did>*)obj;
    did->reset();
    delete did;
}

static const JNINativeMethod gMethods[] = {
        {"native_getId", "(J)Ljava/lang/String;", (void*)native_getId},
        {"native_signInfo", "(JLjava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void*)native_signInfo},
        {"native_setInfo", "(JLjava/lang/String;Ljava/lang/String;J)Ljava/lang/String;", (void*)native_setInfo},
        {"native_syncInfo", "(J)I", (void*)native_syncInfo},
        {"native_getInfo", "(JLjava/lang/String;)Ljava/lang/String;", (void*)native_getInfo},
        {"native_destroyDid", "(J)V", (void*)native_destroyDid},
};

int registerDidMethod(JNIEnv * env) {
    jclass clazz = env->FindClass("org/elastos/sdk/wallet/Did");
    if (clazz == NULL) return JNI_FALSE;

    int ret = env->RegisterNatives(clazz, gMethods, sizeof(gMethods)/sizeof(JNINativeMethod));
    if (ret < 0) return ret;

    return JNI_TRUE;
};


