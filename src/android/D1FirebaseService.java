package com.ahlibank.tokenization;

import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.google.firebase.messaging.FirebaseMessagingService;
import com.google.firebase.messaging.RemoteMessage;
import com.thalesgroup.gemalto.d1.D1Exception;
import com.thalesgroup.gemalto.d1.D1Task;
import com.thalesgroup.gemalto.d1.PushResponseKey;

import java.util.Map;

public class D1FirebaseService  extends FirebaseMessagingService {
    private D1Task d1Task = null;
    private static final String TAG = "Outsystems==>"+CoreUtils.class.getSimpleName();
    @Override
    public void onNewToken(@NonNull String token) {
        Log.i(TAG,"D1FirebaseService Push Token : "+token);
        if (d1Task == null) {
            d1Task = new D1Task.Builder()
                    .setContext(getApplicationContext())
                    .build();
        }

        // D1 SDK does not require initialization in order to call `D1Task.updatePushToken()`. It simply requires Android Context.
        d1Task.updatePushToken(token, new D1Task.Callback<Void>() {
            @Override
            public void onSuccess(@Nullable Void ignored) {
                // Proceed with subsequent flows.
                Log.i(TAG,"D1FirebaseService UpdatePushToken Success: "+token);
            }

            @Override
            public void onError(@NonNull D1Exception exception) {
                // Refer to D1 SDK Integration – Error Management section.
                Log.e(TAG,"D1FirebaseService UpdatePushToken On Error: "+exception.toString());
            }
        });

        // Other application logic.
    }

    @Override
    public void onMessageReceived(@NonNull RemoteMessage remoteMessage) {

        Log.i(TAG,"onMessageReceived : "+remoteMessage.getData());

        if (d1Task == null) {
            d1Task = new D1Task.Builder()
                    .setContext(getApplicationContext())
                    .build();
        }

        d1Task.processNotification(remoteMessage.getData(), new D1Task.Callback<Map<PushResponseKey, String>>() {
            @Override
            public void onSuccess(Map<PushResponseKey, String> pushResponseKeyStringMap) {

            }

            @Override
            public void onError(@NonNull D1Exception e) {

            }
        });

        // Other application logic ...
    }

}