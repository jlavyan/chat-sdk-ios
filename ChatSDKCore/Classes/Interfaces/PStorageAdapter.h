//
//  PStorageAdapter.h
//  Pods
//
//  Created by Benjamin Smiley-andrews on 25/11/2015.
//
//

#ifndef PStorageAdapter_h
#define PStorageAdapter_h

#import "PMessage.h"
#import "PThread_.h"

#define bUserEntity @"CDUser"
#define bMessageEntity @"CDMessage"
#define bThreadEntity @"CDThread"
#define bUserAccountEntity @"CDUserAccount"
#define bMetaDataEntity @"CDMetaData"
#define bUserConnectionEntity @"CDUserConnection"

#define bMessageOrderNewestFirst = 1;
#define bMessageOrderOldestFirst = 2;

@class BMessageDef;
@class BThreadDef;
@class NSFetchRequest;

typedef enum {
    bQueueTypeMain,
    bQueueTypeBackground,
} bQueueType;

@protocol PStorageAdapter <NSObject>

-(NSArray *) fetchEntitiesWithName: (NSString *) entityName withPredicate: (NSPredicate *) predicate;
-(NSArray *) fetchEntitiesWithName: (NSString *) entityName;
-(id) fetchEntityWithID: (NSString *) entityID withType: (NSString *) type;
-(id) fetchOrCreateEntityWithID: (NSString *) entityID withType: (NSString *) type;
-(id) fetchOrCreateEntityWithPredicate: (NSPredicate *) predicate withType: (NSString *) type;
-(id<PThread>) fetchThreadWithUsers: (NSArray *) users;
-(id) executeFetchRequest: (NSFetchRequest *) fetchRequest entityName: (NSString *) entityName predicate: (NSPredicate *) predicate;

-(RXPromise *) unreadMessagesCount: (NSString *) threadEntityID;
-(RXPromise *) threadsWithType: (bThreadType) type;
-(RXPromise *) privateThreadUnreadMessageCount;
-(RXPromise *) publicThreadUnreadMessageCount;
-(RXPromise *) unreadMessages: (NSString *) threadEntityID;

-(id<PMessage>) createMessageEntity;
-(id<PThread>) createThreadEntity;

-(RXPromise *) save;
-(RXPromise *) saveToStore;
-(RXPromise *) saveBackground;
//-(void) saveToStoreOnMain;

-(id) createEntity: (NSString *) entityName;

-(void) beginUndoGroup;
-(void) endUndoGroup;
-(void) undo;

-(void) deleteEntity: (id) entity;
-(void) deleteEntitiesWithType: (NSString *) type;
-(void) deleteEntities: (NSArray *) entities;
-(void) deleteAllData;

-(id<PThread>) threadForEntityID: (NSString *) entityID;
-(id<PUser>) userForEntityID: (NSString *) entityID;
-(id<PMessage>) messageForEntityID: (NSString *) entityID;

-(NSArray *) fetchUserConnectionsWithType: (bUserConnectionType) type entityID: (NSString *) entityID;
-(NSArray *) fetchUserConnectionsWithType: (bUserConnectionType) type;

-(NSArray<PMessage> *) loadMessagesForThread: (id<PThread>) thread fromDate: (NSDate *) date count: (int) count newestFirst: (BOOL) newestFirst;
-(NSArray<PMessage> *) loadAllMessagesForThread: (id<PThread>) thread newestFirst: (BOOL) newestFirst;
-(NSArray<PMessage> *) loadMessagesForThread: (id<PThread>) thread fromDate: (NSDate *) date count: (int) count;
-(NSArray<PMessage> *) loadMessagesForThread: (id<PThread>) thread newest: (int) count;
-(NSArray<PMessage> *) loadMessagesForThread: (id<PThread>) thread oldest: (int) count;

//-(RXPromise *) performOnPrivate: (id (^)(void)) block;
-(void) performOnMain: (void(^)(void)) block;
-(void) performOnMainAndWait:(void(^)(void)) block;

//-(RXPromise *) performOnPrivateAndSave:(id (^)(void))block;
-(RXPromise *) performOnMainAndSave:(id (^)(void))block;

//-(bQueueType) queueType;


@end

#endif /* PStorageAdapter_h */
