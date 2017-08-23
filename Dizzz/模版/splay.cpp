#include<bits/stdc++.h>
using namespace std;
#define key_value tree[tree[root].ch[1]].ch[0]
// 定义了一个宏，代表根节点的右儿子的左儿子，我们在进行操作时都会尽量把数据集中在这个地方
const int maxn = 500010;                    // 数据规模
const int INF = (1 << 29);                  // 定义了一个极大值
struct Node{
    int ch[2];                              // 左右儿子
    int pre, val, size;                     // 父节点，当前节点的值，当前节点为根的子树的大小
    long long sum;                          // 当前节点为根的子树的和
    int rev, add, same;                     // 反转标记, 增量延迟标记， 区间所有元素相同标记
    int lx, rx, mx;                         // 从区间最左端开始的子序列最大和，从区间最右端开始的区间子序列最大和，整个区间里面子序列最大和
};
int root, total;                            // 根节点，节点数量
stack <int> mPool;                          // 内存池，用来存储删除节点时释放的节点, 以便之后使用
Node tree[maxn];                            // 树的所有节点
int n, q;                                   // n 个数， q 个询问
int data[maxn];                             // 原始数据
// 更新增量延迟标记
void updateAdd(int rt, int add){
    if(!rt) return;
    tree[rt].add += add;
    tree[rt].val += add;
    tree[rt].sum += (long long)add * tree[rt].size;
}
// 更新反转延迟标记
void updateRev(int rt){
    if(!rt) return;
    tree[rt].rev ^= 1;
    swap(tree[rt].lx, tree[rt].rx);
    swap(tree[rt].ch[0], tree[rt].ch[1]);
}
// 更新区间元素值相同延迟标记
void updateSame(int rt, int val){
    if(!rt) return;
    tree[rt].val = val;
    tree[rt].sum = val * tree[rt].size;
    tree[rt].lx = tree[rt].rx = tree[rt].mx = max(val, val * tree[rt].size);
    tree[rt].same = 1;
}
// 通过孩子节点的数据来更新父节点的数据
void pushUp(int rt){
    int lson = tree[rt].ch[0], rson = tree[rt].ch[1];
    // 更新节点的大小
    tree[rt].size = tree[lson].size + tree[rson].size + 1;
    // 更新该节点及其子树所有值的和
    tree[rt].sum = tree[lson].sum + tree[rson].sum + tree[rt].val;
    // 更新子序列最大值
    tree[rt].lx = max((long long)tree[lson].lx, tree[lson].sum + tree[rt].val + max(0, tree[rson].lx));
    tree[rt].rx = max((long long)tree[rson].rx, tree[rson].sum + tree[rt].val + max(0, tree[lson].rx));
    tree[rt].mx = max(0, tree[lson].rx) + tree[rt].val + max(0, tree[rson].lx);
    tree[rt].mx = max(tree[rt].mx, max(tree[lson].mx, tree[rson].mx));
}
// 将父节点的延迟标记更新到孩子节点
void pushDown(int rt){
    // 更新增量延迟标记
    if(tree[rt].add){
        updateAdd(tree[rt].ch[0], tree[rt].add);
        updateAdd(tree[rt].ch[1], tree[rt].add);
        tree[rt].add = 0;
    }
    // 更新区间相同标记
    if(tree[rt].same){
        updateSame(tree[rt].ch[0], tree[rt].val);
        updateSame(tree[rt].ch[1], tree[rt].val);
        tree[rt].same = 0;
    }
    // 更新反转标记
    if(tree[rt].rev){
        updateRev(tree[rt].ch[0]);
        updateRev(tree[rt].ch[1]);
        tree[rt].rev = 0;
    }
}
void newNode(int &rt, int pre, int val){
    if(!mPool.empty()){
        rt = mPool.top();
        mPool.pop();
    }else{
        rt = ++total;
    }
    tree[rt].pre = pre;
    tree[rt].size = 1;
    tree[rt].val = val;
    tree[rt].add = 0;
    tree[rt].sum = val;
    tree[rt].rev = tree[rt].same = 0;
    tree[rt].ch[0] = tree[rt].ch[1] = 0;
    tree[rt].lx = tree[rt].rx = tree[rt].mx = val;
}
void buildTree(int &cur, int l, int r, int pre, int *a){
    if(l > r) return;
    int mid = (l + r) >> 1;
    newNode(cur, pre, a[mid]);
    buildTree(tree[cur].ch[0], l, mid - 1, cur, a);
    buildTree(tree[cur].ch[1], mid + 1, r, cur, a);
    pushUp(cur);
}
void init(int *data){
    root = total = 0;
    while(!mPool.empty()) mPool.pop();
    tree[root].rev = tree[root].same = 0;
    tree[root].ch[0] = tree[root].ch[1] = 0;
    tree[root].lx = tree[root].rx = tree[root].mx = -INF;
    tree[root].sum = tree[root].add = tree[root].val = 0;
    tree[root].pre = tree[root].size = tree[root].sum = 0;
    newNode(root, 0, -1);                           // 注1
    newNode(tree[root].ch[1], root, -1);            // 注2
    buildTree(key_value, 0, n - 1, tree[root].ch[1], data);
    pushUp(tree[root].ch[1]);
    pushUp(root);
}
// 实现单旋
// com == 0 时， 对 cur 节点进行左旋
// com == 1 时， 对 cur 节点进行右旋
void rotate(int cur, int com){
    int pre = tree[cur].pre;
    pushDown(pre);
    pushDown(cur);
    tree[pre].ch[!com] = tree[cur].ch[com];
    tree[tree[cur].ch[com]].pre = pre;
    /* 上面的语句可以展开成下面的语句
    if(com){
        tree[pre].ch[0] = tree[cur].ch[1];    
        tree[tree[cur].ch[1]].pre = pre;
    }else{
        tree[pre].ch[1] = tree[cur].ch[0];   
        tree[tree[cur].ch[0]].pre = pre;
    }
    */
    if(tree[pre].pre){
        tree[tree[pre].pre].ch[tree[tree[pre].pre].ch[1] == pre] = cur;
    }
    tree[cur].pre = tree[pre].pre;
    tree[cur].ch[com] = pre;
    tree[pre].pre = cur;
    pushUp(pre);
}
// 实现树的调整
// 将 rt 节点调整到 tar 下面
void splay(int rt, int tar){
    pushDown(rt);
    while(tree[rt].pre != tar){
        if(tree[tree[rt].pre].pre == tar){
            pushDown(tree[rt].pre);
            pushDown(rt);
            rotate(rt, tree[tree[rt].pre].ch[0] == rt);
        }else{
            pushDown(tree[tree[rt].pre].pre);
            pushDown(tree[rt].pre);
            pushDown(rt);
            int pre = tree[rt].pre;
            int com = tree[tree[pre].pre].ch[0] == pre;
            if(tree[pre].ch[com] == rt){
                rotate(rt, !com);
                rotate(rt, com);
            }else{
                rotate(pre, com);
                rotate(rt, com);
            }
        }
    }
    pushUp(rt);
    if(tar == 0) root = rt;
}
int getKth(int rt, int k){
    pushDown(rt);
    int tmp = tree[tree[rt].ch[0]].size + 1;
    if(tmp == k) return rt;
    else if(tmp > k) return getKth(tree[rt].ch[0], k);
    else return getKth(tree[rt].ch[1], k - tmp);
}
int getValMinPos(int rt, int val){
    int Min = INF;
    int pos = -1;
    while(rt){
        pushDown(rt);
        if(tree[rt].val == val) return rt;
        if(tree[rt].val > val){
            if(Min > tree[rt].val){
                Min = tree[rt].val;
                pos = rt;
            }
            rt = tree[rt].ch[0];
        }
        else rt = tree[rt].ch[1];
    }
    return pos;
}
// 得到 val 的位置
int getValPos(int rt, int val){
    if(!rt) return -1;
    if(tree[rt].val == val) return rt;
    else if(tree[rt].val > val)
        return getValPos(tree[rt].ch[0], val);
    else
        return getValPos(tree[rt].ch[1], val);
}
int getValRank(int rt, int val){
    int pos = getValPos(root, val);
    splay(pos, 0);
    int res = 0;
    if(tree[root].ch[0]) res += tree[tree[root].ch[0]].size;
    res += 1;
    return res;
}
int getMin(int rt){
    pushDown(rt);
    while(tree[rt].ch[0]){
        rt = tree[rt].ch[0];
        pushDown(rt);
    }
    return rt;
}
int getMax(int rt){
    pushDown(rt);
    while(tree[rt].ch[1]){
        rt = tree[rt].ch[1];
        pushDown(rt);
    }
    return rt;
}
// 在第 x 个数后面插入 val
void insertOne(int x, int val){
    splay(getKth(root, x + 1), 0);
    splay(getKth(root, x + 2), root);
    newNode(key_value, tree[root].ch[1], val);
    pushUp(tree[root].ch[1]);
    pushUp(root);
}
// 回收内存
void erase(int rt){
    if(rt){
        mPool.push(rt);
        erase(tree[rt].ch[0]);
        erase(tree[rt].ch[1]);   
    }
}
// 删除第 k 个数
void deleteOne(int k){
    splay(getKth(root, k), 0);
    splay(getKth(root, k + 2), root);
    erase(key_value);
    tree[key_value].pre = 0;
    key_value = 0;
    pushUp(tree[root].ch[1]);
    pushUp(root);
}
// 从第 pos 个数后开始插入 val 数组中的数
void insert(int pos, int cnt, int *val){
    splay(getKth(root, pos + 1), 0);
    splay(getKth(root, pos + 2), root);
    buildTree(key_value, 0, cnt - 1, tree[root].ch[1], val);
    pushUp(tree[root].ch[1]);
    pushUp(root);
}
// 从 pos 个数开始连续删除 cnt 个数
void Delete(int pos, int cnt){
    splay(getKth(root, pos), 0);
    splay(getKth(root, pos + cnt + 1), root);
    erase(key_value);
    tree[key_value].pre = 0;
    key_value = 0;
    pushUp(tree[root].ch[1]);
    pushUp(root);
}
// 获取 [l, r] 的和
int getSum(int l, int r){
    splay(getKth(root, l), 0);
    splay(getKth(root, r + 2), root);
    return tree[key_value].sum;
}
// 将 [l, r] 区间循环右移 T 个单位
void revolve(int l, int r, int T){
    int len = r - l + 1;
    T = (T % len + len) % len;
    if(T == 0) return;
    int c = r - T + 1;
    splay(getKth(root, c), 0);
    splay(getKth(root, r + 2), root);
    int tmp = key_value;
    key_value = 0;
    pushUp(tree[root].ch[1]);
    pushUp(root);
    splay(getKth(root, l), 0);
    splay(getKth(root, l + 1), root);
    key_value = tmp;
    tree[key_value].pre = tree[root].ch[1];
    pushUp(tree[root].ch[1]);
    pushUp(root);
}
void reverse(int l, int r){
    splay(getKth(root, l), 0);
    splay(getKth(root, r + 2), root);
    updateRev(key_value);
    pushUp(tree[root].ch[1]);
    pushUp(root);
}
void makeSame(int pos, int cnt, int val){
    splay(getKth(root, pos), 0);
    splay(getKth(root, pos + cnt + 1), root);
    updateSame(key_value, val);
    pushUp(tree[root].ch[1]);
    pushUp(root);
}
// 将 [l, r] 区间的所有值都增加 val
void makeAdd(int l, int r, int val){
    splay(getKth(root, l), 0);
    splay(getKth(root, r + 2), root);
    updateAdd(key_value, val);
    pushUp(tree[root].ch[1]);
    pushUp(root);
}
// 从 pos 开始连续 cnt 长度的区间内子序列的最大和
int getMaxSum(int pos, int cnt){
    splay(getKth(root, pos), 0);
    splay(getKth(root, pos + cnt + 1), root);
    return tree[key_value].mx;
}
int main(){
    int x, y, z;
    char op[20];
    while(scanf("%d%d", &n, &q) != EOF){
        for(int i = 0; i < n; i++){
            scanf("%d", &data[i]);
        }
        init(data);
        while(q--){
            scanf("%s", op);
            if(op[0] == 'I'){
                scanf("%d%d", &x, &y);
                for(int i = 0; i < y; i++)
                    scanf("%d", &data[i]);
                insert(x, y, data);
            }else if(op[0] == 'D'){
                scanf("%d%d", &x, &y);
                Delete(x, y);
            }else if(op[0] == 'M' && op[2] == 'K'){
                scanf("%d%d%d", &x, &y, &z);
                makeSame(x, y, z);
            }else if(op[0] == 'R'){
                scanf("%d%d", &x, &y);
                reverse(x, x + y - 1);
            }else if(op[0] == 'G'){
                scanf("%d%d", &x, &y);
                printf("%d\n", getSum(x, x + y - 1));
            }else{
                printf("%d\n", getMaxSum(1, tree[root].size - 2));
            }
        }
    }
    return 0;
}