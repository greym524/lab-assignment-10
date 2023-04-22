#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TrieNode
{
    int count;
    char letter;
    struct TrieNode* children[26]; //an array of 26 TrieNode pointers
};

void insert(struct TrieNode **ppTrie, char *word)
{
    int length = strlen(word);
    struct TrieNode *temp = NULL;
    char ch;

    struct TrieNode *root = *ppTrie;

    for(int i = 0; i < length; i++)
    {
        ch = word[i];
        int index = (int)ch - 'a';
        
        if(root->children[index] == NULL)
        {
            temp = (struct TrieNode*)malloc(sizeof(struct TrieNode));
            for(int x = 0; x < 26; x++)
            {
                temp->children[x] = NULL;
            }
            temp->letter = ch;
            temp->count = 0;
            root->children[index] = temp;

        }
        root->children[index]->count++;
        root = root->children[index];
    }


}

int numberOfOccurances(struct TrieNode *pTrie, char *word)
{
    int numOccur = 0;
    int length = strlen(word);
    struct TrieNode *temp = pTrie;
    int i = 0, index;
    
    while(i < length)
    {
        char ch = word[i];
        index = ch - 'a';
        temp = temp->children[index];
        i++;
    }
    
    numOccur = temp->count;

    return numOccur;
}

struct TrieNode *deallocateTrie(struct TrieNode *pTrie)
{
    if(pTrie == NULL)
    {
      return pTrie;
    }

    for(int i = 0; i < 26; i++)
    {
      pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
  free(pTrie);
  pTrie = NULL;
  return pTrie;
}

int main(void)
{
    struct TrieNode *trie = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    for(int x = 0; x < 26; x++)
    {
        trie->children[x] = NULL;
    }
    //read the number of the words in the dictionary
    //parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};


    for(int i = 0; i < 5; i++)
    {
        insert(&trie, pWords[i]);
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie,pWords[i]));
    }
    trie = deallocateTrie(trie);
    if(trie != NULL)
    {
        printf("There is an error in this program\n");
    }
    return 0;
}
