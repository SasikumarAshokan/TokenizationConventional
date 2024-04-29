//
//
// Copyright © 2021-2022 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "D1CCardEnums.h"
#import "D1CCardEnumsCaaS.h"
#import "D1CCardActivationMethod.h"
#import "D1CCardPushDetailsEnums.h"
#import "D1Core/D1CPINEntryUI.h"
#import "D1Core/D1CChangePINOptions.h"
#import "D1Core/D1CPINEntryUIDelegate.h"

@class D1CCardMetadata;
@class D1CCardPushDetails;
@class D1CVirtualCard;
@class D1CPhysicalCardPin;
@class D1CA2Client;
@class D1CUiDelegates;
@class D1CEntryUI;
@class D1CCardPinUI;
@class D1CCardDetailsUI;
@class D1CCard;
@class D1CCardSettings;
@class D1CCardControlSettings;
@class D1CCardLimitSettings;

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CCardClient : NSObject
@property NSString *consumerId;
@property NSData *rsaExponent;
@property NSData *rsaModulus;

+ (void)reset;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype _Nullable)initWithBaseUrl:(NSString*)baseUrl
                                 issuerId:(NSString*)issuerId
                                 a2Client:(D1CA2Client*)a2Client
                            a2UiDelegates:(D1CUiDelegates*)a2UiDelegates
                                    error:(NSError **)error;
- (void)virtualCardWithCardId:(NSString*)cardId
                   completion:(void(^)(D1CVirtualCard *_Nullable virtualCard, NSError *_Nullable error))completion;
- (void)displayCardDetailsWithCardId:(NSString*)cardId
                       cardDetailsUi:(D1CCardDetailsUI*)cardDetailsUi
                          completion:(void(^)(NSError *_Nullable error))completion;
- (void)metadataWithCardId:(NSString*)cardId
                completion:(void(^)(D1CCardMetadata *_Nullable cardMetadata, NSError *_Nullable error))completion;
- (void)cardPushDetailsWithCardId:(NSString*)cardId 
                       walletType:(D1CWalletType)walletType
                          context:(D1CCardPushDetailsContext)context
                       completion:(void(^)(D1CCardPushDetails *_Nullable cardPushDetails, NSError *_Nullable error))completion;
- (void)digitalCardAuthCodeWithCardId:(NSString*)cardId
                        digitalCardId:(NSString*)digitalCardId
                           completion:(void(^)(NSMutableData *_Nullable digitalCardAuthCode, NSError *_Nullable error))completion;
- (void)displayPhysicalCardPinWithCardId:(NSString*)cardId
                               cardPinUi:(D1CCardPinUI *)cardPinUi
                              completion:(void(^)(NSError *_Nullable error))completion;
- (D1CPINEntryUI *_Nullable)setPhysicalCardPinWithCardId:(NSString*)cardId
                                            entryEditPin:(D1CSecureTextField *)entryEditPin
                                          confirmEditPin:(D1CSecureTextField *)confirmEditPin
                                                 options:(D1CChangePINOptions *)options
                                         entryUIDelegate:(id<D1CPINEntryUIDelegate>)entryUIDelegate
                                                   error:(NSError **)error;
- (void)cardActivationMethodWithCardId:(NSString*)cardId
                                    completion:(void(^)(D1CCardActivationMethod activationMethod, NSError *_Nullable error))completion;
- (void)activatePhysicalCardWithCardId:(NSString*)cardId
                               entryUi:(D1CEntryUI *)entryUi
                            completion:(void(^)(NSError *_Nullable error))completion;
- (void)activateDigitalCard:(NSString*)digitalCardId
                 completion:(void(^)(NSString *_Nullable operationId, NSError *_Nullable error))completion;
- (void)cardListWithCompletion:(void(^)(NSArray<D1CCard *> *_Nullable cardList, NSError *_Nullable error))completion;
- (void)suspendCardWithCardId:(NSString*)cardId
                   completion:(void(^)(NSError *_Nullable error))completion;
- (void)resumeCardWithCardId:(NSString*)cardId
                  completion:(void(^)(NSError *_Nullable error))completion;
- (void)replaceCardWithCardId:(NSString*)cardId
                       reason:(D1CStateReason)reason
                   completion:(void(^)(NSString *_Nullable newCardId, NSError *_Nullable error))completion;
- (void)cardSettingsWithCardId:(NSString*)cardId
                    completion:(void(^)(D1CCardSettings *_Nullable cardSettings, NSError *_Nullable error))completion;
- (void)updateCardControlSettingsWithCardId:(NSString*)cardId
                        cardControlSettings:(D1CCardControlSettings *)cardControlSettings
                                 completion:(void(^)(NSError *_Nullable error))completion;
- (void)updateCardLimitSettingsWithCardId:(NSString*)cardId
                        cardLimitSettings:(D1CCardLimitSettings *)cardLimitSettings
                               completion:(void(^)(NSError *_Nullable error))completion;
@end

NS_ASSUME_NONNULL_END
