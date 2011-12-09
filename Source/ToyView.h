//
//  ToyView.h
//  ToyCouch
//
//  Created by Jens Alfke on 12/8/11.
//  Copyright (c) 2011 Couchbase, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ToyDB.h"


typedef void (^ToyEmitBlock)(id key, id value);

/** A "map" function called when a document is to be added to a view.
    @param doc  The contents of the document being analyzed.
    @param emit  A block to be called to add a key/value pair to the view. Your block can call it zero, one or multiple times. */
typedef void (^ToyMapBlock)(NSDictionary* doc, ToyEmitBlock emit);


/** Standard query options for views. */
typedef struct ToyDBQueryOptions {
    NSString* startKey;
    NSString* endKey;
    int skip;
    int limit;
    BOOL descending;
    BOOL includeDocs;
    BOOL updateSeq;
} ToyDBQueryOptions;

extern const ToyDBQueryOptions kDefaultToyDBQueryOptions;


/** Represents a view available in a database. */
@interface ToyView : NSObject
{
    @private
    ToyDB* _db;
    NSString* _name;
    int _viewID;
    ToyMapBlock _mapBlock;
}

- (void) deleteView;

@property (readonly) ToyDB* database;
@property (readonly) NSString* name;

@property (readonly) ToyMapBlock mapBlock;
- (BOOL) setMapBlock: (ToyMapBlock)mapBlock version: (NSString*)version;

- (void) removeIndex;
- (BOOL) updateIndex;

- (NSDictionary*) queryWithOptions: (const ToyDBQueryOptions*)options;

@end
