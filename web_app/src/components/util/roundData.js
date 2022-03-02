function roundWithPrecision (n, precision) {
    const precisionWithPow10 = Math.pow(10, precision);
    return Math.round(n * precisionWithPow10) / precisionWithPow10;
}
export {roundWithPrecision}