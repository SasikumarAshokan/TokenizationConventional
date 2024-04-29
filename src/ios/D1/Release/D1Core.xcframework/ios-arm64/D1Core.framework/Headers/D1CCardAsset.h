//
//
// Copyright © 2021-2022 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <D1Core/D1CCardEnums.h>

@class D1CCardAssetContent;

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CCardAsset : NSObject

@property (readonly) D1CAssetContentType assetContentType;
@property (readonly) NSArray <D1CCardAssetContent*> *contentArray;

- (instancetype)initWithAssetContentType:(D1CAssetContentType)contentType
                            assetContent:(NSArray <D1CCardAssetContent*>*)contentArray;

@end

NS_ASSUME_NONNULL_END
