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

#ifndef SecureLogAPI_SecureLog_h
#define SecureLogAPI_SecureLog_h

#import <Foundation/Foundation.h>
#import <SecureLogAPI/SecureLogConfig.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The protocol contains all functions to the app integrators to interact with Secure Log
*/
@protocol SecureLog<NSObject>

/**
 * There is no direct init function available.
 * Cast the SecureLogImpl object to this protocol and call below function to interact with Secure Log
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 * Set the secure log level to write in log file.
 * @param logLevel log level.
*/
- (void)setLevel:(SecureLogLevel)logLevel;

/**
 * Return array of log files that logged by secure log.
 * @return array of log files.
*/
- (NSArray<NSURL *> *)files;

/**
 * Delete all logs that logged by secure log.
 *
*/
- (void)deleteFiles;

@end

NS_ASSUME_NONNULL_END

#endif
