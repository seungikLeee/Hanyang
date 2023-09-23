package Week12;

public class BinarySearch {
    public static int binarySearch(int[] arr, int start, int end, int target){
        if(start<=end) {
            int middle = (start + end) / 2;
            if (arr[middle] == target) {
                return middle;
            }

            if (arr[middle] > target) {
                return binarySearch(arr, start, middle - 1, target);
            }
            if (arr[middle] < target) {
                return binarySearch(arr, middle + 1, end, target);
            }
        }
        return -1;
    }
}
