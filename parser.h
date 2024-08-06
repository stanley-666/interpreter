#pragma once
#include "scanner.h"
#include "ErrorManager.h"
#include "Calculator.h"
static int uTestNum = -1;

class Parser
{
public:
    Parser()
    {
        mscan = true;
    }
    void Parse()
    {
        vector<Token> tokenlist;
        int testnum = 0;
        // cin >> uTestNum;
        int i = 0;
        Token token;
        cout << "Program starts..." << endl;
        while (1)
        { // get a token from scanner
            cout << "> ";
            if (Command(token) && Scan() && mscanner.GetTokenlist(tokenlist))
            {
                mdata.Pushlist(tokenlist);
                tokenlist.clear();
                tokenlist = mdata.Getnewest();
                meval.Evaluate(tokenlist);
            } // if

            if (!Scan())
                break;
            cout << "next token" << endl;
            token = Token();
            mscanner.clear();
        } // while
        cout << "Program exits...";
    } // Parse()
private:
    Scanner mscanner = Scanner();
    Calculator meval;
    Data mdata;
    ErrorManager &error_manager = ErrorManager::getInstance();
    bool mscan;

    void clear(Token &token)
    {
        token.val.clear();
        token.type = EOFTOKEN;
    } // Clear()

    bool Scan()
    {
        return mscan;
    } // Scan()

    bool IsFactor(Token &token)
    {
        string sign = "\0";
        if (token.type == IDENT)
        {
            mscanner.push(token);
            this->clear(token);
            return true;
        } // if

        else if (token.type == PLS || token.type == MNS)
        {
            sign = token.val;
            if (mscanner.GetToken(token))
            {
                if (token.type == NUM)
                {
                    token.val = sign + token.val;
                    token.type = NUM;
                    mscanner.push(token);
                    this->clear(token);
                    return true;
                } // if
            } // if

            return false;
        } // else if

        else if (token.type == NUM)
        {
            token.type = NUM;
            mscanner.push(token);
            this->clear(token);
            return true;
        } // else if

        else if (token.val == "(")
        {
            token.type = LEFT_PAREN;
            mscanner.push(token);
            if (mscanner.GetToken(token))
            {
                if (IsArithExp(token))
                {
                    if (token.val.size() <= 0)
                    {
                        if (!mscanner.GetToken(token))
                        {
                            return false;
                        } // if
                    } // if

                    if (token.val == ")")
                    {
                        token.type = RIGHT_PAREN;
                        mscanner.push(token);
                        this->clear(token);
                        return true;
                    } // if

                    else
                    {
                        error_manager.ErrorHandling(Unexpected_token, token.val);
                    } // else
                } // if
            } // if

            else
            {
                return false;
            } // else
        } // else if

        return false;
    } // IsF()

    bool IsTerm(Token &token)
    {
        while (IsFactor(token))
        {
            if (token.val.empty() && !mscanner.GetToken(token))
            {
                return false;
            } // if

            if (token.type == MUL || token.type == DIV)
            {
                mscanner.push(token);
                if (!mscanner.GetToken(token))
                    return false;
            } // if

            else
            {
                return true; // not * /
            } // else
        } // while

        return false;
    } // IsT()

    bool IsArithExp(Token &token)
    {
        while (IsTerm(token))
        {
            // cout << "isT" << endl;
            if (token.val.empty() && !mscanner.GetToken(token))
            {
                return false;
            } // if

            if (token.type == PLS || token.type == MNS)
            {
                mscanner.push(token);
                if (!mscanner.GetToken(token))
                    return false;
            } // if

            else
            {
                // cout << "reduced to upper level deal with token" << endl;
                return true; // not + -
            } // else
        } // while

        // cout << "is not Arith" << endl;
        return false;
    } // IsArith()

    bool B_opr(Token &token)
    {
        if (token.val == "=")
            token.type = EQU;
        else if (token.val == "<>")
            token.type = NEQ;
        else if (token.val == ">")
            token.type = G;
        else if (token.val == "<")
            token.type = L;
        else if (token.val == ">=")
            token.type = GT;
        else if (token.val == "<=")
            token.type = LT;
        else
            return false;
        return true;
    } // B_opr()

    bool NOT_IDstart(Token &token)
    {
        if (NOT_IDstartArith(token))
        {
            // cout << "NOT_IDstartArith" << endl;
            if (token.val.empty() && !mscanner.GetToken(token))
            {
                return false;
            } // if

            if (B_opr(token))
            {
                // cout << "B_opr" << endl;
                mscanner.push(token);
                if (mscanner.GetToken(token))
                {
                    if (IsArithExp(token))
                    {
                        // cout << "isArith" << endl;
                        return true;
                    } // if

                    else
                    {
                        // error
                        return false;
                    } // else
                } // if

                else
                    return false;
            } // if

            else
            {
                return true;
            } // else
        } // if

        return false;
    } // NOT_IDstart()

    bool NOT_IDstartArith(Token &token)
    {
        if (NOT_IDstartTerm(token))
        {
            if (token.val.empty() && !mscanner.GetToken(token))
            {
                return false;
            } // if

            while (token.type == PLS || token.type == MNS)
            {
                mscanner.push(token);
                if (mscanner.GetToken(token))
                {
                    if (!IsTerm(token))
                    {
                        return false;
                    } // if
                } // if

                else
                {
                    return false;
                } // else
            } // while

            return true;
        } // if

        return false;
    } // NOT_IDstartArith()

