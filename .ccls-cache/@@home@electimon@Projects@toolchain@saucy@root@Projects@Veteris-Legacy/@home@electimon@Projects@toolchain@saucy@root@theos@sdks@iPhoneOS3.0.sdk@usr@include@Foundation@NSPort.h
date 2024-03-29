/*	NSPort.h
	Copyright (c) 1994-2007, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

typedef int NSSocketNativeHandle;

@class NSRunLoop, NSMutableArray, NSDate;
@class NSConnection, NSPortMessage;
@class NSData;

FOUNDATION_EXPORT NSString * const NSPortDidBecomeInvalidNotification;

@interface NSPort : NSObject <NSCopying, NSCoding>

// For backwards compatibility on Mach, +allocWithZone: returns
// an instance of the NSMachPort class when sent to the NSPort
// class.  Otherwise, it returns an instance of a concrete
// subclass which can be used for messaging between threads
// or processes on the local machine.
+ (id)allocWithZone:(NSZone *)zone;

+ (NSPort *)port;

- (void)invalidate;
- (BOOL)isValid;

- (void)setDelegate:(id)anId;
- (id)delegate;

// These two methods should be implemented by subclasses
// to setup monitoring of the port when added to a run loop,
// and stop monitoring if needed when removed;
// These methods should not be called directly!
- (void)scheduleInRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode;
- (void)removeFromRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode;

// DO Transport API; subclassers should implement these methods
- (NSUInteger)reservedSpaceLength;	// default is 0
- (BOOL)sendBeforeDate:(NSDate *)limitDate components:(NSMutableArray *)components from:(NSPort *) receivePort reserved:(NSUInteger)headerSpaceReserved;
- (BOOL)sendBeforeDate:(NSDate *)limitDate msgid:(NSUInteger)msgID components:(NSMutableArray *)components from:(NSPort *)receivePort reserved:(NSUInteger)headerSpaceReserved;
	// The components array consists of a series of instances
	// of some subclass of NSData, and instances of some
	// subclass of NSPort; since one subclass of NSPort does
	// not necessarily know how to transport an instance of
	// another subclass of NSPort (or could do it even if it
	// knew about the other subclass), all of the instances
	// of NSPort in the components array and the 'receivePort'
	// argument MUST be of the same subclass of NSPort that
	// receives this message.  If multiple DO transports are
	// being used in the same program, this requires some care.

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_IPHONE_SIMULATOR
- (void)addConnection:(NSConnection *)conn toRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode;
- (void)removeConnection:(NSConnection *)conn fromRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode;
	// The default implementation of these two methods is to
	// simply add the receiving port to the run loop in the
	// given mode.  Subclassers need not override these methods,
	// but can if they need to do extra work.
#endif

@end

@interface NSObject (NSPortDelegateMethods)

- (void)handlePortMessage:(NSPortMessage *)message;
	// This is the delegate method that subclasses should send
	// to their delegates, unless the subclass has something
	// more specific that it wants to try to send first
@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)

@interface NSMachPort : NSPort {
    @private
    id _delegate;
    NSUInteger _flags;
    uint32_t _machPort;
    NSUInteger _reserved;
}

+ (NSPort *)portWithMachPort:(uint32_t)machPort;
- (id)initWithMachPort:(uint32_t)machPort;	// designated initializer

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED
enum {
    NSMachPortDeallocateNone = 0,
    NSMachPortDeallocateSendRight = (1 << 0),
    NSMachPortDeallocateReceiveRight = (1 << 1)
};

+ (NSPort *)portWithMachPort:(uint32_t)machPort options:(NSUInteger)f AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (id)initWithMachPort:(uint32_t)machPort options:(NSUInteger)f AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
#endif

- (uint32_t)machPort;

- (void)scheduleInRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode;
- (void)removeFromRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode;
	// If you subclass NSMachPort, you have to override these 2
	// methods from NSPort; since this is complicated, subclassing
	// NSMachPort is not recommended

@end

@interface NSObject (NSMachPortDelegateMethods)

// Delegates are sent this if they respond, otherwise they
// are sent handlePortMessage:; argument is the raw Mach message
- (void)handleMachMessage:(void *)msg;

@end

#endif

// A subclass of NSPort which can be used for local
// message sending on all platforms.
@interface NSMessagePort : NSPort {
    @private
    void * __strong _port;
    id _delegate;
}

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32 || TARGET_IPHONE_SIMULATOR

// A subclass of NSPort which can be used for remote
// message sending on all platforms.

@interface NSSocketPort : NSPort {
    @private
    void *_receiver;
    void *_connectors;
    void *_loops;
    void *_data;
    id _signature;
    id _delegate;
    id _lock;
    NSUInteger _maxSize;
    NSUInteger _maxSockets;
    NSUInteger _reserved;
}

- (id)init;
- (id)initWithTCPPort:(unsigned short)port;
- (id)initWithProtocolFamily:(int)family socketType:(int)type protocol:(int)protocol address:(NSData *)address;
- (id)initWithProtocolFamily:(int)family socketType:(int)type protocol:(int)protocol socket:(NSSocketNativeHandle)sock;
- (id)initRemoteWithTCPPort:(unsigned short)port host:(NSString *)hostName;
- (id)initRemoteWithProtocolFamily:(int)family socketType:(int)type protocol:(int)protocol address:(NSData *)address;
- (int)protocolFamily;
- (int)socketType;
- (int)protocol;
- (NSData *)address;
- (NSSocketNativeHandle)socket;

@end

#endif

