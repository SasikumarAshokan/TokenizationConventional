//
//
// Copyright © 2023 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>

@class D1CCardMetadata;

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CCard : NSObject

@property (readonly) D1CCardMetadata *cardMetadata;
@property (readonly) NSString *cardId;

- (instancetype)initWithCardMetadata:(D1CCardMetadata *)cardMetadata;

@end

NS_ASSUME_NONNULL_END
