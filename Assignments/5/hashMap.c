/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Mario Bocaletti 
 * Date: 8/8/18
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
//#pragma warning(disable:4996)

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
  assert(map != 0);
  assert(map->table != 0);
      //pointer to traverse the links
  HashLink* linkptr = 0;
  HashLink* garbage = 0;

  for (int i = (hashMapCapacity(map) - 1); i >= 0; i--) {
    linkptr = map->table[i];
      //delete all the links
    while(linkptr != 0){
      garbage = linkptr;
      linkptr = linkptr->next; 
      hashLinkDelete(garbage);
    }
  }
  free(map->table);
  map->size = 0;
  garbage = 0;
  linkptr = 0;
}
/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
    map = 0;
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
      //pointer to traverse the links
  HashLink* linkptr = 0;
      //get table index 
  int index = abs(HASH_FUNCTION(key) % hashMapCapacity(map));
      //set iterator pointer
  linkptr = map->table[index];
    //traverse buckets
  while (linkptr != 0){
    if (strcmp(linkptr->key,key) == 0) {
      return &linkptr->value;
    }
    linkptr = linkptr->next;
  }
  return 0;
}
/**
 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
      //check pointers
    assert(map != 0);
    assert(map->table != 0);
      //pointer to traverse the links
    HashLink* linkptr = 0;
      //create new table
    HashMap* newMap = hashMapNew(capacity);  
      //rehash values
    for (int i = hashMapCapacity(map) - 1; i >= 0; i--) {
      linkptr = map->table[i];
      while(linkptr != 0) {
        hashMapPut(newMap,linkptr->key,linkptr->value);
        linkptr = linkptr->next;
      }
    }
      //clear old map links
    hashMapCleanUp(map);
		//populate old map with new links
	map->table = newMap->table;
	map->size = newMap->size;
	map->capacity = newMap->capacity;
		//delete the old map
	free(newMap);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    //check the pointers
  assert(map != 0);
  assert(key != 0);
  assert(map->table != 0);

  float loadFactor = 0;
  const int capacity = hashMapCapacity(map);

    //get the index
  int index = abs(HASH_FUNCTION(key) % capacity);
    //pointer to iterate table
  HashLink* linkptr = map->table[index];
  int* updateValue; 
    //search for the key
  if (hashMapContainsKey(map,key)) {
    updateValue = hashMapGet(map,key);
    *updateValue = value;
  } else {
          //increase the size
        map->size++;
        //add first link
    if (map->table[index] == 0) {
        map->table[index] = hashLinkNew(key,value,0);
    } else {
          //find last link
        while(linkptr->next != 0) {
          linkptr = linkptr->next;
        }
          //connect new link to back
        linkptr->next = hashLinkNew(key,value,0);
    }
  }
    //rehash if needed
  loadFactor = hashMapTableLoad(map);
  if (loadFactor >= MAX_TABLE_LOAD) {
	resizeTable(map,2 * capacity);
  }
  return;
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
  int index;
  HashLink* linkptr = 0;
  HashLink* prev = 0;
  if (hashMapContainsKey(map,key)) {
      //get the index
    index = abs(HASH_FUNCTION(key) % hashMapCapacity(map));
      //pointer to iterate table
    linkptr = map->table[index];
    while(linkptr != 0) {
        //find the value
      if (strcmp(linkptr->key,key) == 0) {
          //connect tail to bucket head if 
          //first value is removed
        if(linkptr == map->table[index]) {
          map->table[index] = linkptr->next;
          //connect tail to link before deleted link otherwise
        } else {
          prev->next = linkptr->next;
        }
          hashLinkDelete(linkptr);
          map->size--;
      }
      prev = linkptr;
      linkptr = linkptr->next;
    }
  }
  return;
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
  assert(map != 0);
  assert(key != 0);
    //get the index
  int index = abs(HASH_FUNCTION(key) % hashMapCapacity(map));
    //pointer to iterate table
  HashLink* linkptr = map->table[index]; 
    //search for the key
  while (linkptr != 0){
    if (strcmp(linkptr->key,key) == 0) {
      return 1;
    }
    linkptr = linkptr->next;
  }
  return 0;
}


/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
  assert(map != 0);
  return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
  assert(map != 0);
  return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
  int emptyBuckets = 0;
  for (int i = (hashMapCapacity(map) - 1); i >= 0; i--) {
    if (map->table[i] == 0) {
      emptyBuckets++;
    }
  }
  return emptyBuckets;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
  assert(map != 0);
  return (float)hashMapSize(map)/(float)hashMapCapacity(map);
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
  assert(map != 0);
  HashLink* linkptr = 0;
  for (int i = 0; i < hashMapCapacity(map); i++) {
    linkptr = map->table[i];
    printf("\n\tBucket %d: ",i);
    while (linkptr != 0) {
      printf("%d",linkptr->value);
      linkptr = linkptr->next;
    }
  }
}
