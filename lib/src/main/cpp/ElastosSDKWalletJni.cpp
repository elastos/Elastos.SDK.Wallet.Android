#include <jni.h>
#include <string>

#include <BlockChainNode.h>
#include <DidManager.h>
#include <Identity.h>
#include <MultiSignWallet.h>
#include <WalletError.h>
#include <Did.h>
#include <HDWallet.h>
#include <IdentityManager.h>
#include <Transaction.h>

#include "JniUtils.hpp"

static const char* JavaClassName_ElastosWallet_Data = "org/elastos/sdk/wallet/ElastosWallet$Data";

static jobject NewData(JNIEnv *jEnv)
{
    jclass jClass_Data = JniUtils::GetJavaClass(jEnv, JavaClassName_ElastosWallet_Data);
    jmethodID jMethod_DataConstructor = jEnv->GetMethodID(jClass_Data, "<init>", "()V");
    jobject jData = jEnv->NewObject(jClass_Data, jMethod_DataConstructor);

    return jData;
}

static void SetDataBuffer(JNIEnv *jEnv, jobject jData, int8_t *buf, int size)
{
    auto jBuf = JniUtils::GetByteArraySafely(jEnv, buf, size);

    jclass jClass_Data = JniUtils::GetJavaClass(jEnv, JavaClassName_ElastosWallet_Data);
    jfieldID jField_DataBuf = jEnv->GetFieldID(jClass_Data, "buf", JniUtils::JavaClassNameByteArray);
    jEnv->SetObjectField(jData, jField_DataBuf, jBuf.get());

    return;
}

static std::shared_ptr<int8_t> GetDataBuffer(JNIEnv *jEnv, jobject data)
{
    jclass jClass_Data = JniUtils::GetJavaClass(jEnv, JavaClassName_ElastosWallet_Data);
    jfieldID jField_DataBuf = jEnv->GetFieldID(jClass_Data, "buf", JniUtils::JavaClassNameByteArray);
    jobject jObject_DataBuf = jEnv->GetObjectField(data, jField_DataBuf);

    auto buf = JniUtils::GetByteArraySafely(jEnv, static_cast<jbyteArray>(jObject_DataBuf));

    return buf;
}

extern "C"
JNIEXPORT void JNICALL
Java_org_elastos_sdk_wallet_Did_test(JNIEnv *jEnv, jclass jType)
{
//    Did did("", 0);
}
