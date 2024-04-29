//
//
// Copyright © 2021-2022 THALES. All rights reserved.
//


NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, D1CWalletType) {
    D1CWalletTypeApplePay,
    D1CWalletTypeScheme
};

typedef NS_ENUM(NSInteger, D1CAssetContentType) {
    D1CAssetContentTypeIcon,
    D1CAssetContentTypeBackground,
};

typedef NS_ENUM(NSInteger, D1CCardScheme)
{
    D1CCardSchemeVisa,
    D1CCardSchemeMasterCard
};

typedef NS_ENUM(NSInteger, D1CCardState)
{
    D1CCardStateActive,
    D1CCardStateInactive,
    D1CCardStateExpired,
    D1CCardStateDeleted,
    D1CCardStateReplaced
};

typedef NS_ENUM(NSInteger, D1CCardMimeType)
{
    D1CCardMimeTypePDF,
    D1CCardMimeTypePNG,
    D1CCardMimeTypeSVG
};

typedef NS_ENUM(NSInteger, D1CCardAction)
{
    D1CCardActionResume,
    D1CCardActionSuspend
};

typedef NS_ENUM(NSInteger, D1CActivateDigitalCardStatus)
{
    D1CActivateDigitalCardStatusPending,
    D1CActivateDigitalCardStatusSuccessful,
    D1CActivateDigitalCardStatusFailed
};

typedef NS_ENUM(NSInteger, D1CPINEvent)
{
    D1CPINEventFirstEntryFinish,
    D1CPINEventPinMismatch,
    D1CPINEventPinMatch
};

NS_ASSUME_NONNULL_END
