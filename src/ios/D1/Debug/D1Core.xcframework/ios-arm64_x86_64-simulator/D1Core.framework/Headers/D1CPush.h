//
//
// Copyright © 2021-2022 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CPush : NSObject

+ (void)updateToken:(NSString *)pushToken;
+ (NSString * _Nullable)pushToken;

@end

NS_ASSUME_NONNULL_END
