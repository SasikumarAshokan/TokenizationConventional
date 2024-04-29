//
//
// Copyright © 2023 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <D1Core/D1CPINEntryUIDelegate.h>

@class D1CSecureTextField;
@class D1CChangePINOptions;
@class D1CA2Client;

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CPINEntryUI : NSObject

@property NSString* baseUrl;
@property D1CA2Client* a2Client;
@property NSString* issuerId;

@property NSString *consumerId;
@property NSData *rsaExponent;
@property NSData *rsaModulus;

- (instancetype)initWithCardId:(NSString*)cardId
                  entryEditPin:(D1CSecureTextField *)entryEditPin
                confirmEditPin:(D1CSecureTextField *)confirmEditPin
                       options:(D1CChangePINOptions *)options
                      entryUIDelegate:(id<D1CPINEntryUIDelegate>)pinEntryUiDelegate;

- (void)wipe;

- (void)submitWithCompletion:(void(^)(NSError* _Nullable error))completion;

// MARK: testing usage
#ifdef DEBUG
- (void)submitWithoutValidation:(void(^)(NSError* _Nullable error))completion;
#endif

@end

NS_ASSUME_NONNULL_END