    bool NOT_IDstartTerm(Token &token)
    {
        if (NOT_IDstartFactor(token))
        {
            if (token.val.size() == 0 && !mscanner.GetToken(token))
            { // error with down level
                return false;
            }
            while (token.type == MUL || token.type == DIV)
            {
                mscanner.push(token);
                if (mscanner.GetToken(token))
                {
                    if (!IsFactor(token))
                    {
                        return false;
                    } // if
                } // if

                else
                {
                    return false;
                } // else
            } // while

            return true;
        } // if

        return false;
    } // NOT_IDstartT()

    bool NOT_IDstartFactor(Token &token)
    {
        string sign = string();
        if (token.type == PLS || token.type == MNS)
        {
            sign = token.val;
            if (mscanner.GetToken(token))
            {
                if (token.type == NUM)
                {
                    token.val = sign + token.val;
                    token.type = NUM;
                    mscanner.push(token);
                    token.val.clear();
                    return true;
                } // if

                else
                {
                    return false;
                } // else
            } // if

            else
            {
                return false;
            } // else
        } // if

        else if (token.type == NUM)
        {
            mscanner.push(token);
            token.val.clear();
            return true;
        } // else if

        else if (token.type == LEFT_PAREN)
        {
            mscanner.push(token);
            if (mscanner.GetToken(token))
            {
                if (IsArithExp(token))
                {
                    if (token.val.size() == 0 && !mscanner.GetToken(token))
                    { // error with down level
                        return false;
                    } // if

                    if (token.type == RIGHT_PAREN)
                    {
                        mscanner.push(token);
                        token.val.clear();
                        return true;
                    } // if

                    else
                    {
                        return false; // not )
                    } // else
                } // if

                else
                {
                    return false; // not arith
                } // else
            } // if
        } // else if

        else
        {
            return false;
        } // else

        return false;
    } // NOT_IDstartF()

    bool IsIDless(Token &token)
    {
        while (token.val == "+" || token.val == "-" || token.val == "*" || token.val == "/")
        {
            if (token.val == "+" || token.val == "-")
            {
                mscanner.push(token);
                if (mscanner.GetToken(token))
                {
                    if (!IsTerm(token))
                    {
                        return false;
                    } // if
                } // if

                else
                {
                    return false;
                } // else

            } // if

            else if (token.val == "*" || token.val == "/")
            {
                mscanner.push(token);
                if (mscanner.GetToken(token))
                {
                    if (!IsFactor(token))
                    {
                        return false;
                    } // if
                } // if
                else
                {
                    return false;
                } // else
            } // else if
        } // while

        if (token.val.empty())
            mscanner.GetToken(token);

        if (B_opr(token))
        {
            mscanner.push(token);
            if (!mscanner.GetToken(token))
                return false;
            if (IsArithExp(token))
            {
                return true;
            } // if

            else
            {
                return false;
            } // else

        } // if

        else
        {
            return true;
        } // else
    } // IsIDless()

    bool Command(Token &token)
    { // syntax analize
        while (!mscanner.GetToken(token))
            ;
        cout << "token.val : '" << token.val << "'" << endl;
        if (token.val == "QUIT" || token.val == "quit")
        {
            mscan = false;
            return true;
        } // if

        if (token.type == IDENT)
        { // ID
            mscanner.push(token);
            while (!mscanner.GetToken(token));
            if (token.type == ASSIGN)
            { // :=
                mscanner.push(token);
                while (!mscanner.GetToken(token))
                    ;
                if (IsArithExp(token))
                { // <Arith>
                    if (token.val.size() == 0 && !mscanner.GetToken(token))
                    {
                        return false;
                    } // if

                    if (token.val == ";")
                    { // ;
                        return true;
                    } // if

                    else
                    { // error
                        error_manager.ErrorHandling(Unexpected_token, token.val);
                        mscanner.skip();
                        mscanner.clear();
                        return false;
                    } // else
                } // if

                else
                { // error not Arith
                    error_manager.ErrorHandling(Unexpected_token, token.val);
                    mscanner.skip();
                    mscanner.clear();
                    return false;
                } // else
            } // if

            else if (IsIDless(token))
            { // <IDless>
                if (token.val.empty())
                {
                    if (!mscanner.GetToken(token))
                        return false;
                } // if

                if (token.val == ";")
                { // ;
                    return true;
                } // if

                else
                {
                    error_manager.ErrorHandling(Unexpected_token, token.val);
                    mscanner.skip();
                    mscanner.clear();
                    return false;
                } // else
            } // else if

            else
            { // error no :=
                error_manager.ErrorHandling(Unexpected_token, token.val);
                mscanner.skip();
                mscanner.clear();
                return false;
            } // else
        } // if

        else if (NOT_IDstart(token))
        { // <NOT_IDstart>
            if (token.val == ";")
            { // ;
                return true;
            } // if

            else
            { // error
                error_manager.ErrorHandling(Unexpected_token, token.val);
                mscanner.skip();
                mscanner.clear();
                return false;
            } // else
        } // else if

        else
        {
            error_manager.ErrorHandling(Unexpected_token, token.val);
            mscanner.skip();
            mscanner.clear();
            return false;
        } // else
    } // Command()
};