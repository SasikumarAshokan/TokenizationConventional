//
//
// Copyright © 2023 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>

@class D1CA2Client;
@class D1CUiDelegates;
@class D1CAuthnEnrollInitResponseData;

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CAuthn : NSObject

@property NSString *consumerId;
@property NSString *_Nullable msUrlInMemory;
@property NSString *_Nullable tenantIdInMemory;

+ (void)reset;
+ (NSString * _Nullable)msUrl;
+ (NSString * _Nullable)tenantId;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype _Nullable)initWithBaseUrl:(NSString*)baseUrl
                                 issuerId:(NSString*)issuerId
                                 a2Client:(D1CA2Client*)a2Client
                            a2UiDelegates:(D1CUiDelegates*)a2UiDelegates
                                    error:(NSError **)error;

- (void)enrollAuthnCredentialsWithCompletion:(void(^)(D1CAuthnEnrollInitResponseData *enrollInitRespData, NSError *_Nullable error))completion;

- (void)notifyEnrollmentCompletionWithClientID:(NSString*)clientID
                                     authnType:(NSString*)authnType
                                  localNSError:(NSError*_Nullable)localError
                                    completion:(void(^)(NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
