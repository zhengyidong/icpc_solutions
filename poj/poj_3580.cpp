#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

const int MAX_N = 2005;
const int INF = (1 << 30);

using namespace std;

class splay_tree{
public:
    splay_tree(){
        _nil = &_nil_node;
        _nil_node.key = 0;
        _nil_node.size = 0;
        _nil_node.value = INF;
        _nil_node.min = INF;
        _nil_node.parent = _nil;
        _nil_node.children[LEFT] = _nil;
        _nil_node.children[RIGHT] = _nil;
//        clear();
    }
    void build(int elements[], int num){
        _num_nodes = 0;
        int mid = (num - 1) >> 1;
        _root = _new_node(_nil, -1, elements[mid]);
        _root->children[LEFT] = _build(0, mid - 1, _root, elements);
        _root->children[RIGHT] = _build(mid + 1, num - 1, _root, elements);
        _update(_root);
    }

    void add(int x, int y, int value){
        _find(x, _nil);
        _find(y + 2, _root);
        _root->children[RIGHT]->children[LEFT]->lazy += value;
    }
    void reverse(int x, int y){
        _find(x, _nil);
        _find(y + 2, _root);
        _root->children[RIGHT]->children[LEFT]->is_reverse ^= true;
    }

    void insert(int x, int value){
        _find(x + 1, _nil);
        _find(x + 2, _root);
        _root->children[RIGHT]->children[LEFT] = _new_node(_root->children[RIGHT], -1, value);
    }

    void revolve(int x, int y, int T){
        int len = y - x + 1;
        T %= len;
        if(T){
            _find(y - T + 1, _nil);
            _find(y + 2, _root);
            _inner_node *tmp = _root->children[RIGHT]->children[LEFT];
            _root->children[RIGHT]->children[LEFT] = _nil;
            _find(x, _nil);
            _find(x + 1, _root);
            _root->children[RIGHT]->children[LEFT] = tmp;
            tmp->parent = _root->children[RIGHT];
        }
    }

    void remove(int x){
        _find(x, _nil);
        _find(x + 2, _root);
        _root->children[RIGHT]->children[LEFT] = _nil;
        _update(_root);
    }

    int min(int x, int y){
        _find(x, _nil);
        _find(y + 2, _root);
        _pushdown(_root->children[RIGHT]->children[LEFT]);
        return _root->children[RIGHT]->children[LEFT]->min;
    }

//    void clear(){
//        _num_nodes = 0;
//        _root = _nil;
////        insert(-INF);
////        insert(INF);
//    }

//    void insert(int key){
//        if(_root == _nil){
//            _root = _new_node(_nil, key);
//            return;
//        }
//        _inner_node *x = _root;
//        while(true){
//            int direction = (x->key < key);
//            if(x->children[direction] == _nil){
//                x->children[direction] = _new_node(x, key);
//                _update(x);
//                _splay(x->children[direction], _nil);
//                return;
//            }
//            else{
//                x = x->children[direction];
//            }
//        }
//    }

//    void remove(int key){
//        int k = _find(key);
//        _find(k - 1, _nil);
//        _find(k + 1, _root);
//        _root->children[RIGHT]->children[LEFT] = _nil;
//        _update(_root->children[RIGHT]);
//        _update(_root);
//    }

//    int get_kth(int k){
//        _find(k + 1, _nil); // '+1' because '-INF' inserted for safety by splay tree itself.
//        return _root->key;
//    }

   enum Direction{LEFT=0, RIGHT};
private:
   struct _inner_node{
       int key;
       int value;
       int size;
       int lazy;
       int min;
       bool is_reverse;
       _inner_node *parent;
       _inner_node *children[2];
   }node[MAX_N], _nil_node;  //  _nil_node is a dummy node pointed by _nil(a pointer). This node is added mainly for coding convenience.
   _inner_node *_root, *_nil;
   int _num_nodes;

   _inner_node* _new_node(_inner_node *parent, int key, int value=0){
       node[_num_nodes].key = key;
       node[_num_nodes].size = 1;
       node[_num_nodes].lazy = 0;
       node[_num_nodes].value = value;
       node[_num_nodes].min = value;
       node[_num_nodes].is_reverse = false;
       node[_num_nodes].parent = parent;
       node[_num_nodes].children[LEFT] = _nil;
       node[_num_nodes].children[RIGHT] = _nil;
       return &node[_num_nodes++];
   }

   _inner_node* _build(int l, int r, _inner_node *parent, int elements[]){
       if(l > r) return _nil;
       int mid = (l + r) >> 1;
       _inner_node *x = _new_node(parent, -1, elements[mid]);
       x->children[LEFT] = _build(l, mid - 1, x, elements);
       x->children[RIGHT] = _build(mid + 1, r, x, elements);
       _update(x);
       return x;
   }

