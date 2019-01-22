package org.elastos.sdk.wallet;

public final class HDWallet extends WalletBase {

    HDWallet(int obj) {
        mObj = obj;
    }

    int getCoinType() {
        return native_getCoinType(mObj);
    }

    String sendTransaction(Transaction[] transactions, String memo, String seed, String chain) {
        int txObjs[] = new int[](transactions.length);
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
        return native_getBalance(mObj);
    }

    int syncHistory() {
        return native_syncHistory(mObj);
    }

    int getHistoryCount(String address) {
        return native_getHistoryCount(mObj, address);
    }

    int GetHistory(const std::string& address, int pageSize, int page, bool ascending, std::string& histories);

    std::vector<std::string> GetUsedAddresses();

    std::vector<std::string> GetUnUsedAddresses(unsigned int count);

    int Recover();

    int getObject() {
        return mObj;
    }

    @Override
    protected synchronized void destroy() {
        if (mObj != 0) {
            native_destroyHDWallet(mObj);
            mObj = 0;
        }
    }


    private static native int native_getCoinType(int obj);
    private static native String native_sendTransaction(int obj, int[] transactions, String memo,
                                                     String seed, String chain);
    private static native String native_getAddress(int obj, int chain, int index);
    private static native String native_getPublickey(int obj, int chain, int index);
    private static native long native_getBalance(int obj, String address);
    private static native long native_getBalance(int obj);
    private static native int native_syncHistory(int obj);
    private static native int native_getHistoryCount(int obj, String address);
    private static native String native_getHistory(int obj);
    private static native String[] native_getUsedAddresses(int obj);
    private static native String[] native_getUnUsedAddressed(int obj, int count);
    private static native int native_recover(int obj);
    private static native void native_destroyHDWallet(int obj);
}
