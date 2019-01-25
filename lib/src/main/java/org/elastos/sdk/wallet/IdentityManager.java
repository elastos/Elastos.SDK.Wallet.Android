package org.elastos.sdk.wallet;

public final class IdentityManager {

    static {
        System.loadLibrary("Elastos.SDK.Wallet");
    }

    private IdentityManager(){};


    public static Identity importFromFile(String filePath)
    {
        return null;
    }

    public static void exportToFile(Identity identity, String filePath)
    {}

    public static String getMnemonic(String language, String words)
    {
        return native_getMnemonic(language, words);
    }

    public static String getSeed(String mnemonic, String language, String words, String mnemonicPassword)
    {
        return native_getSeed(mnemonic, language, words, mnemonicPassword);
    }

    public static Identity createIdentity(String localPath)
    {
        long obj = native_createIdentity(localPath);
        return new Identity(obj);
    }


    private static native String native_getMnemonic(String language, String words);
    private static native String native_getSeed(String mnemonic, String language, String words, String mnemonicPassword);
    private static native long native_createIdentity(String localPath);

}
