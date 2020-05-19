#include <bits/stdc++.h>
using namespace std;
string str, vertex;

typedef struct link{
    string equation;
    link *left = NULL, *right = NULL;
}tree;

tree *t = NULL;


//Логическое значение
bool boolean_value(tree* &curr)
{
    if (curr == NULL)
        return -1;
    else
    if (curr->equation == "!")
        return !boolean_value(curr->left);
    else
    if (curr->equation == "1")
        return 1;
    else
    if (curr->equation == "0")
        return 0;
    else
    if (curr->equation == "+")
        return boolean_value(curr->left) || boolean_value(curr->right);
    else
    if (curr->equation == "*")
        return boolean_value(curr->left) && boolean_value(curr->right);
    else
    {
        cout << "It is impossible to find the value";
        exit(0);
    }
}

void show(tree* &curr, int n)
{
    if (curr!= NULL)
    {
        show(curr->left, n + 1);
        cout << setw(n * 3) << curr->equation << '\n';
        show(curr->right, n + 1);
    }
    return;
}

//Разделение на два поддерева с общей вершиной +
void get_plus_strings(string s, string &tmp1, string &tmp2)
{
    int n = s.length(), left_brackets = 0, right_brackets = 0;
    for (int i = 0;i < n;i++)
    {
        if (s[i] == '(')
            left_brackets++;
        if (s[i] == ')')
            right_brackets++;
        if (s[i] == '+' && left_brackets == right_brackets)
        {
            tmp1 = s.substr(0, i);
            tmp2 = s.substr(i + 1, n - i);
            return;
        }
    }
    return;
}

//Разделение на два поддерева с общей вершиной *
void get_multiplication_strings(string s, string &tmp1, string &tmp2)
{
    int n = s.length(), left_brackets = 0, right_brackets = 0;
    for (int i = 0;i < n;i++)
    {
        if (s[i] == '(')
            left_brackets++;
        if (s[i] == ')')
            right_brackets++;
        if (s[i] == '*' && left_brackets == right_brackets)
        {
            tmp1 = s.substr(0, i);
            tmp2 = s.substr(i + 1, n - i);
            return;
        }
    }
    return;
}

//Создаем новый узел с двумя поддеревьями
tree* new_vertex(string c, string str1, string str2)
{
    tree *tmp = new tree, *tmp_left = new tree, *tmp_right = new tree;
    tmp->equation = c;
    tmp->left = tmp_left;
    tmp->right = tmp_right;
    tmp->left->equation = str1;
    tmp->right->equation = str2;
    return tmp;
}

//Наличие операции +
bool plus_in_string(string s)
{
    int left_brackets = 0, right_brackets = 0;
    for (int i = 0;i < s.length();i++)
    {
        if (s[i] == '+' && left_brackets == right_brackets)
            return 1;
        if (s[i] == '(')
            left_brackets++;
        if (s[i] == ')')
            right_brackets++;
    }
    return 0;
}

//Наличие операции *
bool multiplication_in_string(string s)
{
    int left_brackets = 0, right_brackets = 0;
    for (int i = 0;i < s.length();i++)
    {
        if (s[i] == '*' && left_brackets == right_brackets)
            return 1;
        if (s[i] == '(')
            left_brackets++;
        if (s[i] == ')')
            right_brackets++;
    }
    return 0;
}



//Создаем по строке логическое дерево
tree* make_tree(string &s)
{
    string tmp1, tmp2;
    tree *tmp = new tree;
    tmp->equation = s;
    //лишние скобки придется убрать
    if (s[0] == '(' && s[s.length() - 1] == ')')
        s = s.substr(1, s.length() - 2);
    if (plus_in_string(s))
    {
        string vertex = "+";
        get_plus_strings(s, tmp1, tmp2);
        tmp = new_vertex(vertex, tmp1, tmp2);
        tmp->left = make_tree(tmp1);
        tmp->right = make_tree(tmp2);
    }
    else
    if (multiplication_in_string(s))
    {
        string vertex = "*";
        get_multiplication_strings(s, tmp1, tmp2);
        tmp = new_vertex(vertex, tmp1, tmp2);
        tmp->left = make_tree(tmp1);
        tmp->right = make_tree(tmp2);
    }
    else
    if (s[0] == '!')
    {
        vertex = "!";
        tmp->equation = vertex;
        tmp1 = s.substr(1, s.length() - 1);
        tmp->left = make_tree(tmp1);
    }
    return tmp;
}

int main()
{
    ifstream in("input.txt");
    getline(in, str);
    tree *t = make_tree(str);
    show(t, 0);
    cout << "The answer is:\n" << boolean_value(t);
    return 0;
}
