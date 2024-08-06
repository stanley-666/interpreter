#pragma once
#include <iostream>
#include <vector>
using namespace std;
#include "ErrorManager.h"

bool IsWhiteSpace(char &ch)
{
    if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\0')
        return true;
    return false;
} // IsWhiteSpace()

bool IsDelimiter(char &ch, TokenType &type)
{
    if (ch == '+')
    {

        type = PLS;
        return true;
    } // if

    else if (ch == '-')
    {
        type = MNS;
        return true;
    } // else if

    else if (ch == '*')
    {
        type = MUL;
        return true;
    } // else if

    else if (ch == '/')
    {
        type = DIV;
        return true;
    } // else if

    else if (ch == '=')
    {
        type = EQU;
        return true;
    } // else if

    else if (ch == '<')
    {
        type = L;
        return true;
    } // else if

    else if (ch == '>')
    {
        type = G;
        return true;
    } // else if

    else if (ch == '(')
    {
        type = LEFT_PAREN;
        return true;
    } // else if

    else if (ch == ')')
    {
        type = RIGHT_PAREN;
        return true;
    } // else if

    else if (ch == ';')
    {
        type = COLON;
        return true;
    } // else if

    return false;

} // IsDelimiter()

bool Unrecognized(char ch)
{
    if (ch == '!' || ch == '@' || ch == '#' || ch == '$' || ch == '^' || ch == '~')
        return true;
    return false;
} // Unrecognized()

bool IsLetter(char ch)
{
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
} // IsLetter()

bool IsID(string &val)
{
    for (int i = 0; i < val.length(); i++)
    {
        if (!IsLetter(val[i]))
        {
            if (i > 0 && isdigit(val[i]))
                continue;
            else
                return false;
        } // if
    } // for

    return true;
} // IsID()

bool Isnum(string &val)
{
    for (int i = 0; i < val.length(); i++)
    {
        if (val[i] == '.')
        {
            for (int j = i + 1; j < val.length(); j++)
            {
                if (!isdigit(val[i]))
                    return false;
            } // for
            return true;
        } // if

        else if (!isdigit(val[i]))
        {
            return false;
        } // else if
    } // for
    return true;
} // Isnum()

class Scanner
{
private:
    char mch_in;
    char mch_buffer;
    std::vector<Token> mbuffer;
    ErrorManager &error_manager = ErrorManager::getInstance();

public:
    Scanner()
    {
        mch_in = '\0';
        mch_buffer = '\0';
    } // Scanner()

    void Print()
    {
        for (int i = 0; i < mbuffer.size(); i++)
        {
            cout << mbuffer[i].val << " ";
        } // for

        cout << endl;
    } // Print()

    void push(Token token)
    {
        mbuffer.push_back(token);
    } // Saver()

    void clear()
    {
        mch_in = '\0';
        mch_buffer = '\0';
        mbuffer.clear();
    } // Clear()

    void skip()
    { // skip a line
        char ch1 = '\0';
        if (mch_in == '\n')
            return;

        while (ch1 != '\n')
        {
            cin.get(ch1);
        } // while
    } // skip

    bool Getchar(char &ch)
    {
        ch = '\0';
        if(mch_buffer != '\0') {
            swap(ch, mch_buffer);
            return true ;
        }
            
        cin.get(ch);
        if (ch == '\0') {
            error_manager.ErrorHandling(ILLEGAL_GETCHAR,"\0");
            return false;
        }

        return true;
    } // Getchar()

    bool GetToken(Token &token)
    {
        // once an input error (unrecognized token or unexpected token) is
        // encountered, the remaining input on the same
        // line is ignored ; input-processing will resume for the next line
        mch_in = '\0';
        token.val.clear();
        token.type = UNKNOWN;
        while (Getchar(mch_in))
        { // read token one by one
            if (IsWhiteSpace(mch_in) && token.val.empty())
                continue;
               
            if(lexicalAnalyze(token))
                return true ;
            else{
                return false ;
            }
        } // while

        return true;
    } // GetToken()

