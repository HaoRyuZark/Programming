#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int  max(int a, int b);
void naive_approach(char* text, char* pattern, int n, int m);
void longest_prefix_suffix_table(char* pattern, int m, int* table);
void knuth_morris_pratt(char* text, char* pattern, int n, int m);
void compute_bad_character_shift(char* pattern, int m, int* alphabet);
void compute_good_suffix_shift(char* pattern, int m, int* shift);
void boyer_moore(char* text, char* pattern, int n, int m);

int main() {

    char* text = "Hello, Hola, World";
    char* pattern = "Hello";
    
    int n = strlen(text);
    int m = strlen(pattern);

    naive_approach(text, pattern, n, m);
    knuth_morris_pratt(text, pattern, n, m);

    return 0;
}


void naive_approach(char* text, char* pattern, int n, int m) {

    for (int i = 0; i <= n - m; i++) {
        
        int j;

        for (j = 0; j < m; j++) {

            if (text[i + j] != pattern[j]) {
                break;
            }
        
        }

        if (j == m) {
            printf("Found at index %d\n", i);
        }
    }
}

/* 
 * We want to know the length of the longest prefix that also happens to be a suffix. Also the prefix can not 
 * be the entire string 
 * */
void longest_prefix_suffix_table(char* pattern, int m, int* table) {
 
    int i = 1;      // starting by 1 because the start of the pattern has no prefix
    int j = 0;      //counter for the next letter 

    while (i < m) { // iterate over the entire pattern
       
        if (pattern[i] == pattern[j]) { // same letter found at both ends
            
            /*
             * This lines work in the following manner: 
             * we are checking if the character match and if the previous have already
             * matched then they accumulate : table[i] = j because j is already telling us the number
             * of matching characters. Of course, this is the most optimal way of doing it. But a double pointer 
             * approach would also work
             */

            j++;            // move to the next letter / increment length of the proper prefix suffix
            table[i] = j;   // store the length of the suffix/prefix
            i++;            // move to the next letter
        
        } else {                   // if no match
            
            if (j != 0) {         // if not at the start 
                j = table[j - 1];   // set j = to length of the lps of the part that mached ,which is the part at [j -1] 
                                
            } else {              // if j at the start
                table[i] = 0;       // no prefix/suffix -> 0
                i++;                // go to next latter
            }
        }       
    }
}

/*  
*  Demostration 
*
* Start
* 0   1
*  j   i
*  A   A   A   A   B   A
*  
*  0   0   0   0   0   0
*
* Match
*       1
*      ji
*  A   A   A   A   B   A
*  
*  0   1   0   0   0   0
*
* Match
*           2
*          ji
*  A   A   A   A   B   A
*  
*  0   1   2   0   0   0
*
* Match
*
*               3
*              ji
*  A   A   A   A   B   A
*  
*  0   1   2   3   0   0
*
*
* Mismatch -> j = table[ j - 1] = 
*                   4
*                  ji
*  A   A   A   A   B   A
*  
*  0   1   2   3   0   0    
*

* Mismatch -> j = table[j - 1]
*                  4
*          j       i
*  A   A   A   A   B   A
*  
*  0   1   2   3   0   0
*
* After some other mismatches
*
*
* Mismatch  j == 0: -> i++
*                      5
*  j                   i
*  A   A   A   A   B   A
*  
*  0   1   2   3   0   0
*
* Match 
*      1               5
*      j               i
*  A   A   A   A   B   A
*  
*  0   1   2   3   0   1
*
*
* */

/*
 * This algorithm works by shifting the pattern if a mismatch occurrs to the 
 * index of the last matching portion before the missmatch so that the mismatch in the 
 * pattern becomes a match
 * /*/
void knuth_morris_pratt(char* text, char* pattern, int n, int m) {
    
    int* lps = (int*)calloc(m, sizeof(int));

    longest_prefix_suffix_table(pattern, m, lps); // populate table
    
    int j = 0; //ptr for the pattern
    int i = 0; //ptr for the text

    while (i < n) {

        if (text[i] == pattern[j]) { // matching success
            i++;
            j++;
        }    
        
        if (j == m) { // Found!
            j = lps[j - 1]; // update j for skiping the already checked section and continue
            printf("Found at %d \n", i - m);
        
        } else if (i < n && text[i] != pattern[j]) {

            if (j != 0) {    
                j = lps[j - 1]; 
            } else {
                i++; //match next
            }
        }    
    }

    free(lps);
}


int max(int a, int b) {
    if (a < b) {
        return b;
    }

    return a;
}

/*
 * Bad Character Rule
 *
 * Idea: How far do we skip until the mismatched character becomes a match?
 *
 * When encoutering a mismatch, we are going to shift our pattern until:
 *
 *  -> the mismatch becomes a match -> shift to the last occurence
 *  -> or the pattern passes the bad character -> skip all previous character and go to the next
 */

