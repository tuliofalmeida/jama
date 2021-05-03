#ifndef OUTPUT_H
#define OUTPUT_H

template <class Type>
class OUTPUT
{
public:
    OUTPUT();
    virtual void set(const LinAlg::Matrix<Type> &input) = 0;
    LinAlg::Matrix<Type> &getOutput() const;

private:
    LinAlg::Matrix<Type> output;
};
#endif