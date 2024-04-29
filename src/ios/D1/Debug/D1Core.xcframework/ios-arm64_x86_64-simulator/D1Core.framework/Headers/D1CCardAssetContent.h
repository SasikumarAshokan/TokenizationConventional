//
//
// Copyright © 2021-2022 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <D1Core/D1CCardEnums.h>

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CCardAssetContent : NSObject
@property (readonly) NSString *encodedData;
@property (readonly) NSInteger width;
@property (readonly) NSInteger height;
@property (readonly) D1CCardMimeType mimeType;

- (instancetype)initWithMimeType:(D1CCardMimeType)mimeType
                     encodedData:(NSString*)encodedData
                           width:(NSInteger)width
                          height:(NSInteger)height;
@end

NS_ASSUME_NONNULL_END
