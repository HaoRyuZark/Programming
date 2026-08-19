
/**
 * Memoization based on JavaScript equality reles without trie or weird stuff.
 */



const ID_cache = new Map(); 
let currentId = 0;

// Creates a unique ID
function unique_ID(obj) {

    if (!ID_cache.has(obj)) { ID_cache.set(obj, currentId++); }

    return ID_cache.get(obj);
}

function memoize(fn) {

    let d = {}; // memo

    return function(...args) {

        // Getting the key which consist of a sequence of IDS for each argument
        let key = args.map((arg) => unique_ID(arg)).join();

        if (!(key in d)) { d[key] = fn(...args); }

        return d[key]
    }
}