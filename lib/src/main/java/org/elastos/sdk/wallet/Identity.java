package org.elastos.sdk.wallet;

public final class Identity extends WalletBase {

    Identity(long obj) {
        mObj = obj;
    }

    public HDWallet createSingleAddressWallet(String seed, BlockChainNode node) {
        long obj = native_createSingleAddressWallet(mObj, seed, node.getObject());
        return new HDWallet(obj);
    }

    public HDWallet createWallet(String seed, int coinType, BlockChainNode node) {
        long obj = native_createWallet(mObj, seed, coinType, node.getObject());
        return new HDWallet(obj);
    }


    public DidManager createDidManager(String seed) {
        long obj = native_createDidManager(mObj, seed);
        return new DidManager(obj);
    }

    @Override
    protected synchronized void destroy() {
        if (mObj != 0) {
            native_destroyIdentity(mObj);
            mObj = 0;
        }
    }


    private static native long native_createSingleAddressWallet(long obj, String seed, long node);
    private static native long native_createWallet(long obj, String seed, int coinType, long node);
    private static native long native_createDidManager(long obj, String seed);
    private static native void native_destroyIdentity(long obj);
}
