/**
 * Remove all falsy values from an object, including the nested ones.
 */
let _removeFalsy = (val) => {

    if (val === null || typeof val !== 'object') {
        return Boolean(val) ? val : undefined;
    }
    
    const res = Array.isArray(val) ? [] : {};

    for (const [_key, _val] of Object.entries(val)) {
        const cleaned = _removeFalsy(_key, _val, res);

        if (cleaned !== undefined) {
            if (Array.isArray(res)) {
                res.push(cleaned);
            } else {
                res[_key] = cleaned;
            }
        }
    }

    return res;
};

let compactObject = function(obj) {
    const res = Array.isArray(obj) ? [] : {};

    for (const [key, val] of Object.entries(obj)) {
        const cleaned = _removeFalsy(val);

        if (cleaned !== undefined) {
            if (Array.isArray(res)) {
                res.push(cleaned);
            } else {
                res[key] = cleaned;
            }
        }
    }

    return res;
};
