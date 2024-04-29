//
//
// Copyright © 2023 THALES. All rights reserved.
//
    

#import <Foundation/Foundation.h>
#import <D1Core/D1CMessagingEnums.h>

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CMessage : NSObject

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithMessageId:(NSString* _Nullable)messageId
                           format:(D1CMessageFormat)format
                            title:(NSString* _Nullable)title
                          message:(NSString* _Nullable)message
                             type:(D1CMessageType)type
                         metadata:(NSString* _Nullable)metadata
                           action:(NSString* _Nullable)action
                           isRead:(BOOL)isRead
                        timestamp:(NSString* _Nullable)timestamp;

+ (instancetype _Nullable)retrieveMessageWithId:(NSString*)messageId;

+ (void)cacheMessage:(D1CMessage*)message;

+ (void)clearAll;

// D1 (swift) will use id, as id is keyword in D1Core (objc)
@property NSString* _Nullable messageId;
@property D1CMessageFormat format;
@property NSString* _Nullable title;
@property NSString* _Nullable message;
@property D1CMessageType type;
@property NSString* _Nullable metadata;
@property NSString* _Nullable action;
@property BOOL isRead;
@property NSString* _Nullable timestamp;


@end

NS_ASSUME_NONNULL_END
