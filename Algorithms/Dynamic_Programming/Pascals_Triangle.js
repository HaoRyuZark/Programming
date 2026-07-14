/**
 * @param {number} rowIndex
 * @return {number[]}
 */
var getRow = function(rowIndex) {
    let res = Array.from({length: rowIndex + 1}, (_, k) => 1);

    for (let i = 1; i < rowIndex; i++) {

        res[1] = i + 1;

        for (let j = 2; j <= rowIndex - i; j++) {
            res[j] = res[j] + res[j - 1];    
        }
    }
    
    return res;
};

/*
    Intuition:

    We use a imagine the following table to trak how the values changes of our one's array with reach iteration by always iterating until 
    the end:
    
    rowIndex  = 4

    i   0   1   2   3   4   5

    0   1   1   1   1   1   1
    1   1   2   3   4   5   1
    2   1   3   6   10  15  1
    3   1   4   10  20  35  1
    4   1    
    5   1           ...

    The first and lax index never change and we always can leave the element rowIndex -i + 1 intact since the anti diagonal returns 
    the row of the element

    i   0 | 1   2   3   4
          |
    0   1 | 1   1   1   1|  
    1   1 | 2   3   4|
    2   1 | 3   6|
    3   1 | 4|
    4   1 |  
*/
