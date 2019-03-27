cmake_minimum_required(VERSION 3.4.1)

add_library( Elastos.SDK.Wallet SHARED
             Log.cpp
             JniUtils.cpp
             ElastosSDKWalletJni.cpp
             BlockChainNode_jni.cpp
             Did_jni.cpp
             DidManager_jni.cpp
             HDWallet_jni.cpp
             Identity_jni.cpp
             IdentityManager_jni.cpp
             Transaction_jni.cpp )

file(GLOB Elastos.SDK.Wallet.C-AllLibs "${CFG_ELASTOS_SDK_WALLET_C_DIR}/jni/${ANDROID_ABI}/*")
file(GLOB Elastos.SDK.Wallet.C-Libraries ${Elastos.SDK.Wallet.C-AllLibs} ${Elastos.SDK.Wallet.C-AllLibs}) ## fix library order issue
file(GLOB Elastos.SDK.Wallet.C-HeaderDir "${CFG_ELASTOS_SDK_WALLET_C_DIR}/jni/include")
target_include_directories( Elastos.SDK.Wallet PRIVATE "${Elastos.SDK.Wallet.C-HeaderDir}" )
target_link_libraries( Elastos.SDK.Wallet "${Elastos.SDK.Wallet.C-Libraries}" )

target_link_libraries( Elastos.SDK.Wallet log )
target_link_libraries( Elastos.SDK.Wallet z )
