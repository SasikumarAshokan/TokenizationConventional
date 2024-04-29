/*
 * Copyright © 2022 THALES. All rights reserved.
 */

package com.ahlibank.tokenization;

import com.thalesgroup.gemalto.d1.D1Exception;

/**
 * Payment error data.
 */
public class PaymentErrorData extends PaymentData {
    final D1Exception.ErrorCode mCode;
    final String mMessage;

    /**
     * Creates a new instance of {@code PaymentErrorData}.
     *
     * @param code     Error code.
     * @param message  Error message.
     * @param amount   Amount.
     * @param currency Currency.
     * @param cardId   Card Id as String.
     */
    public PaymentErrorData(final D1Exception.ErrorCode code, final String message, final double amount, final String currency, final String cardId) {
        super(amount, currency, cardId);

        mCode = code;
        mMessage = message;
    }

    /**
     * Retrieves the error code.
     *
     * @return Error code.
     */
    public D1Exception.ErrorCode getCode() {
        return mCode;
    }

    /**
     * Retrieves the error message.
     *
     * @return Error message.
     */
    public String getMessage() {
        return mMessage;
    }
}
