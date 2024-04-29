//
//
// Copyright © 2021-2022 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface D1CA2AuthorizeRequest : NSObject

@property (copy) NSString *scope;
@property (copy) NSString *audience;

- (instancetype)init NS_UNAVAILABLE;

@end

__attribute__((visibility("default")))
@interface D1CA2AuthorizeRequestBuilder : NSObject

@property (copy, readonly) NSString *scope;
@property (copy) NSString *audience;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithScope:(NSString *)scope;

- (D1CA2AuthorizeRequest *)build;

@end

NS_ASSUME_NONNULL_END
