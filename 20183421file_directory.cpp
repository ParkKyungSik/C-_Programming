#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
using namespace std;

typedef struct tagLCRSNode {
    char data[300];
    struct tagLCRSNode* parent;
    struct tagLCRSNode* leftChild;
    struct tagLCRSNode* rightSibling;
} LCRSNode;

void promptCLI(vector<string>& tokens);
LCRSNode* processCLI(vector<string>& tokens, LCRSNode* folder, LCRSNode* now);
int searchNowFolder(vector<string>& tokens, string now);
void funcAdd(LCRSNode* folder, string after);
void funcLs(LCRSNode* folder); 
LCRSNode* funcCd(LCRSNode* folder, LCRSNode* now, string after);
int funcCut(LCRSNode* folder, LCRSNode* now, string after); 
int funcCopy(LCRSNode* folder, LCRSNode* now, string after);
void funcPaste(LCRSNode* folder, LCRSNode* now);
void funcRm(LCRSNode* folder, LCRSNode* now, string after);
LCRSNode* LCRS_createNode(string data);
void LCRS_destroyNode(LCRSNode* node);
void LCRS_destroyTree(LCRSNode* root);
void LCRS_deleteFile(LCRSNode* root);
void LCRS_addChildNode(LCRSNode* parent, LCRSNode* child);
void LCRS_printTree(LCRSNode* node, int depth);
LCRSNode* searchNode(LCRSNode* p, string data);
int beforFolderPrint(LCRSNode* node);

LCRSNode* copyNode;
int main(){
    LCRSNode* folder = LCRS_createNode("");
    LCRSNode* now = folder;
    vector<string> tokens;
    copyNode = LCRS_createNode("");
    cout << "/>";
    while (true)
    {
        promptCLI(tokens);
        /* Do something */
        now = processCLI(tokens, folder, now);
        if (tokens.size() > 0)
            tokens.clear();
    }
}
void promptCLI(vector<string>& tokens) {
    string command;
    string ctok;
    getline(cin, command);
    stringstream sscmd(command);
    while (getline(sscmd, ctok, ' '))
    {
        tokens.push_back(ctok);
    }
    return;
}
LCRSNode* processCLI(vector<string>& tokens, LCRSNode* folder, LCRSNode* now) {
    int n = tokens.size();
    int flag1;
    string nowFolder;
    string command;
    if(tokens.size() >= 1)
        command = tokens[0];
    
    transform(command.begin(), command.end(), command.begin(), tolower);

    if (command.compare("add") == 0) {
        funcAdd(now, tokens[1]);
    }else if (command.compare("ls") == 0) {
        funcLs(now);
    }else if (command.compare("cd") == 0) {
        now = funcCd(folder, now, tokens[1]);
    }else if (command.compare("cut") == 0) {
        flag1 = funcCut(folder, now, tokens[1]);
    }else if (command.compare("copy") == 0) {
        flag1 = funcCopy(folder, now, tokens[1]);
    }else if (command.compare("paste") == 0) {
        funcPaste(folder, now);
    }else if (command.compare("rm") == 0) {
        funcRm(folder, now, tokens[1]);
    }else if (command.compare("exit") == 0) {
        exit(0);
    }
    int flag = beforFolderPrint(now);
    if(flag == 1)
        printf("/>");
    else {
        printf(">");
    }
    return now;
}
void funcAdd(LCRSNode* folder, string after) {
    LCRSNode* newnode = LCRS_createNode(after);
    LCRS_addChildNode(folder, newnode);
}
void funcLs(LCRSNode* now) {
    LCRS_printTree(now, 0);
}
LCRSNode* funcCd(LCRSNode* folder, LCRSNode* now, string after) {
    if (after.at(0) == '.' && after.at(1) == '.' && after.at(2) == '/') {
        //상위 이동
        if(now->parent != NULL)
            now = now->parent;
    }
    else {
        //상대 경로
        now = searchNode(now, after);
    }
    return now;
}
int funcCut(LCRSNode* folder, LCRSNode* now, string after) {
    now = searchNode(now, after);
    copyNode = now;
    LCRS_deleteFile(now);
    return 0;
}

int funcCopy(LCRSNode* folder, LCRSNode* now, string after) {
    now = searchNode(now, after);
    copyNode = now;
    return 1;
}

void funcPaste(LCRSNode* folder, LCRSNode* now) {
    LCRS_addChildNode(now, copyNode);
}

void funcRm(LCRSNode* folder, LCRSNode* now, string after) {
    LCRSNode* temp = searchNode(now, after);
    LCRSNode* start = temp->parent->leftChild;
    LCRSNode* before = NULL;
    
    while (start != NULL) {
        if (start->data == after && before == NULL) {
            temp->parent->leftChild = start->rightSibling;
            break;
        }
        else if(start->data == after && before != NULL){
            before->rightSibling = start->rightSibling;
        }

        before = start;
        start = start->rightSibling;
    }
}



LCRSNode* LCRS_createNode(string data) {
    LCRSNode* newNode = (LCRSNode *)malloc(sizeof(LCRSNode));
    int N = data.size();
    const char* cc = data.c_str();
    char* c = (char *)cc;
    c[N] = '\0';
    strcpy_s(newNode->data, sizeof(newNode->data), c);
    newNode->parent = NULL;
    newNode->leftChild = NULL;
    newNode->rightSibling = NULL;
    return newNode;
}
void LCRS_destroyNode(LCRSNode* node) {
    free(node);
}

void LCRS_destroyTree(LCRSNode* root) {
    if (root->rightSibling != NULL) {
        LCRS_destroyTree(root->rightSibling);
    }

    if (root->leftChild != NULL) {
        LCRS_destroyTree(root->leftChild);
    }

    root->parent = NULL;
    root->leftChild = NULL;
    root->rightSibling = NULL;
    LCRS_destroyNode(root);
}
void LCRS_deleteFile(LCRSNode* root) {
    root->parent = NULL;
    root->leftChild = NULL;
    root->rightSibling = NULL;
    LCRS_destroyNode(root);
}

void LCRS_addChildNode(LCRSNode* parent, LCRSNode* child) {
    if (parent->leftChild == NULL) {
        parent->leftChild = child;
    }
    else {
        LCRSNode* temp = parent->leftChild;
        while (temp->rightSibling != NULL) {
            temp = temp->rightSibling;
        }
        temp->rightSibling = child;
    }
    child->parent = parent;
}

void LCRS_printTree(LCRSNode* node, int depth) {
    int i = 0;
    if (depth != 0) {
        beforFolderPrint(node);
        cout << endl;
    }
    if (node->leftChild != NULL) {
        LCRS_printTree(node->leftChild, depth + 1);
    }
    if (node->rightSibling != NULL) {
        LCRS_printTree(node->rightSibling, depth);
    }
    
}
LCRSNode* searchNode(LCRSNode* p, string data) {
    if(p == NULL)return 0;
    if (p->data == data) return p;

    LCRSNode* Right = searchNode(p->rightSibling, data);
    LCRSNode* Left = searchNode(p->leftChild, data);

    if (Right != NULL)return Right;
    if (Left != NULL) return Left;

    return 0;
}
int beforFolderPrint(LCRSNode* node) {
    LCRSNode* tmp = node;
    vector<string> d;
    while (tmp != NULL) {
        string str(tmp->data);
        d.push_back(str);
        tmp = tmp->parent;
    }
    int N = d.size();
    for (int i = N - 1; i >= 0; i--) {
        cout << d[i];
    }
    return N;
}