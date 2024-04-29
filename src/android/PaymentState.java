/*
 * Copyright © 2022 THALES. All rights reserved.
 */

package com.ahlibank.tokenization;

/**
 * Payment states.
 */
public enum PaymentState {
    /**
     * Undetermined payment state.
     */
    STATE_NONE,

    /**
     * Transaction has been started.
     */
    STATE_ON_TRANSACTION_STARTED,

    /**
     * Authentication is required.
     */
    STATE_ON_AUTHENTICATION_REQUIRED,

    /**
     * Ready to tap.
     */
    STATE_ON_READY_TO_TAP,

    /**
     * Transaction has been completed.
     */
    STATE_ON_TRANSACTION_COMPLETED,

    /**
     * Payment has encountered an error.
     */
    STATE_ON_ERROR
}
