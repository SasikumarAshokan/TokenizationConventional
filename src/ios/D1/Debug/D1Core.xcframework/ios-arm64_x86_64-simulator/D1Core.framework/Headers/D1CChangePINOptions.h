//
//  ChangePINOptions.h
//  D1Core
//
//  Copyright © 2023 THALES. All rights reserved.
//

#ifndef D1CChangePINOptions_h
#define D1CChangePINOptions_h

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CChangePINOptions : NSObject

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithPinLength:(NSInteger)pinLength;

- (NSInteger)pinLength;

@end

#endif /* D1CChangePINOptions_h */

NS_ASSUME_NONNULL_END
