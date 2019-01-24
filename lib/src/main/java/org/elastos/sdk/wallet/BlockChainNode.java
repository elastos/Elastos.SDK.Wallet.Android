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


    @Override
    protected synchronized void destroy() {
        if (mObj != 0) {
            native_destroyNode(mObj);
            mObj = 0;
        }
    }


    private static native long native_newBlockNode(String url);
    private static native void native_setUrl(long obj, String url);
    private static native String native_getUrl(long obj);
    private static native void native_setCertificate(long obj, String cert);
    private static native void native_destroyNode(long obj);
}
