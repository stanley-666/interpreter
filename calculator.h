#pragma once
#include <iostream>
#include <stack>
#include <vector>
    using namespace std;

#include "Data.h"
#include "ErrorManager.h"


class Calculator
{
private:
    Data mevaldata;
    ErrorManager& error_manager = ErrorManager::getInstance();

public:
    int Priority(Token &token)
    { // precedence checking
        if (token.type == PLS || token.type == MNS)
            return 1;
        else if (token.type == MUL || token.type == DIV)
            return 2;
        else if (token.type == G || token.type == GT || token.type == EQU ||
                 token.type == L || token.type == LT || token.type == NEQ)
            return 0;
        else
            return -1;
    } // Priority()

    vector<Token> InfixToPostfix(vector<Token> exp)
    {
        vector<Token> result;
        stack<Token> stack; // eval the newest
        for (int i = 0; i < exp.size(); i++)
        {
            Token c = exp[i];
            // If the scanned character is an
            // operand, add it to output.
            if (c.type == NUM || c.type == IDENT)
                result.push_back(c);
            // If the scanned character is an '(',
            // push it to the stack.
            else if (c.type == LEFT_PAREN)
                stack.push(c);
            else if (c.type == G || c.type == GT || c.type == EQU ||
                     c.type == L || c.type == LT || c.type == NEQ)
                stack.push(c);
            //  If the scanned character is an ')',
            // pop and output from the stack
            // until an '(' is encountered.
            else if (c.type == RIGHT_PAREN)
            {
                while (stack.top().type != LEFT_PAREN)
                {
                    result.push_back(stack.top());
                    stack.pop();
                } // while

                stack.pop();
            } // else if

            else
            { // an operator is encountered
                while (!stack.empty() && Priority(c) <= Priority(stack.top()))
                {
                    result.push_back(stack.top());
                    stack.pop();
                } // while

                stack.push(c);
            } // else
        } // for

        // pop all the operators from the stack
        while (!stack.empty())
        {
            result.push_back(stack.top());
            stack.pop();
        } // while

        return result;
    } // InfixToPostfix()

    void Calculate(vector<Token> postfix, float &res, bool &bopr, bool &setres)
    {
        float op1, op2;
        stack<float> stack;
        for (int i = 0; i < postfix.size(); i++)
        {                               // iterate through postfix string
            if (postfix[i].type == NUM) // if a digit, push to stack as int value
                stack.push(atoi(postfix[i].val.c_str()));
            else if (postfix[i].type == PLS)
            {                      // cases for different operators
                op1 = stack.top(); // assign top int to op1
                stack.pop();       // pop top
                op2 = stack.top(); // assign next into to op2
                stack.pop();
                // cout << "op1 " << op1 << " op2 " << op2 << endl;        // pop top
                stack.push(op2 + op1); // add op1 and op2, push result to stack
            } // else if

            else if (postfix[i].type == MNS)
            {
                op1 = stack.top();
                stack.pop();
                op2 = stack.top();
                stack.pop();
                // cout << "op1 " << op1 << " op2 " << op2 << endl;
                stack.push(op2 - op1);
            } // else if

            else if (postfix[i].type == MUL)
            {
                op1 = stack.top();
                stack.pop();
                op2 = stack.top();
                stack.pop();
                // cout << "op1 " << op1 << " op2 " << op2 << endl;
                stack.push(op2 * op1);
            } // else if

            else if (postfix[i].type == DIV)
            {
                op1 = stack.top();
                stack.pop();
                op2 = stack.top();
                stack.pop();
                // cout << "op1 " << op1 << " op2 " << op2 << endl;
                if (op1 == 0)
                {
                    cout << "Error" << endl;
                    return;
                } // if

                else
                {
                    stack.push(op2 / op1);
                } // else
            } // else if

            else if (postfix[i].type == NEQ)
            {
                setres = false;
                op1 = stack.top();
                stack.pop();
                op2 = stack.top();
                stack.pop();
                if (op2 != op1)
                    bopr = true;
                else
                {
                    bopr = false;
                } // else

                return;
            } // else if

            else if (postfix[i].type == EQU)
            {
                setres = false;
                op1 = stack.top();
                stack.pop();
                op2 = stack.top();
                stack.pop();
                if (op2 == op1)
                    bopr = true;
                else
                {
                    bopr = false;
                } // else

                return;
            } // else if

            else if (postfix[i].type == G)
            {
                setres = false;
                op1 = stack.top();
                stack.pop();
                op2 = stack.top();
                stack.pop();
                if (op2 > op1)
                    bopr = true;
                else
                {
                    bopr = false;
                } // else

                return;
            } // else if

            else if (postfix[i].type == GT)
            {
                setres = false;
                op1 = stack.top();
                stack.pop();
                op2 = stack.top();
                stack.pop();
                if (op2 >= op1)
                    bopr = true;
                else
                {
                    bopr = false;
                } // else

                return;
            } // else if

            else if (postfix[i].type == L)
            {
                setres = false;
                op1 = stack.top();
                stack.pop();
                op2 = stack.top();
                stack.pop();
                if (op2 < op1)
                    bopr = true;
                else
                {
                    bopr = false;
                } // else

                return;
            } // else if

            else if (postfix[i].type == LT)
            {
                setres = false;
                op1 = stack.top();
                stack.pop();
                op2 = stack.top();
                stack.pop();
                if (op2 <= op1)
                    bopr = true;
                else
                {
                    bopr = false;
                } // else

                return;
            } // else if
        } // for

        setres = true;
        res = stack.top();
    } // Calculator()

