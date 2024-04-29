//
//
// Copyright © 2021-2022 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <D1Core/D1CCardEnums.h>

NS_ASSUME_NONNULL_BEGIN

@interface D1CCardPushDetails: NSObject

@property NSData *encryptedCardDetails;
@property NSString *publicKeyIdentifier;
@property D1CCardScheme scheme;
@property NSData *_Nullable fpanId;
@property NSString *last4;
@property NSString *_Nullable cardHolderName;

- (instancetype)initWithEncryptedCardDetails:(NSData*)encryptedCardDetails
                         publicKeyIdentifier:(NSString*)publicKeyId
                                      scheme:(D1CCardScheme)scheme
                                      fpanId:(NSData*_Nullable)fpanId
                                   cardLast4:(NSString*)last4
                              cardHolderName:(NSString*_Nullable)cardHolderName;

- (void)wipe;

@end

NS_ASSUME_NONNULL_END
