#include <iostream>
#include <iomanip>

using namespace std;

typedef struct TreeNode
{
    char info;
    TreeNode* left, * right;
} TreeNode;
typedef struct TreeNode* ExpTree;


struct Stack{
    char c;
    Stack* next;
    
}*top;

struct Stack_tree{
    TreeNode c;
    Stack_tree* next;
    
}*top2;

Stack* InS(Stack* p, char out){
    Stack* t = new Stack;
    t->c =  out;
    t->next=p;
    return t;
}

Stack* OutS(Stack* p,char& in){
    Stack* t = p;
    in =p->c;
    p= p->next;
    delete t;
    return p;
}

Stack_tree* InS_tree(Stack_tree* p, ExpTree tree){
    Stack_tree* t = new Stack_tree;
    t->c = *tree;
    t->next=p;
    return t;
}

TreeNode* OutS_tree(Stack_tree* p,ExpTree tree){
    tree = &p->c;
    p= p->next;
    return tree;
}




ExpTree Create_Node(int info);
ExpTree constructTree(ExpTree T, char postfix[]);
int getPriority(char ch);
void Convert_In_To_Post(string infix, char postfix[]);
// Extra
double resultExpression(char postfix[]);
int height(ExpTree T);
int size(ExpTree node);
// Output
void show_node(ExpTree T);
void preorder(ExpTree T);
void postorder(ExpTree T);
void inorder(ExpTree T);
void printExtra(char postfix[], ExpTree tree);
void display(ExpTree tree, char postfix[]);
void line();
// Input Validation
bool IsExpCorrect(string infix);
bool isOperator(char ch);
bool isDigit(char c);
int charToInt(char str);


int main()
{
    cout << "\n\t\t    ( Binary Expression Tree )" << endl;
    line();
    cout << "\n Enter Expression : ";
    string infix;
    cin >> infix;
    char* postfix = (char*)malloc(sizeof(char) * infix.length());
    Convert_In_To_Post(infix, postfix);
    ExpTree tree1 = NULL;
    tree1 = constructTree(tree1, postfix);
    cout<<"Res = "<<fixed<<setprecision(2)<<resultExpression(postfix)<<endl;
    display(tree1, postfix);
    return 0;
}

void line()
{
    cout << "__________________________________________________________________" << endl;
}

void display(ExpTree tree, char postfix[])
{
    line();
    cout << "\n PreOrder Traverse  (Parent, Left, Right) : [ ";
    preorder(tree);
    cout << "]" << endl;
    line();
    cout << "\n PostOrder Traverse (Left, Right, Parent) : [ ";
    postorder(tree);
    cout << "]" << endl;
    line();
    cout << "\n InOrder Traverse   (Left, Parent, Right) : [ ";
    inorder(tree);
    cout << "]" << endl;

}

bool isDigit(char ch)
{
    if (ch > 47 && ch < 57)
        return true;
    return false;
}
bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^')
        return true;
    return false;
}

bool IsExpCorrect(string infix)
{
    for (unsigned int i = 0; i < infix.length(); i++) {
        if (!isDigit(infix[i]) && !isOperator(infix[i]) && infix[i] !=*"(" && infix[i] !=*")"){
            return false;
            
        }
    }
    return true;
}

ExpTree Create_Node(int info)
{
    TreeNode* temp;
    temp = (TreeNode*)malloc(sizeof(TreeNode));
    if (temp == NULL)
    {
        cout << "Out of space!\n";
        return (temp);
    }
    temp->left = NULL;
    temp->right = NULL;
    temp->info = info;
    return temp;
};

ExpTree constructTree(ExpTree tree, char postfix[])
{
    Stack_tree* Op =NULL;
    int i = 0;
    TreeNode* temp_tree1;
    TreeNode* temp_tree2;
    while (postfix[i] != '\0')
    {
        if (!(postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/'
            || postfix[i] == '%' || postfix[i] == '^'||postfix[i] == 'e'|| postfix[i] == 'l'))
        {
            tree = Create_Node(postfix[i]);
            Op = InS_tree(Op,tree);
        }
        else
        {
            tree = Create_Node(postfix[i]);
            temp_tree1 = OutS_tree(Op,tree);
            Op=Op->next;
            temp_tree2 = OutS_tree(Op,tree);
            Op=Op->next;
            tree->right = temp_tree1;
            tree->left = temp_tree2;
            Op = InS_tree(Op,tree);
        }
        i++;
    }
    return tree;
}

