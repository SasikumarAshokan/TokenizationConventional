package com.ahlibank.tokenization;

import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.nfc.NfcAdapter;
import android.nfc.cardemulation.CardEmulation;
import android.os.Build;
import android.util.Base64;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.google.gson.GsonBuilder;
import com.thalesgroup.gemalto.d1.ConfigParams;
import com.thalesgroup.gemalto.d1.D1Exception;
import com.thalesgroup.gemalto.d1.D1Params;
import com.thalesgroup.gemalto.d1.D1Task;
import com.thalesgroup.gemalto.d1.card.AssetContent;
import com.thalesgroup.gemalto.d1.card.CardAction;
import com.thalesgroup.gemalto.d1.card.CardAsset;
import com.thalesgroup.gemalto.d1.card.CardDetails;
import com.thalesgroup.gemalto.d1.card.CardDigitizationState;
import com.thalesgroup.gemalto.d1.card.CardMetadata;
import com.thalesgroup.gemalto.d1.card.OEMPayType;
import com.thalesgroup.gemalto.d1.card.State;
import com.thalesgroup.gemalto.d1.d1pay.AuthenticationParameter;
import com.thalesgroup.gemalto.d1.d1pay.ContactlessTransactionListener;
import com.thalesgroup.gemalto.d1.d1pay.D1HCEService;
import com.thalesgroup.gemalto.d1.d1pay.D1PayConfigParams;
import com.thalesgroup.gemalto.d1.d1pay.D1PayDigitalCard;
import com.thalesgroup.gemalto.d1.d1pay.D1PayWallet;
import com.thalesgroup.gemalto.d1.d1pay.DeviceAuthenticationCallback;
import com.thalesgroup.gemalto.d1.d1pay.DeviceAuthenticationTimeoutCallback;
import com.thalesgroup.gemalto.d1.d1pay.TransactionData;
import com.thalesgroup.gemalto.d1.d1pay.VerificationMethod;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.jetbrains.annotations.NotNull;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * This class echoes a string called from JavaScript.
 */
public class TokenizationConventional extends CordovaPlugin {

    public D1Task mD1Task;
    private D1PayContactlessTransactionListener mD1PayTransactionListener;
    private CallbackContext callback;

    private static final String TAG = "Outsystems==>" + CoreUtils.class.getSimpleName();

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        callback = callbackContext;

