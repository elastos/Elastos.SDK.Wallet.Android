#include <jni.h>
#include "HDWallet.h"
#include "Transaction.h"
#include <vector>
#include <string>

using namespace elastos;

JNICALL jint native_getCoinType(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return 0;

    std::shared_ptr<HDWallet>* wallet = (std::shared_ptr<HDWallet>*)obj;
    return (*wallet)->GetCoinType();
}

JNICALL jstring native_sendTransaction(JNIEnv* env, jobject jobj,
                                       jlong obj, jlongArray transactions, jstring memo,
                                       jstring seed, jstring chain) {
    if (!obj) return env->NewStringUTF("");
    std::shared_ptr<HDWallet>* wallet = (std::shared_ptr<HDWallet>*)obj;

    const char* memoStr = env->GetStringUTFChars(memo, nullptr);
    const char* seedStr = env->GetStringUTFChars(seed, nullptr);
    const char* chainStr = env->GetStringUTFChars(chain, nullptr);

    jsize len = env->GetArrayLength(transactions);
    jlong* txObjs = env->GetLongArrayElements(transactions, 0);
    std::vector<Transaction> txs;
    for (int i = 0; i < len; i++) {
        Transaction* tx = (Transaction*)txObjs[i];
        if (!tx) continue;
        txs.push_back(*tx);
    }
    std::string txid;
    (*wallet)->SendTransaction(txs, memoStr, seedStr, txid, chainStr);
    env->ReleaseStringUTFChars(memo, memoStr);
    env->ReleaseStringUTFChars(seed, seedStr);
    env->ReleaseStringUTFChars(chain, chainStr);
    env->ReleaseLongArrayElements(transactions, txObjs, 0);

    return env->NewStringUTF(txid.c_str());
}

JNICALL jstring native_getAddress(JNIEnv* env, jobject jobj, jlong obj, jint chain, jint index) {
    if (!obj) return env->NewStringUTF("");

    std::shared_ptr<HDWallet>* wallet = (std::shared_ptr<HDWallet>*)obj;
    std::string address = (*wallet)->GetAddress(chain, index);
    return env->NewStringUTF(address.c_str());
}

JNICALL jstring native_getPublickey(JNIEnv* env, jobject jobj, jlong obj, jint chain, jint index) {
    if (!obj) return env->NewStringUTF("");

    std::shared_ptr<HDWallet>* wallet = (std::shared_ptr<HDWallet>*)obj;
    std::string pub = (*wallet)->GetPublicKey(chain, index);
    return env->NewStringUTF(pub.c_str());
}

JNICALL jlong native_getBalance(JNIEnv* env, jobject jobj, jlong obj, jstring address) {
    if (!obj) return 0;

    std::shared_ptr<HDWallet>* wallet = (std::shared_ptr<HDWallet>*)obj;

    const char* addr = env->GetStringUTFChars(address, nullptr);
    long balance = (*wallet)->GetBalance(addr);
    env->ReleaseStringUTFChars(address, addr);

    return balance;
}

JNICALL jlong native_getBalanceEx(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return 0;

    std::shared_ptr<HDWallet>* wallet = (std::shared_ptr<HDWallet>*)obj;
    return (*wallet)->GetBalance();
}

JNICALL jint native_syncHistory(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return 0;

    std::shared_ptr<HDWallet>* wallet = (std::shared_ptr<HDWallet>*)obj;
    return (*wallet)->SyncHistory();
}

JNICALL jint native_getHistoryCount(JNIEnv* env, jobject jobj, jlong obj, jstring address) {
    if (!obj) return 0;

    std::shared_ptr<HDWallet>* wallet = (std::shared_ptr<HDWallet>*)obj;

    const char* addr = env->GetStringUTFChars(address, nullptr);
    int count = (*wallet)->GetHistoryCount(addr);
    env->ReleaseStringUTFChars(address, addr);

    return count;
}

