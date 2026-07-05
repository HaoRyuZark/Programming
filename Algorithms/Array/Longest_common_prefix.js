let longestCommonPrefix = function(strs) {
    
    let lcp = strs[0];
    let l = lcp.length;

    for (let i = 1; i < strs.length; i++) {
        
        let s = strs[i];

        while (lcp !== s.substring(0, l)) {
            l--;
            if (l == 0) {
                return "";
            }
            lcp = lcp.substring(0, l);
        }
    }    

    return lcp;
};
