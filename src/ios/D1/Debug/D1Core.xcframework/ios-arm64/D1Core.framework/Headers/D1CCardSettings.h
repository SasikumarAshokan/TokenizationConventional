//
//
// Copyright © 2023 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <D1Core/D1CCardSettingsEnums.h>

@class D1CCardControlSettings;
@class D1CCardGeographySettings;
@class D1CCardMerchantSettings;
@class D1CCardLimitSettings;
@class D1CCardPurchaseLimitSettings;
@class D1CCardWithdrawalLimitSettings;

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface D1CCardSettings : NSObject

@property (readonly) D1CCardControlSettings *control;
@property (readonly) D1CCardLimitSettings *limit;

- (instancetype)initWithCardControlSettings:(D1CCardControlSettings *)control
                                      limit:(D1CCardLimitSettings *)limit;

@end

__attribute__((visibility("default")))
@interface D1CCardControlSettings : NSObject

@property (readonly) NSNumber *isOnlinePaymentEnabled;
@property (readonly) NSNumber *_Nullable isContactlessEnabled;
@property (readonly) NSNumber *_Nullable isMagneticStripeEnabled;
@property (readonly) NSNumber *_Nullable isATMWithdrawalEnabled;
@property (readonly) NSNumber *isAbroadPaymentEnabled;

@property (readonly) NSArray<NSString *> *deniedCurrencyList;
@property (readonly) D1CCardGeographySettings *geography;
@property (readonly) D1CCardMerchantSettings *merchant;

- (instancetype)initWithIsOnlinePaymentEnabled:(NSNumber *)isOnlinePaymentEnabled
                          isContactlessEnabled:(NSNumber *_Nullable)isContactlessEnabled
                       isMagneticStripeEnabled:(NSNumber *_Nullable)isMagneticStripeEnabled
                        isATMWithdrawalEnabled:(NSNumber *_Nullable)isATMWithdrawalEnabled
                        isAbroadPaymentEnabled:(NSNumber *)isAbroadPaymentEnabled
                          deniedCurrencyList:(NSArray<NSString *> *)deniedCurrencyList
                                   geography:(D1CCardGeographySettings *)geography
                                    merchant:(D1CCardMerchantSettings *)merchant;

@end

__attribute__((visibility("default")))
@interface D1CCardGeographySettings : NSObject

@property (readonly) NSArray<NSNumber *> *regionList;   // D1CCardSettingsGeographyRegion
@property (readonly) NSArray<NSString *> *countryList;

- (instancetype)initWithRegionList:(NSArray<NSNumber *> *)regionList
                       countryList:(NSArray<NSString *> *)countryList;

@end

__attribute__((visibility("default")))
@interface D1CCardMerchantSettings : NSObject

@property (readonly) BOOL isGamblingMerchantEnabled;
@property (readonly) BOOL isAdultMerchantEnabled;
@property (readonly) BOOL isRiskyMerchantEnabled;

- (instancetype)initWithIsGamblingMerchantEnabled:(BOOL)isGamblingMerchantEnabled
                           isAdultMerchantEnabled:(BOOL)isAdultMerchantEnabled
                           isRiskyMerchantEnabled:(BOOL)isRiskyMerchantEnabled;

@end

__attribute__((visibility("default")))
@interface D1CCardLimitSettings : NSObject

@property (readonly) NSString *_Nullable currency;

@property (readonly) D1CCardPurchaseLimitSettings *_Nullable dailyPurchaseLimit;
@property (readonly) D1CCardPurchaseLimitSettings *_Nullable weeklyPurchaseLimit;
@property (readonly) D1CCardPurchaseLimitSettings *_Nullable monthlyPurchaseLimit;
@property (readonly) D1CCardPurchaseLimitSettings *_Nullable yearlyPurchaseLimit;

@property (readonly) D1CCardWithdrawalLimitSettings *_Nullable dailyWithdrawalLimit;
@property (readonly) D1CCardWithdrawalLimitSettings *_Nullable weeklyWithdrawalLimit;
@property (readonly) D1CCardWithdrawalLimitSettings *_Nullable monthlyWithdrawalLimit;
@property (readonly) D1CCardWithdrawalLimitSettings *_Nullable yearlyWithdrawalLimit;

- (instancetype)initWithCurrency:(NSString *_Nullable)currency
              dailyPurchaseLimit:(D1CCardPurchaseLimitSettings *_Nullable)dailyPurchaseLimit
             weeklyPurchaseLimit:(D1CCardPurchaseLimitSettings *_Nullable)weeklyPurchaseLimit
            monthlyPurchaseLimit:(D1CCardPurchaseLimitSettings *_Nullable)monthlyPurchaseLimit
             yearlyPurchaseLimit:(D1CCardPurchaseLimitSettings *_Nullable)yearlyPurchaseLimit
            dailyWithdrawalLimit:(D1CCardWithdrawalLimitSettings *_Nullable)dailyWithdrawalLimit
           weeklyWithdrawalLimit:(D1CCardWithdrawalLimitSettings *_Nullable)weeklyWithdrawalLimit
          monthlyWithdrawalLimit:(D1CCardWithdrawalLimitSettings *_Nullable)monthlyWithdrawalLimit
           yearlyWithdrawalLimit:(D1CCardWithdrawalLimitSettings *_Nullable)yearlyWithdrawalLimit;

@end

__attribute__((visibility("default")))
@interface D1CCardPurchaseLimitSettings : NSObject

@property (readonly) NSNumber *_Nullable periodType;  // D1CCardSettingsPeriodType
@property (readonly) NSNumber *_Nullable fixedPeriodIndex; // Integer
@property (readonly) NSInteger issuerLimit;
@property (readonly) NSInteger userLimit;
@property (readonly) double currentAmount;

- (instancetype)initWithCardSettingsPeriodType:(NSNumber *_Nullable)periodType
                                   fixedPeriodIndex:(NSNumber *_Nullable)fixedPeriodIndex
                                   issuerLimit:(NSInteger)issuerLimit
                                     userLimit:(NSInteger)userLimit
                                 currentAmount:(double)currentAmount;

@end

__attribute__((visibility("default")))
@interface D1CCardWithdrawalLimitSettings : NSObject

@property (readonly) NSNumber *_Nullable periodType;  // D1CCardSettingsPeriodType
@property (readonly) NSNumber *_Nullable fixedPeriodIndex; // Integer
@property (readonly) NSInteger issuerLimit;
@property (readonly) NSInteger userLimit;
@property (readonly) double currentAmount;

- (instancetype)initWithCardSettingsPeriodType:(NSNumber *_Nullable)periodType
                                   fixedPeriodIndex:(NSNumber *_Nullable)fixedPeriodIndex
                                   issuerLimit:(NSInteger)issuerLimit
                                     userLimit:(NSInteger)userLimit
                                 currentAmount:(double)currentAmount;

@end

NS_ASSUME_NONNULL_END
