//
//
// Copyright © 2023 THALES. All rights reserved.
//
    

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CWalletExtensionStorage : NSObject

- (instancetype _Nullable)initWithAppGroupId:(NSString*)appGroupId error:(NSError**)error;

- (BOOL)setString:(NSString*)value forKey:(NSString*)key error:(NSError**)error;
- (BOOL)setImage:(UIImage*)image fileName:(NSString*)fileName error:(NSError**)error;
- (BOOL)setArray:(NSArray<NSDictionary<NSString*,NSString*>*>*)values forKey:(NSString*)key error:(NSError**)error;

- (NSString* _Nullable)stringValueForKey:(NSString*)key error:(NSError**)error;
- (UIImage* _Nullable)imageForFileName:(NSString*)fileName;
- (NSArray<NSDictionary<NSString*,NSString*>*>* _Nullable)arrayValueForKey:(NSString*)key error:(NSError**)error;

+ (void)reset;
+ (NSString* _Nullable)appGroupIdWithError:(NSError**)error;

@end

NS_ASSUME_NONNULL_END
