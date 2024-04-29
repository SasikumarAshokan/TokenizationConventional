//
//
// Copyright © 2021-2022 THALES. All rights reserved.
//

#ifndef D1CError_h
#define D1CError_h

__attribute__((visibility("default")))
extern NSString* const D1CErrorDomain;

/**
 Error types.
 */
typedef NS_ERROR_ENUM(D1CErrorDomain, D1CError) {
    /**
     Unknown error.
     */
    D1CErrorUnknownError = 0x01,
    /**
     Failed storage access.
     */
    D1CErrorStorage = 0x02,
    /**
     Failed network access.
     */
    D1CErrorNetwork = 0x03,
    /**
     The user is not logged in or the login validity has expired.
     */
    D1CErrorNotLoggedIn = 0x04,
    /**
     The user is not authorized.
     */
    D1CErrorNotAuthorized = 0x05,
    /**
     The device environment is potentially unsafe.
     */
    D1CErrorDeviceEnvironmentUnsafe = 0x06,
    /**
     There was no card activation method found for this card. Please retrieve the activation method first.
     */
    D1CErrorNoCardActivationMethod = 0x07,
    /**
     The required UI componenet was not found.
     */
    D1CErrorUIComponentNotFound = 0x08,
    /**
     There was a mismatch with the PIN inputs.
     */
    D1CErrorPinMismatch = 0x09,
    /**
     The provided cardID is not found.
     */
    D1CErrorCardNotFound = 0x0A,
    /**
     The consumer/card is not active.
     */
    D1CErrorNotActive = 0x0B,
    /**
     The consumer/card is not issued by D1.
     @since 3.1.0
     */
    D1CErrorCardNotManagedByD1 = 0x0C,
    /**
     The device passcode is not set/turned-off.
     - Since: 3.0.0
     */
    D1CErrorPasscodeNotSet = 0x0D,
    /**
     Card operation is not allowed on the card.
     @since 3.1.0
     */
    D1CErrorCardOperationNotAllowed = 0x0E,
    /**
     The push token is not found.
     @since 3.1.0
     */
    D1CErrorPushTokenNotFound = 0x0F,
    /**
     The notification type is not supported.
     @since 3.1.0
     */
    D1CErrorNotificationNotSupported = 0x10,
    /**
     Card operation has invalid state reason.
     @since 3.1.0
     */
    D1CErrorCardOperationInvalidReason = 0x11,
    /**
     The Card Settings JSON not well formatted or
     One field is not expected format as defined in this documentation.
     @since 3.1.0
     */
    D1CErrorCardSettingsInvalidFormat = 0x12,
    /**
     One field value is not allowed for the given field.
     @since 3.1.0
     */
    D1CErrorCardSettingsInvalidValue = 0x13,
    /**
     Operation is not allowed on the card.
     For example, updating forbidden card settings field.
     @since 3.1.0
     */
    D1CErrorCardSettingsOperationNotAllowed = 0x14,
    /**
     The provided appGroupID is not valid.
     @since 3.3.0
     */
    D1CErrorInvalidAppGroupId = 0x15,
    /**
     Invalid PIN format.
     @since 3.3.0
     */
    D1CErrorPinInvalid = 0x16,
};

#endif /* D1CError_h */
