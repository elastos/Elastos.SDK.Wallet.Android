package org.elastos.sdk.wallet;

public final class HDWallet extends WalletBase {

    HDWallet(long obj) {
        mObj = obj;
    }

    int getCoinType() {
        return native_getCoinType(mObj);
    }

    String sendTransaction(Transaction[] transactions, String memo, String seed, String chain) {
        long txObjs[] = new long[transactions.length];
        for (int i = 0; i < transactions.length; i++) {
            txObjs[i] = transactions[i].getObject();
        }
        return native_sendTransaction(mObj, txObjs, memo, seed, chain);
    }

    String getAddress(int chain, int index) {
        return native_getAddress(mObj, chain, index);
    }

    String getPublicKey(int chain, int index) {
        return native_getPublickey(mObj, chain, index);
    }

    long getBalance(String address) {
        return native_getBalance(mObj, address);
    }

    long getBalance() {
        return native_getBalanceEx(mObj);
    }

    int syncHistory() {
        return native_syncHistory(mObj);
    }

    int getHistoryCount(String address) {
        return native_getHistoryCount(mObj, address);
    }

    String getHistory(String address, int pageSize, int page, boolean ascending) {
        return native_getHistory(mObj, address, pageSize, page, ascending);
    }

    String[] getUsedAddresses() {
        return native_getUsedAddresses(mObj);
    }

    String[] getUnUsedAddresses(int count) {
        return native_getUnUsedAddressed(mObj, count);
    }

    int recover() {
        return native_recover(mObj);
    }

    @Override
    protected synchronized void destroy() {
        if (mObj != 0) {
            native_destroyHDWallet(mObj);
            mObj = 0;
        }
    }


    private static native int native_getCoinType(long obj);
    private static native String native_sendTransaction(long obj, long[] transactions, String memo,
                                                     String seed, String chain);
    private static native String native_getAddress(long obj, int chain, int index);
    private static native String native_getPublickey(long obj, int chain, int index);
    private static native long native_getBalance(long obj, String address);
    private static native long native_getBalanceEx(long obj);
    private static native int native_syncHistory(long obj);
    private static native int native_getHistoryCount(long obj, String address);
    private static native String native_getHistory(long obj, String address, int pageSize, int page, boolean ascending);
    private static native String[] native_getUsedAddresses(long obj);
    private static native String[] native_getUnUsedAddressed(long obj, int count);
    private static native int native_recover(long obj);
    private static native void native_destroyHDWallet(long obj);
}
