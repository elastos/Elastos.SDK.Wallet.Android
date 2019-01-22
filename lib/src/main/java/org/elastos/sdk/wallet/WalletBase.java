package org.elastos.sdk.wallet;

import java.io.Closeable;
import java.io.IOException;

class WalletBase implements Closeable {

    int mObj = 0;

    @Override
    public void close() throws IOException {
        destroy();
    }

    @Override
    protected void finalize() {
        destroy();
    }

    protected void destroy() {

    }
}
