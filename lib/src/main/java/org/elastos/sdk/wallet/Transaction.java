package org.elastos.sdk.wallet;


public final class Transaction extends WalletBase {

    Transaction(String address, long amount, int coinType) {
        mObj = native_createTransaction(address, amount, coinType);
    }

    void setAddress(String address, int coinType) {
        native_setAddress(mObj, address, coinType);
    }

    void setAmount(long amount) {
        native_setAmount(mObj, amount);
    }

    int getCoinType() {
        return native_getCoinTypeTx(mObj);
    }

    String getAddress() {
        return native_getAddress(mObj);
    }

    long getAmount() {
        return native_getAmount(mObj);
    }

    @Override
    protected synchronized void destroy() {
        if (mObj != 0) {
            native_destroyTransaction(mObj);
            mObj = 0;
        }
    }

    private static native long native_createTransaction(String address, long amount, int coinType);
    private static native void native_setAddress(long obj, String address, int coinType);
    private static native void native_setAmount(long obj, long amount);
    private static native int native_getCoinTypeTx(long obj);
    private static native String native_getAddress(long obj);
    private static native long native_getAmount(long obj);
    private static native void native_destroyTransaction(long obj);
}
