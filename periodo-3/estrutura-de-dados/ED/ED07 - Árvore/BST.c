BST *BST_alloc(int (*compar)(void*, void*)) {
    BST *bst = NULL;
    
    if (compar) {
        bst = (BST*) malloc(sizeof(BST));
        bst->value = NULL;
        bst->left = NULL;
        bst->right = NULL;
        bst->compar = compar;
    }

    return bst;
}

void BST_free(BST *bst) {
    if (bst != NULL) {
        BST_free(bst->left);
        BST_free(bst->right);
        free(bst);
    }
}

void BST_insert(BST *bst, void *value) {

    if (bst && value) {
        if (bst->value == NULL)
            bst->value = value;
        else
            if (bst->compar(bst->value, value) < 0) {
                if (bst->right == NULL)
                    bst->right = BST_alloc(bst->compar);
                
                BST_insert(bst->right, value);
            }
            else 
                if (bst->compar(bst->value, value) > 0) {
                    if (bst->left == NULL)
                        bst->left = BST_alloc(bst->compar);

                    BST_insert(bst->left, value);
                }
	}
}

void *BST_search(BST *bst, void *value) {
    if (bst && value) {
        if (bst->value) {
            if (bst->compar(bst->value, value) == 0)
                return bst->value;
            else 
                if (bst->compar(bst->value, value) < 0)
                    return BST_search(bst->right, value);    
                else 
                    return BST_search(bst->left, value);
		}
	}
    return NULL;
}

