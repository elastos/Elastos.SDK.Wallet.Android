cmake_minimum_required(VERSION 3.4.1)

add_library( Elastos.SDK.Wallet SHARED
             src/main/cpp/Log.cpp
             src/main/cpp/JniUtils.cpp
             src/main/cpp/ElastosSDKWalletJni.cpp
             src/main/cpp/BlockChainNode_jni.cpp
             src/main/cpp/Did_jni.cpp
             src/main/cpp/DidManager_jni.cpp
             src/main/cpp/HDWallet_jni.cpp
             src/main/cpp/Identity_jni.cpp
             src/main/cpp/IdentityManager_jni.cpp
             src/main/cpp/Transaction_jni.cpp )

file(GLOB Elastos.SDK.Wallet.C-AllLibs "${PROJECT_SOURCE_DIR}/build/tmp/Elastos.SDK.Wallet.C/jni/${ANDROID_ABI}/*")
file(GLOB Elastos.SDK.Wallet.C-Libraries ${Elastos.SDK.Wallet.C-AllLibs} ${Elastos.SDK.Wallet.C-AllLibs}) ## fix library order issue
file(GLOB Elastos.SDK.Wallet.C-HeaderDir "${PROJECT_SOURCE_DIR}/build/tmp/Elastos.SDK.Wallet.C/jni/include")
target_include_directories( Elastos.SDK.Wallet PRIVATE "${Elastos.SDK.Wallet.C-HeaderDir}" )
target_link_libraries( Elastos.SDK.Wallet "${Elastos.SDK.Wallet.C-Libraries}" )

target_link_libraries( Elastos.SDK.Wallet log )
target_link_libraries( Elastos.SDK.Wallet z )
