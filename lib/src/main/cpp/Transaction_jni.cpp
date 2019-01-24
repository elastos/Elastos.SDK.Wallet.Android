
#include <jni.h>
#include <string>
#include "Transaction.h"

using namespace elastos;

JNICALL jlong native_createTransaction(JNIEnv* env, jobject jobj, jstring address, jlong amount, jint coinType) {
    const char* addr = env->GetStringUTFChars(address, nullptr);
    Transaction* tx = new Transaction(addr, amount, coinType);
    env->ReleaseStringUTFChars(address, addr);
    return (jlong)tx;
}

JNICALL void native_setAddress(JNIEnv* env, jobject jobj, jlong obj, jstring address, jint coinType) {
    if (!obj) return;

    Transaction* tx = (Transaction*)obj;
    const char* addr = env->GetStringUTFChars(address, nullptr);
    tx->SetAddress(addr, coinType);
    env->ReleaseStringUTFChars(address, addr);
}

JNICALL void native_setAmount(JNIEnv* env, jobject jobj, jlong obj, jlong amount) {
    if (!obj) return;

    Transaction* tx = (Transaction*)obj;
    tx->SetAmount(amount);
}

JNICALL jint native_getCoinTypeTx(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return 0;

    Transaction* tx = (Transaction*)obj;
    return tx->GetCoinType();
}

JNICALL jstring native_getAddress(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return env->NewStringUTF("");

    Transaction* tx = (Transaction*)obj;
    std::string addr = tx->GetAddress();
    return env->NewStringUTF(addr.c_str());
}

JNICALL jlong native_getAmount(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return 0;

    Transaction* tx = (Transaction*)obj;
    return tx->GetAmount();
}

JNICALL void native_destroyTransaction(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return;
    Transaction* tx = (Transaction*)obj;
    delete tx;
}

static const JNINativeMethod gMethods[] = {
        {"native_createTransaction", "(Ljava/lang/String;JI)J", (void*)native_createTransaction},
        {"native_setAddress", "(JLjava/lang/String;I)V", (void*)native_setAddress},
        {"native_setAmount", "(JJ)V", (void*)native_setAmount},
        {"native_getCoinTypeTx", "(J)I", (void*)native_getCoinTypeTx},
        {"native_getAddress", "(J)Ljava/lang/String;", (void*)native_getAddress},
        {"native_getAmount", "(J)J", (void*)native_getAmount},
        {"native_destroyDid", "(J)V", (void*)native_destroyTransaction},
};

int registerTransactionMethod(JNIEnv * env) {
    jclass clazz = env->FindClass("org/elastos/sdk/wallet/Transaction");
    if (clazz == NULL) return JNI_FALSE;

    int ret = env->RegisterNatives(clazz, gMethods, sizeof(gMethods)/sizeof(JNINativeMethod));
    if (ret < 0) return ret;

    return JNI_TRUE;
};
