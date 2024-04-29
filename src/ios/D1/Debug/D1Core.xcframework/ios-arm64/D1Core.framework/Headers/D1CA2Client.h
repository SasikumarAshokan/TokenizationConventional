//
//
// Copyright © 2021-2022 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>

@class D1CUiDelegates;
@class D1CA2AuthorizeRequest;
@class D1CMessagingClient;

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CA2Client : NSObject

@property D1CMessagingClient* _Nullable messagingClient;

+ (NSString* _Nullable)appInstanceIdWithError:(NSError **)error;
+ (void)reset;

- (instancetype)init NS_UNAVAILABLE;
// If appGroupId is nil, storage use app private group (not shared with other apps)
// If appGroupId is not nil, storage use app shared group (shared with other app from same developer)
// Reference: https://developer.apple.com/documentation/security/keychain_services/keychain_items/sharing_access_to_keychain_items_among_a_collection_of_apps/
- (instancetype _Nullable)initWithBaseUrl:(NSString *)baseUrl issuerId:(NSString *)issuerId appGroupId:(NSString* _Nullable)appGroupId error:(NSError **)error;

- (void)login:(NSData *)issuerToken uiDelegates:(D1CUiDelegates *)uiDelegates completion:(void(^)(NSError *_Nullable error))completion;
- (void)authorize:(D1CA2AuthorizeRequest *)authorizeRequest uiDelegates:(D1CUiDelegates *)uiDelegates completion:(void(^)(NSMutableData *_Nullable authorizationToken, NSError *_Nullable error))completion;
- (void)logoutWithCompletion:(void(^)(NSError *_Nullable error))completion;

- (void)wipe;

@end

NS_ASSUME_NONNULL_END
