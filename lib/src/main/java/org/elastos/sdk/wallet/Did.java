package org.elastos.sdk.wallet;

public final class Did extends WalletBase {


    Did(int obj) {
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
    private static native String native_getId(int obj);
    private static native String native_signInfo(int obj, String seed, String json);
    private static native String native_setInfo(int obj, String seed, String json, int wallet);
    private static native int native_syncInfo(int obj);
    private static native String native_getInfo(int obj, String key);
    private static native void native_destroyDid(int obj);
}
