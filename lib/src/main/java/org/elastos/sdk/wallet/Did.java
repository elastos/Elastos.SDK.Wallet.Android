package org.elastos.sdk.wallet;

public final class Did extends WalletBase {


    Did(long obj) {
        mObj = obj;
    }


    public String getId() {
        return native_getId(mObj);
    }

    public String signInfo(String seed, String json, boolean encypt) {
        return native_signInfo(mObj, seed, json, encypt);
    }

    public String setInfo(String seed, String json, HDWallet wallet, boolean encypt) {
        return native_setInfo(mObj, seed, json, wallet.getObject(), encypt);
    }

    public int syncInfo() {
        return native_syncInfo(mObj);
    }

    public String getInfo(String key, boolean encypt, String seed) {
        return native_getInfo(mObj, key, encypt, seed);
    }

    public void setNode(BlockChainNode node) {
        native_setNode(mObj, node.getObject());
    }

    @Override
    protected synchronized void destroy() {
        if (mObj != 0) {
            native_destroyDid(mObj);
            mObj = 0;
        }
    }

    private static native String native_getId(long obj);
    private static native String native_signInfo(long obj, String seed, String json, boolean encypt);
    private static native String native_setInfo(long obj, String seed, String json, long wallet, boolean encypt);
    private static native int native_syncInfo(long obj);
    private static native String native_getInfo(long obj, String key, boolean encypt, String seed);
    private static native void native_setNode(long obj, long node);
    private static native void native_destroyDid(long obj);
}
