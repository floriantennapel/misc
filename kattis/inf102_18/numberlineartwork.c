#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Mark
{
    long double pos;
    char color[11];
} Mark;

typedef struct BstNode 
{
    Mark mark;
    struct BstNode *left;
    struct BstNode *right;
} BstNode;

void bst_insert(BstNode* root, Mark mark)
{
    BstNode* allocated = malloc(sizeof(BstNode));
    allocated->mark = mark;
    allocated->left = NULL;
    allocated->right = NULL;

    BstNode* current = root;
    while (1) { 
        if (mark.pos <= current->mark.pos) {
            if (current->left == NULL) {
                current->left = allocated;
                break;
            } else {
                current = current->left;
            } 
        } else {
            if (current->right == NULL) {
                current->right = allocated;
                break;
            } else {
                current = current->right;
            }
        }
    }
}

long double find_left(const BstNode* root, long double val)
{
    const BstNode* current = root;
    long double min = -1;

    while (current != NULL) {
        long double current_pos = current->mark.pos;
        if (current_pos < val) {
            if (min == -1 || current_pos < val) {
                min = current_pos;
            }
            current = current->right;
        } else {
            current = current->left;
        }
    }

    return min;
}

long double find_right(const BstNode* root, long double val)
{
    const BstNode* current = root;
    long double max = -1;
    while (current != NULL) {
        long double current_pos = current->mark.pos;
        if (current_pos >= val) {
            if (current_pos > max) {
                max = current_pos;
            }
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return max;
}

const BstNode* find_min(const BstNode* root)
{
    const BstNode* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

const BstNode* find_max(const BstNode* root)
{
    const BstNode* current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}

void traverse(BstNode* node, const BstNode* min)
{
    if (node == NULL) return;

    traverse(node->left, min);
    if (node != min)
        printf(" %s", node->mark.color);
    traverse(node->right, min);

    free(node);
}

long double mark_pos(const BstNode* root, long double arm)
{
    long double left = find_left(root, arm);
    long double right = find_right(root, arm);

    if (left == -1) left = 0;
    if (right == -1) right = find_max(root)->mark.pos;

    return left + (right - left) / 2.l;
}

int main()
{
    int n, m;
    Mark mark;
    scanf("%d %d\n", &n, &m);
    long double arms[n];
    for (int i = 0; i < n; i++) {
        arms[i] = i;
    }
    
    char* buf = malloc(n * 11 + 1);
    fgets(buf, n * 11 + 2, stdin);
    
    char* color = strtok(buf, " \n");
    strcpy(mark.color, color);
    mark.pos = 0;
    BstNode* root = malloc(sizeof(BstNode));
    root->left = NULL;
    root->right = NULL;
    root->mark = mark;

    for (int i = 1; i < n; i++) {
        color = strtok(NULL, " \n");
        strcpy(mark.color, color);
        mark.pos = i;
        bst_insert(root, mark);
    }

    free(buf);

    int arm;
    char col[11];
    for (int i = 0; i < m; i++) {
        scanf("%d %s\n", &arm, col);
        if (strcmp(col, "R") == 0) {
            arms[arm] += 1;
        } else if (strcmp(col, "L") == 0) {
            arms[arm] -= 1;
        } else {
            mark.pos = mark_pos(root, arms[arm]);
            arms[arm] = mark.pos;
            strcpy(mark.color, col);
            bst_insert(root, mark);
        }
    }

    const BstNode* min = find_min(root);
    printf("%s", min->mark.color);
    traverse(root, min);
    puts("");
}
