//
//
// Copyright © 2023 THALES. All rights reserved.
//
    

#import <Foundation/Foundation.h>
#import <D1Core/D1CMessagingEnums.h>

@class D1CA2Client;
@class D1CMessage;

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CMessagingClient : NSObject

@property NSString* _Nullable consumerId;
@property __weak D1CA2Client* _Nullable a2Client;
@property (readonly) NSString* _Nullable pushToken;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype _Nullable)initWithBaseUrl:(NSString*)baseUrl
                                 issuerId:(NSString*)issuerId
                             appProfileId:(NSString*)appProfileId
                                    error:(NSError **)error;

- (void)updatePushToken:(NSString*)pushToken
             completion:(void(^)(NSError* _Nullable error))completionBlock;

- (void)tryUpdatePushTokenAfterLoginWithCompletion:(void(^)(NSError* _Nullable error))completionBlock;

- (void)registerNotificationWithType:(D1CNotificationType)type
                          completion:(void(^)(NSError* _Nullable error))completionBlock;

- (void)unregisterNotificationWithType:(D1CNotificationType)type 
                            completion:(void(^)(NSError* _Nullable error))completionBlock;

- (void)messageWithId:(NSString*)messageId
           completion:(void(^)(NSError* _Nullable error))completionBlock;

- (void)messageListWithCompletion:(void(^)(NSArray<D1CMessage*>* _Nullable messageList, NSError* _Nullable error))completionBlock;

- (void)markMessageListAsReadWithIdList:(NSArray<NSString*>*)messageIdList
                         completion:(void(^)(NSError* _Nullable error))completionBlock;

+ (void)reset;

@end

NS_ASSUME_NONNULL_END
