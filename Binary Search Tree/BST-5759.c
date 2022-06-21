#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//assuming you dont search for the last word and dont type numbers instead of characters


typedef struct node
{

    char info[200];
    struct node *left;
    struct node *right;
    //int size;

} node;


int max (int left,int right)
{

    if(left >= right)
        return left;
    else
        return right;
}


int height(node *root)
{

    if(root==NULL)
        return -1;
    else
        return 1 + max(height(root->left),height(root->right));
}

int size (node *root)
{

    if(root == NULL)
        return 0;
    else
        return 1 + size(root->left) + size(root->right);
}


node* newNode(char data[])
{

    node *temp =  (node*)malloc(sizeof(node));
    strcpy(temp->info, data);
    temp->left = temp->right = NULL;
    return temp;
}

node* insert(node* root, char data[])
{

    if (root == NULL)
        return newNode(data);
    if (strcmp(root->info, data) > 0 )
        root->left  = insert(root->left, data);
    else if (strcmp(root->info, data) < 0 )
        root->right = insert(root->right, data);

    return root;
}

node *search(node* root, char data [], node*temp)
{


    if(root == NULL)
    {

        printf("%s\n", temp->info);
        return temp;
    }

    else if (strcmp(root->info, data) == 0)
    {

        printf("%s--This Word is Correct\n", data);
        //temp = NULL;
        return temp;
    }

    else if (strcmp(root->info, data) > 0 )
    {

        temp = root;
        root = root->left;
        search(root,data, temp);
    }

    else
    {

        temp = root;
        root = root->right;
        search(root,data, temp);
    }


}

node* parent(node* root, node *child, node* temp)
{

    if (strcmp(root->info, child->info) == 0)
    {

        return temp;
    }
    else if(strcmp(root->info, child->info) > 0 )
    {

        temp = root;
        root = root->left;
        parent(root, child, temp);
    }
    else
    {

        temp = root;
        root = root->right;
        parent(root, child, temp);
    }
}

void findsuc(node* root, node *nodee)
{


    node *forsearch = NULL;
    node *temp = nodee;
    node *parentt = parent(root, temp, forsearch);

    if(nodee->right != NULL)
    {

        temp = nodee->right;
        while(temp->left != NULL)
        {

            temp = temp->left;

        }
        node *suc = temp;
        printf("THE SUC IS %s\n",suc->info);
    }
    else if(nodee->right == NULL)
    {

        if(temp == parentt->right)
        {

            while(temp != parentt->left)
            {

                temp = parentt;
                parentt = parent(root, temp, forsearch);
            }
        }
        printf("THE SUC IS %s\n",parentt->info);
    }
    else if(temp == parentt->left)
    {

        printf("THE SUC IS %s\n",parentt->info);

    }
}

void findpre(node* root, node *nodee)
{

    node *forsearch = NULL;
    node *temp = nodee;
    node *parentt = parent(root, temp, forsearch);


    if(nodee->left != NULL)
    {

        temp = nodee->left;
        while(temp->right != NULL)
        {

            temp = temp->right;

        }
        node *pre = temp;
        printf("THE PRE IS %s\n\n\n", pre->info);
    }
    else if(nodee->left == NULL)
    {

        if(temp == parentt->left)
        {

            while(temp != parentt->right)
            {

                temp = parentt;
                parentt = parent(root, temp, forsearch);
            }

        }
        printf("THE PRE IS %s\n\n\n",parentt->info);
    }
    else if(temp == parentt->right)
    {

        printf("THE PRE IS %s\n\n\n",parentt->info);
    }
}

void BinaryTree(node *root)
{

    node* temp = NULL;
    char word [50];
    char check [50];
    char *tok;
    int i=0;
    FILE *file;
    file = fopen("EN-US-randomized.txt", "r");
    if(!file)
    {

        printf("Error file not found!\n");
        fclose(file);
        exit(1);
    }
    else
    {

        while(!feof(file))
        {

            fscanf(file, "%s", word);
            root = insert(root,word);
            i++;

        }
        printf("Height of tree = %d\n",height(root));
        printf("Size of tree = %d\n",size(root));
        printf("Enter a word to check for its spelling:\t");
        while(1)
        {
        gets(check);
        tok = strtok(check," ");
        while(tok != NULL){

              printf("%s\n",tok);

              node *ans = search(root, tok, temp);
              findsuc(root, ans);
              findpre(root, ans);
              tok = strtok(NULL," ");
        }

           /* node *ans = search(root, check, temp);
            findsuc(root, ans);
            findpre(root, ans);*/
            fclose(file);
        }
    }
}


void main()
{

    node *root = NULL;
    BinaryTree(root);//reads file , creates tree , prints heigth and size , takes a word and searches , prints suc and pre if word doesnt exist

}

