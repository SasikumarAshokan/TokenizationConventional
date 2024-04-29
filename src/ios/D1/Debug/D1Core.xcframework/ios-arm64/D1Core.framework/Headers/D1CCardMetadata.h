//
//
// Copyright © 2021-2022 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <D1Core/D1CCardEnums.h>
#import <D1Core/D1CCardEnumsCaaS.h>

@class D1CCardAsset;
@class D1CA2Client;

NS_ASSUME_NONNULL_BEGIN

@interface D1CCardMetadata : NSObject

@property NSString *cardLast4;
@property NSString *cardExpiry;
@property D1CCardScheme cardScheme;
@property D1CCardState cardState;
// CaaS related properties
@property D1COngoingOperation ongoingOperation;
@property D1CStateReason stateReason;

// additional internal properties so that it could download the assets
@property NSArray<NSString*> *cardArtManifest;
@property NSString* baseUrl;
@property D1CA2Client* a2Client;
@property NSString* cardId;
@property NSString* issuerId;

- (instancetype)initWithScheme:(D1CCardScheme)scheme
                         last4:(NSString*)last4
                        expiry:(NSString*)expiry
                         state:(D1CCardState)state;

- (void)cardAssetArrayWithCompletion:(void(^)(NSArray<D1CCardAsset*>* _Nullable, NSError* _Nullable))completionBlock;

@end

NS_ASSUME_NONNULL_END