void compute_bad_character_shift(char* pattern, int m, int* alphabet) {
    
    int i;

    for (i = 0; i < 256; ++i) {
        alphabet[i] = -1;
    }
    
    for (i = 0; i < m; ++i) {
        alphabet[(unsigned char)pattern[i]] = i;  // last occurrance of the character
    }
}

/*
 * 
 * Good Suffix Rule
 *
 * Idea: If a mismatch happens at position j of the pattern, and a suffix P[j+1 ... m-1] (end to j + 1)
 * matched with the text, the Good Suffix Rule looks for
 *
 *  -> Another occurence of the suffix in the patter, so we can shift the pattern to aling with that
 *  -> If no such occurence, it looks for a prefix of the pattern that matchers a suffix for the matched part
 *  -> If neither the entire pattern is a mismatch
 *
 * Other Points
 * - Goal of the first part is about finding the border: prefix that is also a suffix not at the start just anywhere
 * - The shift array tell us where to go when a missmatch a some position happens -> go to shift[j]
 * - Note that a border also can have inner borders
 * */
void compute_good_suffix_shift(char* pattern, int m, int* shift) {
    
    int* borders = (int*)calloc(m + 1, sizeof(int));
    
    int i = m;          // end of the pattern 
    int j = m + 1;      // one past the end -> used as the beginning position of the righborder during the process
    
    // Each i has a correspondance to a j which represent:
    // The start of prefix that is also a suffix of the pattern from some position i - 1 matches with a character with the 
    // start of the suffix at position j - 1. Thus borders[i] gives us the start of the right border from the left.

    borders[i] = j; // initial setup with no valid border 
    
    // Cases Covered in the first loops: prefix fully found inside and is not prefix of the full pattern 
    //Moving left in the pattern
    while (i > 0) {
        
        // Loop for the mismismatch
        while (j <= m && pattern[i-1] != pattern[j-1]) { // if mismatch -> find the previous border
                                                         
            // We are interested in the right border of the right border of [i]    
            // the right border[i] = j therefore we get the value of border[j] = x then update  j = x
            // which is the index of right border of the rightboder and we repeat until we reach equality again or we dont have more borders
    
            
            if (j - 1 >= 0 && shift[j - 1] == 0) {   // if the next position is valid and the shift has not been updated:   
                shift[j - 1] = j - i;                // we want our character at position i-1 to aling with the character at position
                                                     // t+j-1 which is shifting by j - i 
            }
            
            j = borders[j];   // border[i] is j, but here we get border[j] which is the value at the end of the right
                              // which is the beginning of a previous border
        }
        
        // We want compare pattern[i - 1] with the character on the left of the right
        // boder this is pattern[j - 1] which is the beginning position of the inner right boder
        // This is the simple case where we have matches. Thus, we just store each of the borders 
        --j;
        --i;
        borders[i] = j; // updates the border
    }

    // Cases Covered: prefix and suffix at both ends and suffix of suffix is prefix

    int b = borders[0]; // remember that i is maybe the index of a end of some left border, and j the end but for the rightboder
                        // border. This is telling us: give me the end of the right border that is also the end of the left border 
                        // -> give me the starting indexes (from the left) of the prefix that is also a suffix

    for (i = 0; i <= m; ++i) {

        if (i == b) {  // at same index as the left of the right border
            b = borders[b]; // update with the value of the border of the border -> because the rightboder also has a border
        }
        
        if (shift[i] == 0) { // if no border was found before -> Update with the value for a full shift from suffix to prefix
            shift[i] = b;
        }
    }

    free(borders);
}

void boyer_moore(char* text, char* pattern, int n, int m) {

    int i = 0;
    int* bad_character_shift = (int*)calloc(256, sizeof(int)); // only lower case ascii for simplicity
    int* good_suffix_shift = (int*)calloc(m + 1, sizeof(int));

    compute_bad_character_shift(pattern, m, bad_character_shift); // store last occurence of each character in the pattern
    compute_good_suffix_shift(pattern, m, good_suffix_shift);

    while (i <= n - m) { // iterate over the string
        
        int j = m - 1;   // set j to start at the end of the pattern

        while (j >= 0 && pattern[j] == text[i + j]) {  //matching pattern from right to left
            j--;
        }

        if (j == -1) {  //found!
            
            printf("Found at %d\n", i);
            i += good_suffix_shift[0];

        } else {
            
            char character = text[i + j]; //faulty character
            
            int last_occurence = (bad_character_shift[(int)character] != -1)? bad_character_shift[(int)character] : -1; // get last occurrance

            i = i + max(j - last_occurence, good_suffix_shift[j]); //deciding between bad character and good suffix
                                                                         // we use max here because we allways want to skip as much useless 
                                                                         // alingments
        }
    }

    free(bad_character_shift);
    free(good_suffix_shift);
}



