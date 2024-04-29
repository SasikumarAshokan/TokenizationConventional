/* -----------------------------------------------------------------------------
 *
 *     Copyright (c) 2020  -  THALES DEVELOPMENT - R&D
 *
 * -----------------------------------------------------------------------------
 * THALES MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR NON-INFRINGEMENT. THALES SHALL NOT BE
 * LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 *
 * THIS SOFTWARE IS NOT DESIGNED OR INTENDED FOR USE OR RESALE AS ON-LINE
 * CONTROL EQUIPMENT IN HAZARDOUS ENVIRONMENTS REQUIRING FAIL-SAFE
 * PERFORMANCE, SUCH AS IN THE OPERATION OF NUCLEAR FACILITIES, AIRCRAFT
 * NAVIGATION OR COMMUNICATION SYSTEMS, AIR TRAFFIC CONTROL, DIRECT LIFE
 * SUPPORT MACHINES, OR WEAPONS SYSTEMS, IN WHICH THE FAILURE OF THE
 * SOFTWARE COULD LEAD DIRECTLY TO DEATH, PERSONAL INJURY, OR SEVERE
 * PHYSICAL OR ENVIRONMENTAL DAMAGE ("HIGH RISK ACTIVITIES"). THALES
 * SPECIFICALLY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTY OF FITNESS FOR
 * HIGH RISK ACTIVITIES.
 *
 * -----------------------------------------------------------------------------
 */

#ifndef SecureLogAPI_SecureLogConfig_h
#define SecureLogAPI_SecureLogConfig_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The secure log log level.
*/
typedef NS_ENUM(NSInteger, SecureLogLevel) {
    /** 
     * Disables writing of logs for all levels.
    */
    SecureLogLevelOff   = 0,

    /** 
     * Log level - Fatal
    */
    SecureLogLevelFatal = 2,

    /** 
     * Log level - Error
    */
    SecureLogLevelError = 3,

    /** 
     * Log level - Warn
    */
    SecureLogLevelWarn  = 4,

    /** 
     * Log level - Info
    */
    SecureLogLevelInfo  = 6,

    /** 
     * Log level - Debug
    */
    SecureLogLevelDebug = 7
};

/**
 * The class contains all parameters which is required to initialise SecureLog.
 * Set all parameters value to this object and pass to SecureLogConfig initialise function
*/
@interface SecureLogConfigComponents : NSObject

/**
 * Optional parameter
 * This file Id is part of the log file name.
 * Default value: d5a1
 * Maximum length is 10 characters
 * Throw NSInvalidArgumentException if the length is more than 10 characters
*/
@property (nonatomic, strong) NSString *fileID;

/**
 * Mandatory parameter
 * Is required to retrieve public key and encrypt the log message (Max Length is 1024 characters)
 * Throw NSInvalidArgumentException if publicKeyModulus is nil or the length is more than 1024 characters
*/
@property (nonatomic, strong) NSData *publicKeyModulus;

/**
 * Mandatory parameter
 * Is required to retrieve public key and encrypt the log message (Max Length is 8 characters)
 * Throw NSInvalidArgumentException if publicKeyExponent is nil or the length is more than 8 characters
*/
@property (nonatomic, strong) NSData *publicKeyExponent;

/**
 * Optional parameter
 * To set a Secure logger rolling file max count
 * Default value: 8
 * Throw NSInvalidArgumentException if rollingFileMaxCount is equals to 0 or more than 99.
*/
@property (nonatomic, assign) NSUInteger rollingFileMaxCount;

/**
 * Optional parameter
 * To set a Secure logger rolling size
 * Default value: 1024
 * Throw NSInvalidArgumentException if rollingSizeInKB = 0
*/
@property (nonatomic, assign) NSUInteger rollingSizeInKB;

/**
 * Optional parameter
 * The directory to store the logs
 * Default value: Library/Application Support/Thales
 * Throw NSInvalidArgumentException if the directory is not existed
*/
@property (nonatomic, strong) NSURL *directory;

/**
 * Optional parameter
 * The level of log which you want the secure log to write to the file
 * Default value: SecureLogLevelWarn
 * Throw NSInvalidArgumentException if the level is not from SecureLogLevel
*/
@property (nonatomic, assign) SecureLogLevel logLevel;

@end



/**
 * The class to provide initialisation function to initialise SecureLog config, it takes the parameters from SecureLogConfigComponents.
 * All of parameters is read-only and can't be changed after the initWithConfigComponentsBuilder function is called
*/
@interface SecureLogConfig : NSObject

/**
 * Get the config file Id.
 */
@property (nonatomic, readonly, strong) NSString *fileID;

/**
 * Get the config public key modulus.
 */
@property (nonatomic, readonly, strong) NSData *publicKeyModulus;

/**
 * Get the config public key exponent.
 */
@property (nonatomic, readonly, strong) NSData *publicKeyExponent;

/**
 * Get the config logs directory.
 */
@property (nonatomic, readonly, strong) NSURL *directory;

/**
 * Get the config rolling file max count.
 */
@property (nonatomic, readonly) NSUInteger rollingFileMaxCount;

/**
 * Get the config rolling size.
 */
@property (nonatomic, readonly) NSUInteger rollingSizeInKB;

/**
 * Get the config log level.
 */
@property (nonatomic, readonly) SecureLogLevel logLevel;

/**
 * There is no direct init function available. The init function shall be done via SecureLogConfigComponents and return SecureLogConfig object to use
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 * Init secure log config with components builder
 * @param componentsBuilder components builder.
 * @return Instance of secure log config.
*/
- (instancetype)initWithConfigComponentsBuilder:(void(^)(SecureLogConfigComponents *))componentsBuilder;

@end

NS_ASSUME_NONNULL_END

#endif
