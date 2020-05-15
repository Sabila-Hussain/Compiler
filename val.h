#ifndef VAL_H
#define VAL_H

#include <string>
using namespace std;

class Val {
    int        i;
    string    s;
    enum ValType { ISINT, ISSTR, ISERR } vt;
    
public:
    Val() : i(0), vt(ISERR) {}
    Val(int i) : i(i), vt(ISINT) {}
    Val(string s) : i(0), s(s), vt(ISSTR) {}
    Val(ValType vt, string errmsg) : i(0), s(errmsg), vt(ISERR) {}
    
    ValType getVt() const { return vt; }
    
    bool isErr() const { return vt == ISERR; }
    bool isInt() const { return vt == ISINT; }
    bool isStr() const { return vt == ISSTR; }
    
    int ValInt() const {
        if( isInt() ) return i;
        throw "This Val is not an Int";
    }
    string ValString() const {
        if( isStr() ) return s;
        throw "This Val is not a Str";
    }
    
    friend ostream& operator<<(ostream& out, const Val& v) { 
        if(v.isInt()){
            out << v.ValInt();
        }
        if(v.isStr()){
            out << v.ValString();
        }
        if(v.isErr()){
            out <<  v.ValString();
        }
        return out;
    }
    
    string GetErrMsg() const {
        if( isErr() ) return s;
            throw "This Val is not an Error";
    }
   
    Val operator+(const Val& op) const {
        
        if( isInt() && op.isInt() )
            return ValInt() + op.ValInt();
        if( isStr() && op.isStr() )
            return ValString() + op.ValString();
        return Val(ISERR, "Type mismatch on operands of +");
    }
    
    Val operator-(const Val& op) const {
        if( isInt() && op.isInt() )
            return ValInt() - op.ValInt();
        return Val(ISERR, "Type mismatch on operands of -");
    }
    
    Val operator*(const Val& op) const {
        if( isInt() && op.isInt() )
            return ValInt() * op.ValInt();
        //need string*int and int*string
        if( isStr() && op.isInt() ){
            if (op.ValInt()<0){
                return Val(ISERR, "Cannot multiply string by negative int");
            }
            string phrase = "";
            for (int j = 0; j < op.i ; j++){
                phrase += s ;
            }
            return phrase; 
        }
        
        if( op.isStr() && isInt() ){
            if (ValInt() < 0){
                return Val(ISERR, "Cannot multiply string by negative int");
            }
            string phrase = "";
            for (int j = 0; j < i ; j++){
                phrase += op.s ;
            }
            return phrase; 
        }
        
            
            
        return Val(ISERR, "Type mismatch on operands of *");
    }
    
    Val operator/(const Val& op) const {
        if(op.isInt() && op.ValInt() == 0)
            return Val(ISERR, "Divide by zero error");
        
        if( isInt() && op.isInt() )
            return ValInt() / op.ValInt();
       
        return Val(ISERR, "Type mismatch on operands of /");
    }
    
    Val operator!() const {
        if(isInt()){
           int c = ValInt();
            bool isneg = false;
            if(c < 0)
            {
                isneg = true;
                c = c * -1;
            }
            int newnum = 0;
            while (c != 0){
                newnum = newnum*10 + c % 10;
                c = c/10;
            }
        
            if(isneg)
                newnum *= -1;
            return newnum; 
        }
        else if(isStr()){
            string rev = "";
            for(int i = ValString().length()-1; i >= 0 ; i --)
            {
                rev += ValString()[i];
            }
            return rev;
        }
        else
            return Val(ISERR, "Type mismatch on operands of !");
    }
    
};

#endif