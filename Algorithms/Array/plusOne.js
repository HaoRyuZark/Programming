var plusOne = function(digits) {

    let carry = 1;

    for (let i = digits.length - 1; i >= 0; i--) {
        
        digits[i] += carry;

       if (digits[i] == 10) {
        digits[i] = 0;
        carry = 1
       } else {
        carry = 0;
        break;
       }
    } 
    return carry === 1? [1, ...digits]: digits;
};
