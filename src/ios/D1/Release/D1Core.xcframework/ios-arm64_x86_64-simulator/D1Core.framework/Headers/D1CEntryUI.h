//
//
// Copyright © 2022 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>

@class D1CSecureTextField;

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CEntryUI : NSObject

@property D1CSecureTextField *entryTextField;

- (instancetype)initWithEntryTextField:(D1CSecureTextField *_Nullable)entryTextField;

@end

NS_ASSUME_NONNULL_END
