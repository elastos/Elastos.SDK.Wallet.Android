package org.elastos.sdk.wallet;


public final class DidManager extends WalletBase {

    DidManager(long obj) {
        mObj = obj;
    }

    Did createDid(int index) {
        int obj = native_createDid(mObj, index);
        return new Did(mObj);
    }

    @Override
    protected synchronized void destroy() {
        if (mObj != 0) {
            native_destroyDidManager(mObj);
            mObj = 0;
        }
    }


    private static native int native_createDid(long obj, int index);
    private static native void native_destroyDidManager(long obj);
}
