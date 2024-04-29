//
//
// Copyright © 2021-2022 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface D1CVirtualCard : NSObject

@property (readonly) NSData *pan;
@property (readonly) NSData *expiryDate;
@property (readonly) NSData *cvv;
@property (readonly) NSData *_Nullable cardHolderName;

- (instancetype)initWithPan:(NSData*)panData
                 expiryDate:(NSData*)expiryDateData
                        cvv:(NSData*)cvvData
             cardHolderName:(NSData* _Nullable)cardHolderNameData;

- (void)wipe;

@end

NS_ASSUME_NONNULL_END
