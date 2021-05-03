#ifndef INPUT_H
#define INPUT_H 

template<class Type>
class INPUT{
 public:
    INPUT()
    virtual LinAlg::Matrix<Type> get();

 private:
    LinAlg::Matrix<Type> input;
    
};
#endif