    void Evaluate(vector<Token> &exp)
    {
        float res = 0.00000;
        bool setres = false, bopr = false;
        int asn = 0;
        vector<Token> tmp = exp;
        vector<Token> tmp1, tmp2;
        vector<Token> postfix1, postfix2;
        ID newID;
        Token token;
        for (int i = 0; i < tmp.size(); i++)
        {
            if (tmp[i].type == ASSIGN)
            {
                asn = 3;
            } // if

            else
            {
                if (asn <= 2)
                    asn = 2;
            } // else

        } // for

        if (asn == 3)
        {
            for (int i = 0; i < tmp.size(); i++)
            {
                if (tmp[i].type == ASSIGN)
                {
                    if (i - 1 >= 0 && tmp[i - 1].type == IDENT)
                    {
                        newID.val = tmp[i - 1].val;
                        newID.type = IDENT;
                        for (int j = i + 1; j < tmp.size(); j++)
                        {
                            if (tmp[j].type == IDENT)
                            {
                                if (!mevaldata.Find(tmp[j]))
                                { // can't not find the IDENT declaration
                                    error_manager.ErrorHandling(Undefined_identifier, tmp[j].val);
                                    return;
                                } // if

                                else
                                {
                                    token = mevaldata.GetIDENTVALUE(tmp[j]);
                                    // CHANGE IDENT TO NUMBER VALUE
                                    tmp1.push_back(token);
                                } // else
                            } // if

                            else
                            {
                                tmp1.push_back(tmp[j]);
                            } // else
                        } // for

                        postfix1 = InfixToPostfix(tmp1);
                        Calculate(postfix1, res, bopr, setres);
                        if (setres == true)
                        {
                            newID.num = res;
                            cout << newID.num << endl;
                            mevaldata.PushIDENT(newID);
                            return;
                        } // if

                        else
                        {
                            if (bopr)
                                cout << "true" << endl;
                            else
                                cout << "false" << endl;
                            return;
                        } // else
                    } // if
                } // if
            } // for
        } // if

        else if (asn == 2)
        {
            for (int i = 0; i < tmp.size(); i++)
            {
                if (tmp[i].type == G || tmp[i].type == GT || tmp[i].type == NEQ ||
                    tmp[i].type == L || tmp[i].type == LT || tmp[i].type == EQU)
                {

                    if (!mevaldata.Find(tmp[i]))
                    { // can't not find the IDENT declaration
                        error_manager.ErrorHandling(Undefined_identifier, tmp[i].val);
                        return;
                    } // if

                    else
                    {
                        token = mevaldata.GetIDENTVALUE(tmp[i]);
                        // CHANGE IDENT TO NUMBER VALUE
                        tmp1.push_back(token);
                    } // else
                } // if

                else
                {
                    tmp1.push_back(tmp[i]);
                } // else
            } // for

            postfix1 = InfixToPostfix(tmp1);
            Calculate(postfix1, res, bopr, setres);
            if (setres == true)
            {
                newID.num = res;
                cout << newID.num << endl;
                mevaldata.PushIDENT(newID);
            } // if

            else
            {
                if (bopr)
                    cout << "true" << endl;
                else
                    cout << "false" << endl;
            } // else

            return;
        } // else if
    } // Evaluate()
};