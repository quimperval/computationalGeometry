#ifndef INTEGER_H
#define INTEGER_H

class Integer{
    private: 
    int myvalue;
    public: 
        Integer(int value){
            this->myvalue = value;
        }
        ~Integer(){
            
        }
        
        int getValue(){
            return this->myvalue;
        }
        
};

#endif INTEGER_H