var sumAndMultiply = function(n) {
    let x = 0;
    let i = 0;
    let sum = 0;

    while (n !== 0) {
        let m = n % 10;

        if (m !== 0) {
            x += m * (10 ** i);
            i++;
        }

        sum += m;
        n = Math.floor(n / 10);
    }

    return sum * x;
};