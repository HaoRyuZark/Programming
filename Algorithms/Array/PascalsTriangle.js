/**
 * @param {number} numRows
 * @return {number[][]}
 */
var generate = function(numRows) {
    

    let res = new Array(numRows);
    res[0] = [1];

    for (let i = 1; i < numRows; i++) {
        let row = new Array(i + 1);
        row[0] = 1;

        for (let j = 1; j < i; j++) {
            row[j] = res[i - 1][j - 1] + res[i - 1][j];
        }
        row[i] = 1;
        res[i] = row;
    }

    return res;
};
