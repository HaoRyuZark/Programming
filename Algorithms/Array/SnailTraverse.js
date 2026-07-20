/**
 * @param {number} rowsCount
 * @param {number} colsCount
 * @return {Array<Array<number>>}
 */
Array.prototype.snail = function(rowsCount, colsCount) {

    if (rowsCount * colsCount != this.length) return [];

    let i = 0;
    let j = 0;

    let res = Array.from({length: rowsCount}, (_, i) => Array.from({length: colsCount}, (_, j) => 0));
    
    for (let k = 0; k < this.length; k++) {
        
        if (j % 2 === 0) res[i++][j] = this[k]; 
        if (j % 2 !== 0) res[i--][j] = this[k]; 
        
        if (i === rowsCount) { 
            i = rowsCount - 1;
            j++;
        }

        if (i === -1) {
            i = 0;
            j++;
        } 
    }
    
    return res;
}

/**
 * const arr = [1,2,3,4];
 * arr.snail(1,4); // [[1,2,3,4]]
 */
