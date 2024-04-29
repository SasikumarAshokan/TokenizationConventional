//
//
// Copyright © 2022 THALES. All rights reserved.
//
    

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CCoreConfig : NSObject

+ (NSString*)version;

+ (void)setVersionInfo:(NSDictionary<NSString*, NSString*>*)versionInfo;

+ (NSDictionary<NSString*, NSString*>*)versionInfo;

@end

NS_ASSUME_NONNULL_END
