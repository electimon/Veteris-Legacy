/*	
    NSURLCredential.h
    Copyright (C) 2003-2007, Apple Inc. All rights reserved.    
    
    Public header file.
*/

// Note: To use the APIs described in these headers, you must perform
// a runtime check for Foundation-462.1 or later.
#import <AvailabilityMacros.h>
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

#import <Foundation/NSObject.h>
#import <Security/Security.h>

@class NSString;
@class NSArray;

/*!
    @enum NSURLCredentialPersistence
    @abstract Constants defining how long a credential will be kept around
    @constant NSURLCredentialPersistenceNone This credential won't be saved.
    @constant NSURLCredentialPersistenceForSession This credential will only be stored for this session.
    @constant NSURLCredentialPersistencePermanent This credential will be stored permanently and shared with other applications.
*/

enum {
    NSURLCredentialPersistenceNone,
    NSURLCredentialPersistenceForSession,
    NSURLCredentialPersistencePermanent
};
typedef NSUInteger NSURLCredentialPersistence;

@class NSURLCredentialInternal;

/*!
    @class NSURLCredential
    @discussion This class is an immutable object representing an authentication credential.  The actual type of the credential is determined by the constructor called in the categories declared below.
*/

@interface NSURLCredential : NSObject <NSCopying>
{
    @private
    __strong NSURLCredentialInternal *_internal;
}

/*!
    @method persistence
    @abstract Determine whether this credential is or should be stored persistently
    @result A value indicating whether this credential is stored permanently, per session or not at all.
 */
- (NSURLCredentialPersistence)persistence;

@end

/*!
    @class NSURLCredential(NSInternetPassword)
    @discussion This category defines the methods available to an NSURLCredential created to represent an internet password credential.  These are most commonly used for resources that require a username and password combination.
 */
@interface NSURLCredential(NSInternetPassword)

/*!
    @method initWithUser:password:persistence:
    @abstract Initialize a NSURLCredential with a user and password
    @param user the username
    @param password the password
    @param persistence enum that says to store per session, permanently or not at all
    @result The initialized NSURLCredential
*/
- (id)initWithUser:(NSString *)user password:(NSString *)password persistence:(NSURLCredentialPersistence)persistence;

/*!
    @method credentialWithUser:password:persistence:
    @abstract Create a new NSURLCredential with a user and password
    @param user the username
    @param password the password
    @param persistence enum that says to store per session, permanently or not at all
    @result The new autoreleased NSURLCredential
*/
+ (NSURLCredential *)credentialWithUser:(NSString *)user password:(NSString *)password persistence:(NSURLCredentialPersistence)persistence;

/*!
    @method user
    @abstract Get the username
    @result The user string
*/
- (NSString *)user;

/*!
    @method password
    @abstract Get the password
    @result The password string
    @discussion This method might actually attempt to retrieve the
    password from an external store, possible resulting in prompting,
    so do not call it unless needed.
*/
- (NSString *)password;

/*!
    @method hasPassword
    @abstract Find out if this credential has a password, without trying to get it
    @result YES if this credential has a password, otherwise NO
    @discussion If this credential's password is actually kept in an
    external store, the password method may return nil even if this
    method returns YES, since getting the password may fail, or the
    user may refuse access.
*/
- (BOOL)hasPassword;

@end

/*!
    @class NSURLCredential(NSClientCertificate)
    @discussion This category defines the methods available to an NSURLCredential created to represent a client certificate credential.  Client certificates are commonly stored on the users computer in the keychain and must be presented to the server during a handshake.
*/
@interface NSURLCredential(NSClientCertificate)

/*!
    @method initWithIdentity:certificateArray:persistence:
    @abstract Initialize an NSURLCredential with an identity and array of at least 1 client certificates (SecCertificateRef)
    @param identity a SecIdentityRef object
    @param certArray an array containing at least one SecCertificateRef objects
    @param persistence enum that says to store per session, permanently or not at all
    @result the Initialized NSURLCredential
 */
- (id)initWithIdentity:(SecIdentityRef)identity certificates:(NSArray *)certArray persistence:(NSURLCredentialPersistence) persistence __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

/*!
    @method credentialWithCertificateArray:password:persistence:
    @abstract Create a new NSURLCredential with an identity and certificate array
    @param identity a SecIdentityRef object
    @param certArray an array containing at least one SecCertificateRef objects
    @param persistence enum that says to store per session, permanently or not at all
    @result The new autoreleased NSURLCredential
 */
+ (NSURLCredential *)credentialWithIdentity:(SecIdentityRef)identity certificates:(NSArray *)certArray persistence:(NSURLCredentialPersistence)persistence __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

/*!
    @method identity
    @abstract Returns the SecIdentityRef of this credential, if it was created with a certificate and identity
    @result A SecIdentityRef or NULL if this is a username/password credential
 */
- (SecIdentityRef)identity __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

/*!
    @method certificateArray
    @abstract Returns an NSArray of SecCertificateRef objects representing the client certificate for this credential, if this credential was created with an identity and certificate.
    @result an NSArray of SecCertificateRef or NULL if this is a username/password credential
 */
- (NSArray *)certificates __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end

@interface NSURLCredential(NSServerTrust)

/*!
    @method initWithTrust:(SecTrustRef) trust
    @abstract Initialize a new NSURLCredential which specifies that the specified trust has been accepted.
    @result the Initialized NSURLCredential
 */
- (id)initWithTrust:(SecTrustRef)trust __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

/*!
    @method continueWithHandshakeCredential
    @abstract Create a new NSURLCredential which specifies that a handshake has been trusted.
    @result The new autoreleased NSURLCredential
 */
+ (NSURLCredential *)credentialForTrust:(SecTrustRef)trust __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end


#endif
