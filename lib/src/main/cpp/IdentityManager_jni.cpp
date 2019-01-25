#include <jni.h>
#include <string>
#include "IdentityManager.h"
#include "WalletError.h"
#include "Log.hpp"

using namespace elastos;

JNICALL jstring native_getMnemonic(JNIEnv* env, jobject jobj, jstring language, jstring words) {
    const char* lan = env->GetStringUTFChars(language, nullptr);
    const char* wordsStr = env->GetStringUTFChars(words, nullptr);

    std::string mnemonic = IdentityManager::GetMnemonic(lan, wordsStr);
    env->ReleaseStringUTFChars(language, lan);
    env->ReleaseStringUTFChars(words, wordsStr);

    return env->NewStringUTF(mnemonic.c_str());
}

JNICALL jstring native_getSeed(JNIEnv* env, jobject jobj, jstring mnemonic, jstring language, jstring words, jstring mnemonicPassword) {
    const char* lan = env->GetStringUTFChars(language, nullptr);
    const char* wordsStr = env->GetStringUTFChars(words, nullptr);
    const char* mne = env->GetStringUTFChars(mnemonic, nullptr);
    const char* mnePwd = env->GetStringUTFChars(mnemonicPassword, nullptr);

    std::string seed = IdentityManager::GetSeed(mne, lan, wordsStr, mnePwd);
    env->ReleaseStringUTFChars(language, lan);
    env->ReleaseStringUTFChars(words, wordsStr);
    env->ReleaseStringUTFChars(mnemonic, mne);
    env->ReleaseStringUTFChars(mnemonicPassword, mnePwd);

    return env->NewStringUTF(seed.c_str());
}

JNICALL jlong native_createIdentity(JNIEnv* env, jobject jobj, jstring localPath) {
    const char* path = env->GetStringUTFChars(localPath, nullptr);

    std::shared_ptr<Identity>* identity = new std::shared_ptr<Identity>();
    int ret = IdentityManager::CreateIdentity(path, identity);
    if (ret != E_WALLET_C_OK) {
        delete identity;
        return 0;
    }

    return (jlong)identity;
}


static const JNINativeMethod gMethods[] = {
        {"native_getMnemonic", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void*)native_getMnemonic},
        {"native_getSeed", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void*)native_getSeed},
        {"native_createIdentity", "(Ljava/lang/String;)J", (void*)native_createIdentity},
};

int registerIdentityManagerMethod(JNIEnv * env) {
    jclass clazz = env->FindClass("org/elastos/sdk/wallet/IdentityManager");
    if (clazz == NULL) return JNI_FALSE;

    int ret = env->RegisterNatives(clazz, gMethods, sizeof(gMethods)/sizeof(JNINativeMethod));
    if (ret < 0) return ret;

    return JNI_TRUE;
};

