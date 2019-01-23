package org.elastos.sdk.wallet;

public final class IdentityManager {
    private IdentityManager(){};


    static Identity importFromFile(String filePath)
    {
        return null;
    }

    static void exportToFile(Identity identity, String filePath)
    {}

    static String getMnemonic(String language, String words)
    {
        return native_getMnemonic(language, words);
    }

    static String getSeed(String mnemonic, String language, String words, String mnemonicPassword)
    {
        return native_getSeed(mnemonic, language, words, mnemonicPassword);
    }

    static Identity createIdentity(String localPath)
    {
        int obj = native_createIdentity(localPath);
        return new Identity(obj);
    }


    private static native String native_getMnemonic(String language, String words);
    private static native String native_getSeed(String mnemonic, String lanaguage, String words, String mnemonicPassword);
    private static native int native_createIdentity(String localPath);

}
