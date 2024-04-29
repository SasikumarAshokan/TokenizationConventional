//
//
// Copyright © 2022 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>

@class D1CPinDisplayTextField;

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CCardPinUI : NSObject

@property D1CPinDisplayTextField *pinTextField;

- (instancetype)initWithPinTextField:(D1CPinDisplayTextField *_Nullable)pinTextField;

@end

NS_ASSUME_NONNULL_END
