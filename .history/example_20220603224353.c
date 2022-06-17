int clostVal(int arr[],
             int N,
             int K)
{
    // Stores the closest
    // value to K
    int res = arr[0];
 
    // Traverse the array
    for (int i = 1; i < N;
         i++) {
 
        // If absolute difference
        // of K and res exceeds
        // absolute difference of K
        // and current element
        if (abs(K - res) > abs(K - arr[i])) {
            res = arr[i];
        }
    }
 
    // Return the closest
    // array element
    return res;
}
 
// Driver Code
int main()
{
    int arr[] = { 100, 200, 400 };
    int K = 300;
    int N = sizeof(arr) / sizeof(arr[0]);
 
    cout << clostVal(arr, N, K);
}