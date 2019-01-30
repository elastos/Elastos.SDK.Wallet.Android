package org.elastos.sdk.wallet;


public final class DidManager extends WalletBase {

    DidManager(long obj) {
        mObj = obj;
    }

    public Did createDid(int index) {
        long obj = native_createDid(mObj, index);
        return new Did(obj);
    }

    public int recover() {
        return native_didRecover(mObj);
    }

    @Override
    protected synchronized void destroy() {
        if (mObj != 0) {
            native_destroyDidManager(mObj);
            mObj = 0;
        }
    }


    private static native long native_createDid(long obj, int index);
    private static native int native_didRecover(long obj);
    private static native void native_destroyDidManager(long obj);
}
