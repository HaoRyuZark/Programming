/**
 * @param {number[]} nums1
 * @param {number} m
 * @param {number[]} nums2
 * @param {number} n
 * @return {void} Do not return anything, modify nums1 in-place instead.
 */
var merge = function(nums1, m, nums2, n) {

    if (m === 0 && n === 1) {
        nums1[0] = nums2[0];
        return;
    }
    
    let k = m + n - 1;
    let i = m - 1;
    let j = n - 1;

    while (j >= 0) {

        if (nums2[j] > nums1[i]) {
            nums1[k--] = nums2[j--];
        }
        else if (nums2[j] < nums1[i]) {
            nums1[k--] = nums1[i--];
        }
        else {
            nums1[k--] = nums2[j--];
        }
    }
};
