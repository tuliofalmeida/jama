#ifndef MA_H
#define MA_H
#include "SistemasdeControle/headers/modelLibs/model.h"

template <class UsedType>
class MA : public Model<UsedType>
{
public:
    MA();

    void setLinearVector(LinAlg::Matrix<UsedType> Input, LinAlg::Matrix<UsedType> Output);
    void setLinearModel(LinAlg::Matrix<UsedType> Input, LinAlg::Matrix<UsedType> Output);

    void print();
    UsedType sim(UsedType input);
    UsedType sim(UsedType input, UsedType output);
    LinAlg::Matrix<UsedType> sim(LinAlg::Matrix<UsedType> Input);
    LinAlg::Matrix<UsedType> sim(LinAlg::Matrix<UsedType> x, LinAlg::Matrix<UsedType> y);
    LinAlg::Matrix<UsedType> sim(UsedType lsim, UsedType lmax, UsedType step);
};

#endif // MA_H
