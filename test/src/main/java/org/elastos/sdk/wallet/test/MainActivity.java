package org.elastos.sdk.wallet.test;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import org.elastos.sdk.wallet.IdentityManager;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;

import static org.elastos.sdk.wallet.IdentityManager.getMnemonic;

public class MainActivity extends Activity {
    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    protected void onStart() {
        super.onStart();

        TextView txtMsg = findViewById(R.id.txt_message);

        findViewById(R.id.btn_test_mnemonic).setOnClickListener((view) -> {
            String message = testGenrateMnemonic();
            txtMsg.setText(message);
        });
        findViewById(R.id.btn_test_hdwallet).setOnClickListener((view) -> {
            String message = testHDWalletAddress();
            txtMsg.setText(message);
        });
        findViewById(R.id.btn_test_did).setOnClickListener((view) -> {
            String message = testDid();
            txtMsg.setText(message);
        });
        findViewById(R.id.btn_test_sign).setOnClickListener((view) -> {
            String message = testSignTxData();
            message += testCosignTxData();
            txtMsg.setText(message);
        });
    }

    private String testGenrateMnemonic() {
        StringBuilder buf = new StringBuilder();
        InputStream file = null;
        try {
            file = getAssets().open("mnemonic_chinese.txt");
            BufferedReader in = new BufferedReader(new InputStreamReader(file, "UTF-8"));

            String str;

            while ((str = in.readLine()) != null) {
                buf.append(str);
            }

            in.close();
        } catch (IOException e) {
            e.printStackTrace();
        }


        return IdentityManager.getMnemonic("chinese", buf.toString());
    }

    private String testHDWalletAddress() {
        String message = "";

        message += "================================================\n";
        return message;
    }

    private String testDid() {
        String message = "";

        message += "================================================\n";
        return message;
    }

    private String testSignTxData() {
        String message = "";

        message += "================================================\n";
        return message;
    }

    private String testCosignTxData() {
        String message = "";

        message += "================================================\n";
        return message;
    }
}
