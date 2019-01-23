package org.elastos.sdk.wallet;

public final class Identity extends WalletBase {

    Identity(int obj) {
        mObj = obj;
    }

    public HDWallet createSingleAddressWallet(String seed, BlockChainNode node) {
        int obj = native_createSingleAddressWallet(mObj, seed, node.getObject());
        return new HDWallet(obj);
    }

    public HDWallet createWallet(String seed, int coinType, BlockChainNode node) {
        int obj = native_createWallet(mObj, seed, coinType, node.getObject());
        return new HDWallet(obj);
    }


    public DidManager createDidManager(String seed) {
        int obj = native_createDidManager(mObj, seed);
        return new DidManager(obj);
    }

    @Override
    protected synchronized void destroy() {
        if (mObj != 0) {
            native_destroyIdentity(mObj);
            mObj = 0;
        }
    }


    private static native int native_createSingleAddressWallet(int obj, String seed, int node);
    private static native int native_createWallet(int obj, String seed, int coinType, int node);
    private static native int native_createDidManager(int obj, String seed);
    private static native void native_destroyIdentity(int obj);
}
