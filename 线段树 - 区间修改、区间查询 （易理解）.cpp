
const int maxn = 1e5+10;
int arr[maxn];
int tree[maxn*20];
void build_tree(int arr[], int tree[], int node, int start, int _end){
    if (start == _end){
        tree[node] = arr[start];
    }
    else{
        int mid = (start+_end) >> 1;
        int left_node  =  node*2 + 1;
        int right_node =  node*2 + 2;
        build_tree(arr, tree, left_node, start, mid);
        build_tree(arr, tree, right_node, mid+1, _end);
        tree[node] = tree[left_node]+tree[right_node];
    }
}
void update(int arr[], int tree[], int node, int start, int _end, int index, int value){
    //arr[index] = value;
    if (start == _end){
        arr[index] = value;
        tree[node] = value;
        return ;
    }
    else{
        int mid = (start+_end) >> 1;
        int left_node  = node*2 + 1;
        int right_node = node*2 + 2;
        if (index >= start && index <= mid){
            update(arr, tree, left_node, start, mid, index, value);
        }
        else {
            update(arr, tree, right_node, mid+1, _end, index, value);
        }
        tree[node] = tree[left_node] + tree[right_node];
    }
}
int query(int arr[], int tree[], int node, int start, int _end, int L, int R){
    if (R < start || L > _end) return 0;
    else if (start == _end) return tree[node];
    else {
        int mid = (start + _end) >> 1;
        int left_node  = node*2 + 1;
        int right_node = node*2 + 2;
        int sum_left  = query(arr, tree, left_node, start, mid, L, R);
        int sum_right = query(arr, tree, right_node, mid+1, _end, L, R);
        return sum_left+sum_right;
    }

}
int main(){
    int n, m; RD(n, m);
    FOR_1(i, 0, n - 1) RD(arr[i]);
    build_tree(arr, tree, 0, 0, n-1);
    FOR_1(i, 0, m - 1) {
        int x; RD(x);
        if (x == 1){
            int l, r, k; RD(l, r, k);
            FOR_1(j, l-1, r-1) update(arr, tree, 0, 0, n-1, j, arr[j]+k);
        }
        else if (x == 2){
            int l, r; RD(l, r);
            cout << query(arr, tree, 0, 0, n-1, l-1, r-1) << '\n';
        }
    }
}
