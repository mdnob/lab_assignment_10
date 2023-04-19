#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie{
    int isWord;
    struct Trie * next[26];
};

void insert (struct Trie **ppTrie, char *word);
int numberOfOccurances (struct Trie *pTrie, char *word);
struct Trie * deallocateTrie (struct Trie *pTrie);

int main () {
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    // trie initialize
    struct Trie * trie = malloc(sizeof(struct Trie));
    trie->isWord = 0;

    // insert
    for (int i = 0; i < sizeof(pWords) / sizeof(pWords[0]); i++) {
        for(int j = 0; j < i + 1; j++) {
            insert(&trie, pWords[i]);
        }
    }

    // print
    for (int i=0;i<5;i++) {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    // deallocate
    //struct * Trie trie = deallocateTree(&trie);
    trie = deallocateTrie(trie);

    if (trie != NULL){
       printf("There is an error in this program\n");
    }

    return 0;
}

void insert (struct Trie **ppTrie, char *word) {

    struct Trie * tree = *ppTrie;

    for(int i = 0; i < strlen(word); i++) {
        if (tree->next[word[i] - 'a'] == NULL){
            tree->next[word[i] - 'a'] = (struct Trie *) malloc(sizeof(struct Trie));
            tree->next[word[i] - 'a']->isWord = 0;
        }

        tree = tree->next[word[i] - 'a'];

        if (i == strlen(word) - 1){
            tree->isWord++;
        }
        
        //printf("%i, %i\n", word[i] - 'a', tree->isWord);
    }

}

int numberOfOccurances (struct Trie *pTrie, char *word) {
    struct Trie * tree = pTrie;

    for (int i = 0; i < strlen(word); i++) {
        if (tree == NULL) {
            return 0;
        }
        tree = tree->next[word[i] - 'a'];
        if(i == strlen(word) - 1) {
            return tree->isWord;
        }
    }

    return 0;

}

struct Trie * deallocateTrie (struct Trie *pTrie){
    struct Trie * next = NULL;
    struct Trie * prev = pTrie;

    for(int i = 0; i < 26; i++) {
        if (prev->next[i] != NULL) {
            next = prev->next[i];
            deallocateTrie(next);
            printf("deallocate %c\n", (char)('a' + i));
        }
    }

    free(prev);
    prev = NULL;
    return prev;
}