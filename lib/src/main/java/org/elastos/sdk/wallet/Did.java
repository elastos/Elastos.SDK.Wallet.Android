package org.elastos.sdk.wallet;

public final class Did extends WalletBase {


    Did(long obj) {
        mObj = obj;
    }

    static {
        System.loadLibrary("Elastos.SDK.Wallet");
    }


    public String getId() {
        return native_getId(mObj);
    }

    public String signInfo(String seed, String json) {
        return native_signInfo(mObj, seed, json);
    }

    String setInfo(String seed, String json, HDWallet wallet) {
        return native_setInfo(mObj, seed, json, wallet.getObject());
    }

    int syncInfo() {
        return native_syncInfo(mObj);
    }

    String getInfo(String key) {
        return native_getInfo(mObj, key);
    }

    @Override
    protected synchronized void destroy() {
        if (mObj != 0) {
            native_destroyDid(mObj);
            mObj = 0;
        }
    }


    public static native void test();
    private static native String native_getId(long obj);
    private static native String native_signInfo(long obj, String seed, String json);
    private static native String native_setInfo(long obj, String seed, String json, long wallet);
    private static native int native_syncInfo(long obj);
    private static native String native_getInfo(long obj, String key);
    private static native void native_destroyDid(long obj);
}
