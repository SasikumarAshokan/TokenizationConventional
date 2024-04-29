//
//
// Copyright © 2023 THALES. All rights reserved.
//
    

#ifndef D1CMessagingEnums_h
#define D1CMessagingEnums_h

typedef NS_OPTIONS(NSInteger, D1CNotificationType)
{
    D1CNotificationTypeMessaging = 1 << 0,

    // internal value; not exposed in D1 yet. only used for testing
    D1CNotificationTypeCardState = 1 << 1
};

typedef NS_ENUM(NSInteger, D1CMessageType)
{
    D1CMessageTypeCardStatusUpdate,
    D1CMessageTypeAuthorization
};

typedef NS_ENUM(NSInteger, D1CMessageFormat)
{
    D1CMessageFormatText,
    D1CMessageFormatHtml
};

#endif /* D1CMessagingEnums_h */
