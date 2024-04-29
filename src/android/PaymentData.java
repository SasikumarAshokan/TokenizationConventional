/*
 * Copyright © 2022 THALES. All rights reserved.
 */

package com.ahlibank.tokenization;

import java.io.Serializable;

/**
 * Payment data.
 */
public class PaymentData implements Serializable {

    private static final long serialVersionUID = -8846799612852355120L;
    private final double mAmount;
    private final String mCurrency;
    private final String mCardId;

    /**
     * Creates a new instance of {@code PaymentData}.
     *
     * @param amount   Amount.
     * @param currency Currency.
     * @param cardId   Card Id
     */
    public PaymentData(final double amount, final String currency, final String cardId) {
        mAmount = amount;
        mCurrency = currency;
        mCardId = cardId;
    }

    /**
     * Retrieves the amount.
     *
     * @return Amount.
     */
    public double getAmount() {
        return mAmount;
    }

    /**
     * Retrieves the currency.
     *
     * @return Currency.
     */
    public String getCurrency() {
        return mCurrency;
    }

    /**
     * Retrieves the card Id.
     *
     * @return Card Id.
     */
    public String getCardId() {
        return mCardId;
    }
}