void show_node(ExpTree T)
{
    cout << T->info << " ";
}
void preorder(ExpTree T)
{
    if (T != NULL)
    {
        show_node(T);
        preorder(T->left);
        preorder(T->right);
    }
}
void postorder(ExpTree T)
{
    if (T != NULL)
    {
        postorder(T->left);
        postorder(T->right);
        show_node(T);
    }
}
void inorder(ExpTree T)
{
    if (T != NULL)
    {
        inorder(T->left);
        show_node(T);
        inorder(T->right);
    }
}
int getPriority(char ch)
{
    switch (ch)
    {
        case 'l':
        case 'e':
    case '^':
        return 4;
    case '%':
        return 3;
    case '/':
    case '*':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}
void Convert_In_To_Post(string infix, char postfix[])
{
    Stack* t, * Op =NULL;
    char  a;
    int k=0,l=0;
    while (infix[k]!='\0') {
        if(infix[k]>='a'&&infix[k]<='z' && infix[k]!='l' &&infix[k]!='e'){
            postfix[l++]= infix[k];
        }
        if (infix[k] >47 && infix[k] <57){
            postfix[l++]= infix[k];
        }
        if(infix[k]=='(') Op = InS(Op,infix[k]);
        if(infix[k]==')'){
            while((Op->c)!='('){
                Op=OutS(Op,a);
                if(!Op) a = '\0';
                postfix[l++]=a;
            }
            t=Op;
            Op=Op->next;
            delete t;
        }
        if(infix[k]=='+'|| infix[k]=='-'||infix[k]=='*'||infix[k]=='/'||infix[k]=='^'||infix[k] == 'e'|| infix[k] == 'l'){
            while (Op!=NULL && getPriority(Op->c)>=getPriority(infix[k])){
                Op = OutS(Op,a);
                postfix[l++]=a;
            }
            Op=InS(Op,infix[k]);
        }
        k++;
    }
    while(Op!=NULL){
        Op=OutS(Op,a);
        postfix[l++]=a;
    }
    postfix[l]='\0';
 
}



int charToInt(char str){
    int num;
    num = str - '0';
    return num;
}

double log(double a, double b)
{
    return log(b) / log(a);
}

double resultExpression(char postfix[])
{
    int i;
    char ss,ss1,ss2,ssR = 'z'+1;
    double op1,op2,res=0,mas[200];
    for(i=0;postfix[i]!='\0';++i){
        ss=postfix[i];
        if (ss >= 47 && ss <= 57){
            mas[int(ss)]=charToInt(ss);
        }
        else if(ss>='a'&& ss<='z' && ss!='l' && ss!='e'){
            cout<<ss<<" = ";
            cin>>mas[int(ss)];
        }
    }
    for(i=0;postfix[i]!='\0';++i){
        ss=postfix[i];
        if(!(ss == '+' || ss == '-' || ss == '*' || ss == '/' || ss == '%' || ss == '^'|| ss == 'e'|| ss == 'l')) top = InS(top,ss);
        else{
            top  = OutS(top,ss2);
            top  = OutS(top,ss1);
            op2=mas[int(ss2)];
            op1=mas[int(ss1)];
            switch (ss)
            {
            case '+':
                    res = op1 + op2;
                break;
            case '-':
                    res = op1 - op2;
                break;
            case '*':
                    res = op1 * op2;
                break;
            case '/':
                if (op2 == 0)
                {
                    cout << "\n Math Error: Can't Divide by Zero " << endl;
                    break;
                }
                    res = op1 / op2;
                break;
            case '%':
                if (op2 == 0)
                {
                    cout << "\n Math Error: Can't Divide by Zero " << endl;
                    break;
                }
                    res = ((int)op1) % ((int)op2);
                break;
            case '^':
                    res = pow(op1, op2);
                break;
                    
            case 'e':
                    res = exp(op1);
                break;
            case 'l':
                    res = log(op1, op2);
                break;
            }
            mas[int(ssR)]=res;
            top= InS(top,ssR);
            ssR++;
            }
    }
    return res;

}