        switch (action) {
            case "setApplicationContext":
                setAppContext();
                break;

            case "configure":
                final String serviceUrl = args.getString(0);
                final String issuerId = args.getString(1);
                String sExponent = String.valueOf(args.getString(2));
                final byte[] exponent = sExponent.getBytes();
                String sModulus = String.valueOf(args.getString(3));
                final byte[] modulus = sModulus.getBytes();
                final String digitalCardUrl = args.getString(4);
                final String consumerId = args.getString(5);

                Log.i(TAG, "serviceUrl : " + serviceUrl);
                Log.i(TAG, "issuerId : " + issuerId);
                Log.i(TAG, "exponent : " + sExponent);
                Log.i(TAG, "modulus : " + sModulus);
                Log.i(TAG, "digitalCardUrl : " + digitalCardUrl);
                Log.i(TAG, "consumerId : " + consumerId);

                configure(cordova.getContext(), cordova.getActivity(), serviceUrl, issuerId, exponent, modulus, digitalCardUrl, consumerId);
                break;

            case "login":
                final String token = args.getString(0);
                login(token.getBytes(StandardCharsets.UTF_8));
                break;

            case "checkCardDigitizationState":
                checkCardDigitizationState(args.getString(0), callback, cordova.getContext());
                break;

            case "addDigitalCard":
                addDigitalCard(args.getString(0), callback);
                break;

            case "getCardData":
                getDigitalCardList();
                break;

            case "doManualPayment":
                doManualPayment(args.getString(0));
                break;

            case "setDefultPaymentCard":
                setDefultPaymentCard(args.getString(0));
                break;

            case "unSetDefaultPaymentCard":
                unSetDefaultPaymentCard();
                break;

            case "updateDigitalCard":
                updateDigitalCard(args.getString(0));
                break;

            case "getDeviceName":
                callbackContext.success(getDeviceName());
                break;

            case "checkNFCEnable":
                checkNFCStatus();
                break;

            case "checkDefaultPaymentApp":
                checkDefaultPaymentApp();
                break;

            case "setDefaultPaymentApp":
                setDefaultPaymentApp();
                break;

            default:
                callbackContext.error("undefined action");
                return false;
        }
        return true;
    }

    public void setAppContext() {
        try {
            new D1Task.Builder().setContext(cordova.getActivity().getApplicationContext()).build();
        } catch (Exception e) {
            Log.e(TAG, "setAppContext : " + e.toString());
        }
    }

    private void configure(@NotNull final Context context,
                           @NotNull final Activity activity,
                           @NotNull final String serviceUrl,
                           @NotNull final String issuerId,
                           @NotNull final byte[] exponent,
                           @NotNull final byte[] modulus,
                           @NotNull final String digitalCardUrl,
                           @NotNull final String consumerId) {

        try {
            mD1Task = new D1Task.Builder()
                    .setContext(context)
                    .setD1ServiceURL(serviceUrl)
                    .setIssuerID(issuerId)
                    .setD1ServiceRSAExponent(exponent)
                    .setD1ServiceRSAModulus(modulus)
                    .setDigitalCardURL(digitalCardUrl).build();

            final D1Params coreConfig = ConfigParams.buildConfigCore(consumerId);
            final D1Params cardConfig = ConfigParams.buildConfigCard(activity, OEMPayType.NONE, null);

            // D1Pay config.
            final D1PayConfigParams d1PayConfigParams = D1PayConfigParams.getInstance();
            d1PayConfigParams.setContactlessTransactionListener(mD1PayTransactionListener = new D1PayContactlessTransactionListener(cordova.getActivity().getApplicationContext(), null));
            d1PayConfigParams.setReplenishAuthenticationUIStrings("Replenishment Title",
                    "Replenishment Subtitle",
                    "Replenishment Description",
                    "Cancel");

            mD1Task.configure(new D1Task.ConfigCallback<Void>() {
                @Override
                public void onSuccess(final Void data) {
                    callback.success("D1 SDK Configuration Successfull");
                    Log.i(TAG, "D1 SDK Configuration Successfull");
                }

                @Override
                public void onError(@NonNull List<D1Exception> exceptions) {
                    Log.e(TAG, "mD1Task.configure Exception : " + exceptions.toString());
                    callback.error(createJsonError(exceptions));
                }
            }, coreConfig, cardConfig, d1PayConfigParams);
        } catch (Exception exception) {
            Log.e(TAG, "Configure Fun Error : " + exception.toString());
            callback.error("Configure Fun Error : " + exception.toString());
        }
    }

    private void login(@NotNull final byte[] issuerToken) {
        try {
            mD1Task.login(issuerToken, new D1Task.Callback<Void>() {
                @Override
                public void onSuccess(final Void data) {
                    callback.success("D1 SDK Login Successfull");
                    Log.i(TAG, "D1 SDK Login Successfull");
                }

                @Override
                public void onError(@NonNull final D1Exception exception) {
                    callback.error(createJsonError(Collections.singletonList(exception)));
                    Log.e(TAG, "D1 SDK Login Error : " + exception.toString());
                }
            });
        } catch (Exception e) {
            callback.error("Login : " + e.toString());
        }
    }

    public void checkCardDigitizationState(String cardID, CallbackContext callback, Context context) {
        try {
            D1Task.Callback<CardDigitizationState> digitizationCallback = new D1Task.Callback<CardDigitizationState>() {
                @Override
                public void onSuccess(@NonNull CardDigitizationState state) {
                    // update UI bases on the state value

                    // Hide button "Enable NFC Payment"
                    switch (state) {
                        case NOT_DIGITIZED:
                            // Check Device is Eligible
                            // show button "Enable NFC Payment"
                            callback.success("NOT_DIGITIZED");
                            Log.i(TAG, "Card Digitization State : NOT_DIGITIZED");
                            break;

                        case DIGITIZATION_IN_PROGRESS:
                            // Hide button "Enable NFC Payment"
                            // Show digitization in progress
                            callback.success("DIGITIZATION_IN_PROGRESS");
                            Log.i(TAG, "Card Digitization State : DIGITIZATION_IN_PROGRESS");
                            break;

                        case DIGITIZED:
                            // Tap&Pay settings
                            // check issuer application is the default payment application
                            //defaultPaymentApplication(context, callback);
                            callback.success("DIGITIZED");
                            Log.i(TAG, "Card Digitization State : DIGITIZED");
                            break;
                    }
                }

                @Override
                public void onError(@NonNull D1Exception exception) {
                    // Refer to D1 SDK Integration – Error Management section
                    // Exception: Not Supported: Display message 'Not Supported'
                    callback.error("DigitizationCallback : " + exception.toString());
                    Log.e(TAG, "Card Digitization State On Error : " + exception.toString());
                }
            };

            D1PayWallet d1PayWallet = mD1Task.getD1PayWallet();
            d1PayWallet.getCardDigitizationState(cardID, digitizationCallback);

        } catch (Exception e) {
            callback.error("CheckCardDigitizationState : " + e.toString());
        }
    }

    public void addDigitalCard(String cardID, CallbackContext callback) {
        try {
            Log.i(TAG, "AddDigitalCard CardID : " + cardID);
            D1PayWallet d1PayWallet = mD1Task.getD1PayWallet();

            d1PayWallet.registerD1PayDataChangedListener((cardId, state) -> {
                Log.i(TAG, "registerD1PayDataChangedListener : " + "cardId : " + cardId + " | state : " + state.toString());
                if (state == State.ACTIVE) {
                    // if it is the first digitization process, then:
                    // Tap and Pay settings - Check issuer application is the default payment application
                    // if not redirect end user to Tap and Pay settings
                    callback.success("Card Added Successfully");
                }
            });

            D1Task.Callback<Void> digitalCardCallback = new D1Task.Callback<Void>() {
                @Override
                public void onSuccess(@Nullable Void ignored) {
                    // Data will be updated through Push Notification
                    Log.i(TAG, "Card Added Successfully");
                }

                @Override
                public void onError(@NonNull D1Exception exception) {
                    // Refer to D1 SDK Integration – Error Management section
                    callback.error("AddDigitalCard On Error " + exception.toString());
                    Log.e(TAG, "AddDigitalCard On Error : " + exception.toString());
                }
            };

            d1PayWallet.addDigitalCard(cardID, digitalCardCallback);

        } catch (Exception e) {
            callback.error("Add Digital Card Excep: " + e.toString());
        }
    }

    @NonNull
    public D1Task getD1Task() {
        if (mD1Task == null) {
            throw new IllegalStateException("Need to configure D1 SDK first.");
        }

        return mD1Task;
    }

    private void checkNFCStatus() {
        try {
            PackageManager pm = cordova.getContext().getPackageManager();
            if (pm.hasSystemFeature(PackageManager.FEATURE_NFC_HOST_CARD_EMULATION)) {
                callback.success("E"); //Eligible
                Log.i(TAG, "Device Eligible for NFC Payment");
            } else {
                callback.success("N"); //Not Eligible
                Log.i(TAG, "Device Not Eligible for NFC Payment");
            }
        } catch (Exception e) {
            callback.error("CheckNFCStatus : " + e.toString());
        }
    }

    private void checkDefaultPaymentApp() {
        try {
            CardEmulation cardEmulation = CardEmulation.getInstance(NfcAdapter.getDefaultAdapter(cordova.getContext()));

            // Construct the componentName with the default D1 Pay HCE service class
            ComponentName componentName = new ComponentName(cordova.getContext(), D1HCEService.class.getCanonicalName());

            if (cardEmulation.isDefaultServiceForCategory(componentName, CardEmulation.CATEGORY_PAYMENT)) {
                // Application is default NFC payment app
                callback.success("Default App");
                Log.i(TAG, "Default Payment App");
            } else {
                // Application is not default NFC payment app
                callback.success("Not Default App");
                Log.i(TAG, "Not Default Payment App");
            }
        } catch (Exception e) {
            callback.error("checkDefaultPaymentApp : " + e.toString());
        }
    }

    private void setDefaultPaymentApp() {
        try {
            // Construct the componentName with the default D1 Pay HCE service class
            ComponentName componentName = new ComponentName(cordova.getContext(), D1HCEService.class.getCanonicalName());

            Intent activate = new Intent();
            activate.setFlags(FLAG_ACTIVITY_NEW_TASK);
            activate.setAction(CardEmulation.ACTION_CHANGE_DEFAULT);
            activate.putExtra(CardEmulation.EXTRA_SERVICE_COMPONENT, componentName);
            activate.putExtra(CardEmulation.EXTRA_CATEGORY, CardEmulation.CATEGORY_PAYMENT);
            cordova.getContext().startActivity(activate);
        } catch (Exception e) {
            callback.error("setDefaultPaymentApp : " + e.toString());
        }
    }

    private String getDeviceName() {
        return Build.MANUFACTURER;
    }

    private String createJsonError(final List<D1Exception> exceptions) {
        try {
            final List<Map<String, Object>> json = new ArrayList<>();
            for (final D1Exception exception : exceptions) {
                final Map<String, Object> jsonMap = new HashMap<>();
                jsonMap.put("message", exception.getLocalizedMessage());
                jsonMap.put("code", exception.getErrorCode().getCode());
                json.add(jsonMap);
            }

            if (json.size() > 1) {
                return new GsonBuilder().setPrettyPrinting().create().toJson(json);
            } else if (json.size() == 1) {
                return new GsonBuilder().setPrettyPrinting().create().toJson(json.get(0));
            }

            return new GsonBuilder().setPrettyPrinting().create().toJson(json);
        } catch (Exception e) {
            callback.error("CreateJsonError : " + e.toString());
        }
        return null;
    }

    private void getCardDetails(String cardID) {
        try {
            D1Task.Callback<CardDetails> cardDetailsCallback = new D1Task.Callback<CardDetails>() {
                @Override
                public void onSuccess(CardDetails cardDetails) {
                    // handle cardDetails object from server, convert byte array type to string
                    String cardHolderName = null;
                    String pan = new String(cardDetails.getPan(), StandardCharsets.UTF_8);
                    String expiryDate = new String(cardDetails.getExpiryDate(), StandardCharsets.UTF_8);
                    String cvv = new String(cardDetails.getCvv(), StandardCharsets.UTF_8);
                    if (cardDetails.getCardHolderName() != null) {
                        cardHolderName = new String(cardDetails.getCardHolderName(), StandardCharsets.UTF_8);
                    }
                    Log.i("getCardDetails", "cardHolderName = " + cardHolderName + " | " + "pan = " + pan + " | " + "expiryDate = " + expiryDate + " | " + "cvv = " + cvv);
                    // wipe byte array variables of cardDetails object
                    cardDetails.wipe();
                }

                @Override
                public void onError(D1Exception exception) {
                    // Refer to D1 SDK Integration – Error Management section
                    Log.e(TAG, "getCardDetails onError : " + exception.toString());
                }
            };
            mD1Task.getCardDetails(cardID, cardDetailsCallback);
        } catch (Exception e) {
            Log.e(TAG, "getCardDetails Exception : " + e.toString());
        }
    }

    private void getDigitalCardList() {
        try {
            JSONArray cardDetailsArray = new JSONArray();
            mD1Task.getD1PayWallet().getDigitalCardList(new D1Task.Callback<Map<String, D1PayDigitalCard>>() {
                @Override
                public void onSuccess(Map<String, D1PayDigitalCard> digitalCards) {
                    for (Map.Entry<String, D1PayDigitalCard> entry : digitalCards.entrySet()) {
                        try {
                            String d1CardID = entry.getKey();
                            D1PayDigitalCard digitalCard = entry.getValue();

                            JSONObject cardObj = new JSONObject();
                            cardObj.put("CardID", d1CardID);
                            cardObj.put("Last4Pan",digitalCard.getLast4());
                            cardObj.put("ExpiryDate",digitalCard.getExpiryDate());
                            cardObj.put("IsDefaultCard",digitalCard.isDefaultCard());
                            cardObj.put("NumberOfPaymentsLeft",digitalCard.getNumberOfPaymentsLeft());
                            cardObj.put("Scheme",digitalCard.getScheme());
                            cardObj.put("State",digitalCard.getState());
                            cardObj.put("TncURL",digitalCard.getTncURL());
                            cardObj.put("IsAuthRequiredBeforeReplenishment",digitalCard.isAuthenticationRequiredBeforeReplenishment());
                            cardObj.put("IsODAReplenishmentNeeded",digitalCard.isODAReplenishmentNeeded());
                            cardObj.put("IsReplenishmentNeeded",digitalCard.isReplenishmentNeeded());
                            cardObj.put("CardArt",getCardMetaData(d1CardID));

                            cardDetailsArray.put(cardObj);

                        } catch (JSONException e) {
                            throw new RuntimeException(e);
                        }
                    }
                    Log.i(TAG, "Card Details : " + cardDetailsArray.toString());
                    callback.success(cardDetailsArray.toString());
                }

                @Override
                public void onError(@NonNull D1Exception e) {
                    Log.e(TAG, "getDigitalCardList onError : " + e.toString());
                }
            });


        } catch (Exception e) {
            Log.e(TAG, "getDigitalCardList Exception : " + e.toString());
        }
    }

    private String getCardMetaData(String cardID) {
        final String[] cardImageURI = {null};
        try {
            D1Task.Callback<CardMetadata> cardCallback = new D1Task.Callback<CardMetadata>() {
                @Override
                public void onSuccess(CardMetadata cardMetadata) {
                    // Last 4 digits of PAN
                    String last4Pan = cardMetadata.getLast4Pan();
                    String expiryDate = cardMetadata.getExpiryDate();
                    // CardAsset is used to display Card Artwork
                    cardMetadata.getAssetList(new D1Task.Callback<List<CardAsset>>() {
                        @Override
                        public void onSuccess(List<CardAsset> cardAssets) {
                            // Proceeds with the application logic
                            for (final CardAsset cardAsset : cardAssets) {
                                final CardAsset.AssetType assetType = cardAsset.getType();

                                for (final AssetContent assetContent : cardAsset.getContents()) {
                                    if (assetContent.getMimeType() == AssetContent.MimeType.PNG) {

                                        final byte[] data = Base64.decode(assetContent.getEncodedData(), Base64.DEFAULT);
                                        cardImageURI[0] = CoreUtils.getInstance().writeToFile(cordova.getActivity().getApplicationContext(), cardID, data);

                                    } else if (assetContent.getMimeType() == AssetContent.MimeType.SVG) {
                                        Log.i(TAG, "extractAndSaveImageResources MimeType = SVG");

                                    } else if (assetContent.getMimeType() == AssetContent.MimeType.PDF) {
                                        Log.i(TAG, "extractAndSaveImageResources MimeType = PDF");
                                    }
                                }
                            }
                        }

                        @Override
                        public void onError(@NonNull D1Exception e) {
                            // Handles the error. For example, log it, display it, and so on.
                            Log.e(TAG, "getAssetList On Error : " + e.toString());
                        }
                    });
                }

                @Override
                public void onError(D1Exception exception) {
                    // Refer to D1 SDK Integration – Error Management section.
                    Log.e(TAG, "getCardMetaData onError : " + exception.toString());
                }
            };

            mD1Task.getCardMetadata(cardID, cardCallback);
        } catch (Exception e) {
            Log.e(TAG, "getCardData Exception : " + e.toString());
        }
        return cardImageURI[0];
    }

    private void setDefultPaymentCard(String d1CardID) {
        try {
            D1PayWallet d1PayWallet = mD1Task.getD1PayWallet();
            d1PayWallet.setDefaultPaymentDigitalCard(
                    d1CardID,
                    new D1Task.Callback<Void>() {
                        @Override
                        public void onSuccess(Void ignored) {
                            callback.success("success");
                            Log.i(TAG, "setDefultPaymentCard : success");
                        }

                        @Override
                        public void onError(@NonNull D1Exception exception) {
                            // Refer to D1 SDK Integration – Error Management section
                            // Common error: invalid d1CardID
                            callback.error(exception.toString());
                            Log.e(TAG, "setDefultPaymentCard onError : " + exception.toString());
                        }
                    });
        } catch (Exception e) {
            Log.e(TAG, "setDefultPaymentCard Exception : " + e.toString());
        }
    }

    private void unSetDefaultPaymentCard(){
        try{
            D1PayWallet d1PayWallet = mD1Task.getD1PayWallet();
            d1PayWallet.unsetDefaultPaymentDigitalCard(
                    new D1Task.Callback<Void>() {
                        @Override
                        public void onSuccess(Void ignored) {
                            // the default card is unset
                            callback.success("success");
                            Log.i(TAG, "unSetDefaultPaymentCard : success");
                        }

                        @Override
                        public void onError(@NonNull D1Exception exception) {
                            // Refer to D1 SDK Integration – Error Management section
                            // Common error: there is no default card.
                            callback.error(exception.toString());
                            Log.e(TAG, "unSetDefaultPaymentCard onError : " + exception.toString());
                        }
                    });
        }catch (Exception e){
            Log.e(TAG, "unSetDefaultPaymentCard Exception : " + e.toString());
        }
    }

    private void updateDigitalCard(String d1CardID){
        try{
            mD1Task.getD1PayWallet().registerD1PayDataChangedListener((cardId, state) -> {
                // The actual update to wallet is received here
            });

            D1PayDigitalCard digitalCard = getDigitalCard(d1CardID); // retrieved from getDigitalCard or getDigitalCardList
            mD1Task.getD1PayWallet().updateDigitalCard(
                    d1CardID,
                    digitalCard,
                    CardAction.SUSPEND,
                    new D1Task.Callback<Boolean>() {
                        @Override
                        public void onSuccess(@NonNull Boolean result) {
                            callback.success("success");
                            Log.i(TAG, "updateDigitalCard : success");
                        }

                        @Override
                        public void onError(@NonNull D1Exception exception) {
                            // Refer to D1 SDK Integration – Error Management section
                            callback.success(exception.toString());
                            Log.e(TAG, "updateDigitalCard onError : " + exception.toString());
                        }
                    }
            );
        }catch (Exception e){
            Log.e(TAG, "unSetDefaultPaymentCard Exception : " + e.toString());
        }
    }

   private D1PayDigitalCard getDigitalCard(String d1CardID){
       final D1PayDigitalCard[] d1PayDigitalCard = {null};
        try{
            D1PayWallet d1PayWallet = mD1Task.getD1PayWallet();
            d1PayWallet.getDigitalCard(d1CardID,
                    new D1Task.Callback<D1PayDigitalCard>() {
                        @Override
                        public void onSuccess(@NonNull D1PayDigitalCard digitalCard) {
                            d1PayDigitalCard[0] = digitalCard;
                        }

                        @Override
                        public void onError(@NonNull D1Exception exception) {
                            // Refer to D1 SDK Integration – Error Management section
                            Log.e(TAG, "getDigitalCard onError : " + exception.toString());
                        }
                    }
            );
        }catch (Exception e){
            Log.e(TAG, "getDigitalCard Exception : " + e.toString());
        }
        return d1PayDigitalCard[0];
   }

    private void doManualPayment(String cardID) {
        try {
            // D1Pay configuration : register contactless transaction callback
            Log.i(TAG, "doManualPayment Card ID : " + cardID);

            D1PayConfigParams configParams = D1PayConfigParams.getInstance();
            configParams.setContactlessTransactionListener(mD1PayTransactionListener = new D1PayContactlessTransactionListener(cordova.getActivity().getApplicationContext(), cardID));

            configParams.setManualModeContactlessTransactionListener(mD1PayTransactionListener = new D1PayContactlessTransactionListener(cordova.getActivity().getApplicationContext(), cardID));

            D1PayWallet d1PayWallet = mD1Task.getD1PayWallet();
            d1PayWallet.startManualModePayment(cardID);
        } catch (Exception e) {
            Log.e(TAG, "doManualPayment Exception : " + e.toString());
        }
    }

    public class D1PayContactlessTransactionListener extends ContactlessTransactionListener {
        protected Context mContext;
        private double mAmount;
        private String mCurrency;
        private final String mCardId;

        /**
         * Creates a new instance of {@code D1PayContactlessTransactionListener}.
         *
         * @param context Context.
         * @param cardId  CardId
         */
        public D1PayContactlessTransactionListener(@NonNull final Context context, final String cardId) {
            super();
            Log.i(TAG, "D1PayContactlessTransactionListener Card ID : " + cardId);
            mContext = context;
            mCardId = cardId;

            resetState();
        }

        @Override
        public void onTransactionStarted() {
            // Display transaction is ongoing
            Log.i(TAG, "onTransactionStarted");
            updateState(PaymentState.STATE_ON_TRANSACTION_STARTED, new PaymentData(mAmount, mCurrency, mCardId));
        }

        @Override
        public void onAuthenticationRequired(@NonNull final VerificationMethod method) {
            /* Only applicable for 2-TAP experience
             * Display transaction details and tell consumer to authenticate
             */
            Log.i(TAG, "onAuthenticationRequired");

            // All current state values are no longer relevant.
            resetState();

            updateAmountAndCurrency();

            // Update state and notify everyone.
            updateState(PaymentState.STATE_ON_AUTHENTICATION_REQUIRED, new PaymentData(mAmount, mCurrency, mCardId));
        }

        @Override
        public void onReadyToTap() {
            /* Only applicable for 2-TAP experience
             * Inform customer application is ready for 2nd TAP.
             * Display transaction details and display the remaining time for the 2nd TAP
             */
            Log.i(TAG, "onReadyToTap");

            // Register the timeout callback to update the user on remaining time for the 2nd tap.
            this.registerDeviceAuthTimeoutCallback(new DeviceAuthenticationTimeoutCallback() {
                @Override
                public void onTimer(final int remain) {
                    // The mobile application should update the countdown screen with current "remaining" time.
                }

                @Override
                public void onTimeout() {
                    // The mobile application should inform end user of the timeout error.
                    updateAmountAndCurrency();
                    deactivate();
                    updateState(PaymentState.STATE_ON_ERROR, new PaymentErrorData(null, "Timer exceeded", mAmount, mCurrency, mCardId));
                    //updateState(PaymentState.STATE_ON_ERROR, new PaymentErrorData(null, mContext.getString(com.thalesgroup.d1.core.R.string.transaction_timeout), mAmount, mCurrency, mCardId));
                }
            });

            updateState(PaymentState.STATE_ON_READY_TO_TAP, new PaymentData(mAmount, mCurrency, mCardId));
        }

        @Override
        public void onTransactionCompleted() {
            /* The transaction has been completed successfully on the mobile app.
             * Display transaction status success and details
             */
            Log.i(TAG, "onTransactionCompleted");

            CoreUtils.getInstance().showToastMsg(cordova.getActivity(), "Transaction Completed");
            callback.success("Transaction Completed");

            updateAmountAndCurrency();
            updateState(PaymentState.STATE_ON_TRANSACTION_COMPLETED, new PaymentData(mAmount, mCurrency, mCardId));
        }

        @Override
        public void onError(@NonNull final D1Exception error) {
            /* The transaction failed due to an error.
             * Mobile application should get detailed information from the "error" param and inform the end user.
             */
            Log.i(TAG, "onError : " + error.toString());
            // All current state values are no longer relevant.
            resetState();

            updateState(PaymentState.STATE_ON_ERROR,
                    new PaymentErrorData(error.getErrorCode(), error.getLocalizedMessage(), mAmount, mCurrency, mCardId));
        }

        /**
         * Updates the amount and currency and wipes the transaction data.
         */
        private void updateAmountAndCurrency() {
            Log.i(TAG, "updateAmountAndCurrency");
            final TransactionData transactionData = getTransactionData();
            if (transactionData == null) {
                mAmount = -1.0;
                mCurrency = null;
            } else {
                mAmount = getTransactionData().getAmount();
                mCurrency = "OMR";
            }

            if (transactionData != null) {
                transactionData.wipe();
            }
        }

        /**
         * Resets the amount, currency and payment state.
         */
        private void resetState() {
            Log.i(TAG, "resetState");
            mAmount = 0.0;
            mCurrency = null;
        }

        /**
         * Updates the payment state and payment data.
         *
         * @param state Payment state.
         * @param data  Payment data.
         */
        protected void updateState(final PaymentState state, final PaymentData data) {
            // Store last state so it can be read onResume when app was not in foreground.
            Log.i(TAG, "updateState : " + state);
            // Notify rest of the application in UI thread.
            CoreUtils.getInstance().runInMainThread(() -> {
                final Intent intent = new Intent(mContext, cordova.getContext().getClass());
                intent.setFlags(FLAG_ACTIVITY_NEW_TASK);
                intent.putExtra("STATE_EXTRA_KEY", state);
                intent.putExtra("PAYMENT_DATA_EXTRA_KEY", data);
                mContext.startActivity(intent);
            });
            if (state == PaymentState.STATE_ON_AUTHENTICATION_REQUIRED) {
                doAuthenticate();
            }
        }

        private final DeviceAuthenticationCallback deviceAuthenticationCallback = new DeviceAuthenticationCallback() {
            @Override
            public void onSuccess() {
                CoreUtils.getInstance().showToastMsg(cordova.getActivity(), "Authentication Success");
            }

            @Override
            public void onFailed() {
                CoreUtils.getInstance().showToastMsg(cordova.getActivity(), "Authentication Failed");
                callback.success("Authentication Failed");
            }

            @Override
            public void onError(int i) {
                CoreUtils.getInstance().showToastMsg(cordova.getActivity(), "onError : " + i);
            }

            @Override
            public void onHelp(int i, @NonNull CharSequence charSequence) {
                CoreUtils.getInstance().showToastMsg(cordova.getActivity(), "onHelp : " + charSequence.toString());
            }
        };


        private void doAuthenticate() {
            try {
                Log.i(TAG, "doAuthenticate Called");
                final AuthenticationParameter authenticationParameter = new AuthenticationParameter(cordova.getActivity(),
                        "Authentication Required",
                        "Please authenticate yourself for payment",
                        "See amount on POS",
                        "Cancel",
                        deviceAuthenticationCallback);

                mD1PayTransactionListener.startAuthenticate(authenticationParameter);
            } catch (Exception e) {
                Log.e(TAG, "doAuthenticate : " + e.toString());
            }
        }
    }
}