   void _pushdown(_inner_node *x){
       if(x == _nil) return ;

       if(x->is_reverse){
           swap(x->children[LEFT], x->children[RIGHT]);
           x->children[LEFT]->is_reverse ^= true;
           x->children[RIGHT]->is_reverse ^= true;
           x->is_reverse = false;
       }

       if(x->lazy){
           x->value += x->lazy;
           x->min += x->lazy;
           x->children[LEFT]->lazy += x->lazy;
           x->children[RIGHT]->lazy += x->lazy;
           x->lazy = 0;
       }
   }

   void _update(_inner_node *x){
       if(x == _nil) return;
       x->size = x->children[LEFT]->size + x->children[RIGHT]->size + 1;
       x->min = std::min(x->value, std::min(x->children[LEFT]->min, x->children[RIGHT]->min));
   }

   void _rotate(_inner_node *x, Direction direction){
       _inner_node *p = x->parent;
       _pushdown(x->children[LEFT]);
       _pushdown(x->children[RIGHT]);
       _pushdown(p->children[direction]);
       p->children[!direction] = x->children[direction];
       p->children[!direction]->parent = p;
       x->children[direction] = p;
       x->parent = p->parent;
       if(p->parent->children[LEFT] == p){
           p->parent->children[LEFT] = x;
       }
       else{
           p->parent->children[RIGHT] = x;
       }
       p->parent = x;
       _update(p);
       _update(x);
       if(_root == p) _root = x;
   }

   // splay x to the child of y. to root if y is nil.
   void _splay(_inner_node *x, _inner_node *y){
       _pushdown(x);
       while(x->parent != y){
           if(x->parent->parent == y){
               if(x->parent->children[LEFT] == x){
                   _rotate(x, RIGHT);
               }
               else{
                   _rotate(x, LEFT);
               }
           }
           else if(x->parent->parent->children[LEFT] == x->parent){
               if(x->parent->children[LEFT] == x){
                   _rotate(x->parent, RIGHT);
                   _rotate(x, RIGHT);
               }
               else{
                   _rotate(x, LEFT);
                   _rotate(x, RIGHT);
               }
           }
           else{
               if(x->parent->children[RIGHT] == x){
                   _rotate(x->parent, LEFT);
                   _rotate(x, LEFT);
               }
               else{
                   _rotate(x, RIGHT);
                   _rotate(x, LEFT);
               }
           }
           _update(x);
       }
   }

//   int _find(int key){
//       _inner_node *x = _root;
//       int count = 0;
//       while(true){
//           if(x->key == key){
//               return count + x->size - x->children[RIGHT]->size;
//           }
//           else if(x->key > key){
//               x = x->children[LEFT];
//           }
//           else{
//               count += x->size - x->children[RIGHT]->size;
//               x = x->children[RIGHT];
//           }
//       }
//   }

   void _find(int k, _inner_node *y){
       _inner_node *x = _root;
       _pushdown(x);
       while(k != x->children[LEFT]->size + 1){
           if(k <= x->children[LEFT]->size){
               x = x->children[LEFT];
           }
           else{
               k -= x->children[LEFT]->size + 1;
               x = x->children[RIGHT];
           }
           _pushdown(x);
       }

       _splay(x, y);
   }
};

int N, M;
int main(){
    splay_tree tree;
    char cmd[10];
    int seq[MAX_N];
    int x, y ,val;
    while(scanf("%d", &N) != EOF){
        for(int i=1; i<=N; ++i) scanf("%d", &seq[i]);
        seq[0] = INF;
        seq[N+1] = INF;
        tree.build(seq, N + 2);
        scanf("%d", &M);
        for(int i=0; i<M; ++i){
            scanf("%s", cmd);
            if(!strcmp(cmd, "ADD")){
                scanf("%d%d%d", &x, &y, &val);
                tree.add(x, y, val);
            }
            else if(!strcmp(cmd, "REVERSE")){
                scanf("%d%d", &x, &y);
                tree.reverse(x, y);
            }
            else if(!strcmp(cmd, "REVOLVE")){
                scanf("%d%d%d", &x, &y, &val);
                tree.revolve(x, y, val);
            }
            else if(!strcmp(cmd, "INSERT")){
                scanf("%d%d", &x, &val);
                tree.insert(x, val);
            }
            else if(!strcmp(cmd, "DELETE")){
                scanf("%d", &x);
                tree.remove(x);
            }
            else{
                scanf("%d%d", &x, &y);
                printf("%d\n", tree.min(x, y));
            }
        }
    }
    return 0;
}
