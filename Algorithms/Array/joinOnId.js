/**
 * Given two arrays arr1 and arr2, return a new array joinedArray. All the objects in each of the two inputs arrays will contain an id field that has an integer value. 
 * joinedArray is an array formed by merging arr1 and arr2 based on their id key. The length of joinedArray should be the length of unique values of id. The returned array should be 
 * sorted in ascending order based on the id key.
 *
 * If a given id exists in one array but not the other, the single object with that id should be included in the result array without modification.
 * If two objects share an id, their properties should be merged into a single object:
 * If a key only exists in one object, that single key-value pair should be included in the object.
 * If a key is included in both objects, the value in the object from arr2 should override the value from arr1.
 *
 * @param {Array} arr1
 * @param {Array} arr2
 * @return {Array}
 */
var join = function(arr1, arr2) {
    
    const l1 = arr1.length;
    const l2 = arr2.length;

    let arr1Ids = Array.from(arr1.sort((x, y) => x["id"] - y["id"]), x => x["id"]);
    let arr2Ids = Array.from(arr2.sort((x, y) => x["id"] - y["id"]), x => x["id"]);

    let res = [];
    let i = 0;
    let j = 0;
    
    while (i < l1 && j < l2) {

        if (arr1Ids[i] < arr2Ids[j]) {

            res.push(arr1[i]);
            i++;

        } else if (arr1Ids[i] >arr2Ids[j]) {

            res.push(arr2[j]);
            j++;

        } else {
            
            obj = arr1[i];

            for (const [key, value] of Object.entries(arr2[j])) {
                obj[key] = value;
            }

            res.push(obj);
            i++;
            j++;
        }
    }

    while (i < l1) {
        res.push(arr1[i]);
        i++; 
    }

    while (j < l2) {
        res.push(arr2[j]);
        j++; 
    }

    return res;

};

// Not the most efficient, but it works.
