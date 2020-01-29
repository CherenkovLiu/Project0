package Project0.Extend;

public class EArray {
    public static int[] rangeTo(int until) {
        int[] result = new int[until];
        for(int i = 0; i < until; ++i)
            result[i] = i + 1;
        return result;
    }
}