package org.elastos.sdk.wallet;


public final class BlockChainNode extends WalletBase {

    public BlockChainNode(String url) {
       mObj = native_newBlockNode(url);
    }

    public void setUrl(String url) {
        native_setUrl(mObj, url);
    }

    public String getUrl() {
        return native_getUrl(mObj);
    }

    public void setCertificate(String cert) {
        native_setCertificate(mObj, cert);
    }

    int getObject() {
        return mObj;
    }

    @Override
    protected synchronized void destroy() {
        if (mObj != 0) {
            native_destroyNode(mObj);
            mObj = 0;
        }
    }


    private static native int native_newBlockNode(String url);
    private static native void native_setUrl(int obj, String url);
    private static native String native_getUrl(int obj);
    private static native void native_setCertificate(int obj, String cert);
    private static native void native_destroyNode(int obj);
}