    bool lexicalAnalyze(Token &token)
    {
        if(IsWhiteSpace(mch_in) && !token.val.empty())
            return true ;
  
        else if (IsDelimiter(mch_in, token.type))
        {
            if (!token.val.empty())
            {
                mch_buffer = mch_in;
                return true;
            } // if

            else
            { // empty
                if (mch_in == ';')
                {
                    token.val += mch_in;
                    // token.type = COLON;
                    return true;
                } // if

                else if (mch_in == '<')
                {
                    token.val += mch_in;
                    // token.type = L;
                    Getchar(mch_in); // read next input
                    if (mch_in == '=')
                    {
                        token.val += mch_in;
                        token.type = LT;
                        return true;
                    } // if

                    else if (mch_in == '>')
                    {
                        token.val += mch_in;
                        // token.type = NEQ;
                        return true;
                    } // else if

                    else
                    {
                        mch_buffer = mch_in;
                        return true;
                    } // else
                } // else if

                else if (mch_in == '>')
                {
                    token.val += mch_in;
                    // token.type = G;
                    Getchar(mch_in); // read next input
                    if (mch_in == '=')
                    {
                        token.val += mch_in;
                        token.type = GT;
                        return true;
                    } // if

                    else
                    {
                        mch_buffer = mch_in;
                        return true;
                    } // else
                } // else if

                else if (mch_in == '/')
                {
                    token.val += mch_in;
                    token.type = DIV;
                    Getchar(mch_in); // read next input
                    if (mch_in == '/')
                    {
                        skip();
                        token.val.clear();
                        token.type = EOFTOKEN;
                    } // if

                    else
                    {
                        mch_buffer = mch_in;
                        return true;
                    } // else

                } // else if

                else
                {
                    token.val += mch_in;
                    return true;
                } // else
            } // else
        } // else if

        else if (mch_in == ':')
        {
            token.val += mch_in;
            this->Getchar(mch_in);
            if (mch_in == '=')
            { // :=
                token.val += mch_in;
                token.type = ASSIGN;
                return true;
            } // if

            else
            { // :+
                this->skip();
                error_manager.ErrorHandling(Unrecognized_token, token.val);
                token.val.clear();
                token.type = EOFTOKEN;
            } // else
        } // else if

        else if (mch_in == '.')
        {
            mch_buffer = mch_in;
            Getchar(mch_in);
            if (isdigit(mch_in))
            {
                token.val += mch_buffer; // add '.'
                token.val += mch_in;
                mch_buffer = '\0';
                Getchar(mch_in);
                while (isdigit(mch_in))
                {
                    token.val += mch_in;
                    Getchar(mch_in);
                } // while

                token.type = NUM;
                mch_buffer = mch_in;
                return true;
            } // if

            else
            { // 123..6
                // already set token , ch_buffer
                token.val += mch_buffer;
                error_manager.ErrorHandling(Unrecognized_token, token.val);
                skip();
                token.val.clear();
                token.type = EOFTOKEN;
            } // else
        } // else if

        else if (IsLetter(mch_in))
        {
            token.val += mch_in;
            Getchar(mch_in);
            while (isdigit(mch_in) || IsLetter(mch_in))
            {
                token.val += mch_in;
                Getchar(mch_in);
            } // while

            token.type = IDENT;
            mch_buffer = mch_in;
            return true;
        } // else if

        else if (isdigit(mch_in))
        { // is a digit and read all digit
            token.val += mch_in;
            Getchar(mch_in);
            while (isdigit(mch_in))
            {
                token.val += mch_in;
                Getchar(mch_in);
            } // while

            token.type = NUM;
            if (mch_in == '.')
            {
                mch_buffer = mch_in;
                Getchar(mch_in);
                if (isdigit(mch_in))
                {
                    token.val += mch_buffer; // add '.'
                    token.val += mch_in;
                    mch_buffer = '\0';
                    Getchar(mch_in);
                    while (isdigit(mch_in))
                    {
                        token.val += mch_in;
                        Getchar(mch_in);
                    } // while

                    mch_buffer = mch_in;
                    return true;
                } // if

                else
                { // 123..6
                    return true;
                } // else
            } // if

            else
            { // other not digit char
                mch_buffer = mch_in;
                return true;
            } // else
        } // else if

        else
        {
            token.val += mch_in;
            skip();
            error_manager.ErrorHandling(Unrecognized_token, token.val);
            token.val.clear();
            token.type = EOFTOKEN;
            clear();
            return false ;
        } // else
    } 

    bool GetTokenlist(vector<Token> &tmp)
    {
        if (mbuffer.size() != 0)
        {
            // vector<Token> emptyb;
            // for (int i = 0; i < mbuffer.size(); i++)
            //     emptyb.push_back(mbuffer[i]);
            tmp = mbuffer;
            return true;
        } // if

        return false;
    } // GetTokenlist()
};