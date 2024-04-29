//
//  D1CPINEntryUIDelegate.h
//  D1Core
//
//  Copyright © 2023 THALES. All rights reserved.
//

#ifndef D1CPINEntryUIDelegate_h
#define D1CPINEntryUIDelegate_h

#import <D1Core/D1CCardEnums.h>

@class D1CPINEntryUI;

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@protocol D1CPINEntryUIDelegate <NSObject>
- (void)pinEntryUI:(D1CPINEntryUI *_Nonnull)pinEntryUI pinEvent:(D1CPINEvent)pinEvent  additionalInfo:(NSString *_Nullable)info;
@end

NS_ASSUME_NONNULL_END

#endif /* D1CPINEntryUIDelegate_h */
