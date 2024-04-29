//
//
// Copyright © 2023 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface D1CAuthnEnrollInitResponseData : NSObject

@property NSString *enrollmentToken;
@property NSString *tenantId;
@property NSString *msUrl;

- (instancetype)initWithEnrollmentToken:(NSString*)enrollmentToken
                               tenantId:(NSString*)tenantId
                                  msUrl:(NSString*)msUrl;


@end

NS_ASSUME_NONNULL_END
