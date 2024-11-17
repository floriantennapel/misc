#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

/*
 * red black BST based on code in Sedgewick & Wayne, Algorithms chap. 3.3
 */

typedef struct _Node
{
    int val;
    unsigned counter : 31;
    unsigned color : 1;
    struct _Node *left, *right;
} Node;

typedef struct
{
    Node *root;
} BST;

Node* _rotLeft(Node* h)
{
    Node* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

Node* _rotRight(Node* h)
{
    Node* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

void _colorFlip(Node* h)
{
    h->color = RED;
    h->left->color = BLACK;
    h->right->color = BLACK;
}

int _is_red(const Node* n)
{
    if (!n)
        return 0;
    return n->color == RED;
}

Node* _insert(Node* h, int val)
{
    if (!h) {
        Node* ret = malloc(sizeof(Node));
        *ret = (Node) { val, 1, RED, NULL, NULL };
        return ret;
    }

    if (val < h->val)
        h->left = _insert(h->left, val);
    else if (val > h->val)
        h->right = _insert(h->right, val);
    else
        ++h->counter;

    if (_is_red(h->right) && !_is_red(h->left))
        h = _rotLeft(h);
    if (_is_red(h->left) && _is_red(h->left->left))
        h = _rotRight(h);
    if (_is_red(h->left) && _is_red(h->right))
        _colorFlip(h);

    return h;
}

void insert(BST* tree, int val)
{
    tree->root = _insert(tree->root, val);
    tree->root->color = BLACK;
}

Node* mode1(Node* h, int val)
{
    if (!h) return NULL;

    if (h->val <= val)
        return mode1(h->right, val);
    if (h->val == val + 1)
        return h;

    Node* res = mode1(h->left, val);
    if (!res)
        return h;
    return res;
}

Node* mode2(Node* h, int val)
{
    if (!h) return NULL;

    if (h->val > val)
        return mode2(h->left, val);
    if (h->val == val)
        return h;

    Node* res = mode2(h->right, val);
    if (!res)
        return h;
    return res;
}

Node* slow_remove(Node* h, int val)
{
    if (h->val == val) {
        free(h);
        return NULL;
    }
    if (val > h->val)
        h->right = slow_remove(h->right, val);
    else
        h->left = slow_remove(h->left, val);
    return h;
}

Node* get_min_parent(Node* parent)
{
    Node* current = parent->left;
    if (!current->left)
        return parent;
    return get_min_parent(current);
}

void rem_node(BST* tree, Node* h)
{
    if (!(h->left || h->right))
        tree->root = slow_remove(tree->root, h->val);
    else if (!h->right || !h->left) {
        Node* tmp = (h->left) ? h->left : h->right;
        h->val = tmp->val;
        h->counter = tmp->counter;
        h->left = tmp->left;
        h->right = tmp->right;
        free(tmp);
    } else {
        if (!h->right->left) {
            Node* tmp = h->right;
            h->val = tmp->val;
            h->counter = tmp->counter;
            h->right = tmp->right;
            free(tmp);
        } else {
            Node* min_parent = get_min_parent(h->right);
            Node* min = min_parent->left;
            h->val = min->val;
            h->counter = min->counter;
            min_parent->left = min->right;
            free(min);
        }
    }
}

/** only for debugging, might be useful for later */
void print_tree(const Node* node, int depth)
{
    if (!node)
        return;

    for (int i = 0; i < depth; i++)
        printf("  ");

    printf("%2d,%d\n", node->val, node->counter);
    print_tree(node->left, depth + 1);
    print_tree(node->right, depth + 1);
}

int main()
{
    int n, q, d, mode;
    scanf("%d %d", &n, &q);
    BST tree = { NULL };
    for (int i = 0; i < n; i++) {
        scanf("%d", &d);
        insert(&tree, d);
    }
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &mode, &d);
        Node* res = (mode == 1)
            ? mode1(tree.root, d)
            : mode2(tree.root, d);
        printf("%d\n", res ? res->val : -1);
        if (res && !--res->counter)
            rem_node(&tree, res);
    }
}