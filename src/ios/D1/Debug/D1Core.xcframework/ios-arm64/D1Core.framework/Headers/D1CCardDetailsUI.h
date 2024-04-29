//
//
// Copyright © 2022 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>

@class D1CDisplayTextField;
@class D1CCardClient;

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CCardDetailsUI : NSObject

- (instancetype)initWithPanTextField:(D1CDisplayTextField* _Nullable)panTextField
                 expiryDateTextField:(D1CDisplayTextField* _Nullable)expiryDateTextField
                        cvvTextField:(D1CDisplayTextField* _Nullable)cvvTextField
             cardHolderNameTextField:(D1CDisplayTextField* _Nullable)cardHolderNameTextField;

@property (weak) D1CCardClient* cardClient;
@property NSString* cardId;

@property D1CDisplayTextField* _Nullable panTextField;
@property D1CDisplayTextField* _Nullable cvvTextField;
@property D1CDisplayTextField* _Nullable expiryDateTextField;
@property D1CDisplayTextField* _Nullable cardHolderNameTextField;

// by default, it is  " "
@property NSString* panSeparatorCharacter;

// by default, it is "*"
@property NSString* panMaskCharacter;

// by default, MM/yy
@property NSString* expiryDateFormat;

- (void)showCardDetailsWithCompletion:(void(^)(NSError *_Nullable error))completion;
- (void)maskCardDetails;
- (void)wipe;

@end

NS_ASSUME_NONNULL_END
