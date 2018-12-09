package org.elastos.sdk.wallet;

public final class Did {
    private Did() {}

    static {
        System.loadLibrary("Elastos.SDK.Wallet");
    }

    public static class Data {
        public byte[] buf;
    }

    public static native void test();
}