JNICALL jstring native_getHistory(JNIEnv* env, jobject jobj, jlong obj,
                                  jstring address, jint pageSize, jint page, jboolean ascending) {
    if (!obj) return env->NewStringUTF("");
    std::shared_ptr<HDWallet>* wallet = (std::shared_ptr<HDWallet>*)obj;

    const char* addr = env->GetStringUTFChars(address, nullptr);
    std::string histories;
    (*wallet)->GetHistory(addr, pageSize, page, ascending, histories);
    env->ReleaseStringUTFChars(address, addr);

    return env->NewStringUTF(histories.c_str());
}

JNICALL jobjectArray native_getUsedAddresses(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return nullptr;
    std::shared_ptr<HDWallet>* wallet = (std::shared_ptr<HDWallet>*)obj;

    std::vector<std::string> addrs = (*wallet)->GetUsedAddresses();

    jobjectArray array = env->NewObjectArray((jsize)addrs.size(), env->FindClass("java/lang/String"), env->NewStringUTF(""));
    for (int i = 0; i < addrs.size(); i++) {
        env->SetObjectArrayElement(array, i, env->NewStringUTF(addrs[i].c_str()));
    }

    return array;
}

JNICALL jobjectArray native_getUnUsedAddressed(JNIEnv* env, jobject jobj, jlong obj, jint count) {
    if (!obj) return nullptr;
    std::shared_ptr<HDWallet>* wallet = (std::shared_ptr<HDWallet>*)obj;

    std::vector<std::string> addrs = (*wallet)->GetUnUsedAddresses(count);

    jobjectArray array = env->NewObjectArray((jsize)addrs.size(), env->FindClass("java/lang/String"), env->NewStringUTF(""));
    for (int i = 0; i < addrs.size(); i++) {
        env->SetObjectArrayElement(array, i, env->NewStringUTF(addrs[i].c_str()));
    }

    return array;
}

JNICALL jint native_recover(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return 0;

    std::shared_ptr<HDWallet>* wallet = (std::shared_ptr<HDWallet>*)obj;
    return (*wallet)->Recover();
}

JNICALL void native_destroyHDWallet(JNIEnv* env, jobject jobj, jlong obj) {
    if (!obj) return;

    std::shared_ptr<HDWallet>* wallet = (std::shared_ptr<HDWallet>*)obj;
    wallet->reset();
    delete wallet;
}

static const JNINativeMethod gMethods[] = {
        {"native_getCoinType", "(J)I", (void*)native_getCoinType},
        {"native_sendTransaction", "(J[JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void*)native_sendTransaction},
        {"native_getAddress", "(JII)Ljava/lang/String;", (void*)native_getAddress},
        {"native_getPublickey", "(JII)Ljava/lang/String;", (void*)native_getPublickey},
        {"native_getBalance", "(JLjava/lang/String;)J", (void*)native_getBalance},
        {"native_getBalanceEx", "(J)J", (void*)native_getBalanceEx},
        {"native_syncHistory", "(J)I", (void*)native_syncHistory},
        {"native_getHistoryCount", "(JLjava/lang/String;)I", (void*)native_getHistoryCount},
        {"native_getHistory", "(JLjava/lang/String;IIZ)Ljava/lang/String;", (void*)native_getHistory},
        {"native_getUsedAddresses", "(J)[Ljava/lang/String;", (void*)native_getUsedAddresses},
        {"native_getUnUsedAddressed", "(J)[Ljava/lang/String;", (void*)native_getUnUsedAddressed},
        {"native_recover", "(J)I", (void*)native_recover},
        {"native_destroyHDWallet", "(J)V", (void*)native_destroyHDWallet},
};

int registerHDWalletMethod(JNIEnv * env) {
    jclass clazz = env->FindClass("org/elastos/sdk/wallet/HDWallet");
    if (clazz == NULL) return JNI_FALSE;

    int ret = env->RegisterNatives(clazz, gMethods, sizeof(gMethods)/sizeof(JNINativeMethod));
    if (ret < 0) return ret;

    return JNI_TRUE;
};

