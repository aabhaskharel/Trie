#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define SIZE (256)

struct trie {
  struct trie *children[SIZE];
  bool isEnd;
};

int encode(u32 len, u8 * key)
{
  u8 *temp=(u8*)malloc(sizeof(key));
  for(int i=0; i < len; i++)
    {
      temp[i] = key[i] + 1;
    }

    return temp;
}

  struct trie *
trie_new(void)
{
  struct trie *temp = NULL;

  temp = (struct trie*)malloc(sizeof(struct trie));

  if(temp)
  {
    int i;
    temp->isEnd = false;
    for (i = 0; i < SIZE; i++)
        temp->children[i] = NULL;
  }
  return temp;
}

  bool
trie_set(struct trie * trie, u32 len, u8 * key)
{
  struct trie *temp = trie;


  *key = encode(len,key);

  for(int level=0; level < len; level++)
  {
    if(!temp->children[key[level]])
      temp->children[key[level]] = trie_new();

    temp = temp->children[key[level]];
  }

  temp->isEnd = true;

  return true;
}

  bool
trie_get(struct trie * trie, u32 len, u8 * key)
{
  struct trie *temp = trie;

  *key = encode(len,key);

  for(int level =0; level < len; level++)
  {
    if (!temp->children[key[level]])
      return false;

    temp = temp->children[key[level]];
  }

  return (temp->isEnd);
}

  bool
trie_del(struct trie * trie, u32 len, u8 * key)
{
  struct trie *temp = trie;

  *key = encode(len,key);

  for(int level = 0; level < len; level++)
  {
    temp = temp->children[key[level]];
  }

  temp->isEnd = false;

  return true;
}
