#include "matrix.h"

template<typename Type>
LinAlg::Matrix<Type>::Matrix (Type Number)
{
    this->mat = std::deque<std::deque<Type>>(1,std::deque<Type>(1,Number));
}

template<typename Type>
LinAlg::Matrix<Type>::Matrix (const char* Mat)
{
    this->Init (Mat);
}


template<typename Type>
LinAlg::Matrix<Type>::Matrix (std::string Mat)
{
    this->Init (Mat);
}

template<typename Type>
LinAlg::Matrix<Type>::Matrix (unsigned row, unsigned column)
{
    this->Init (row, column);
}

template<typename Type>
LinAlg::Matrix<Type>::Matrix (const LinAlg::Matrix<Type>& otherMatrix)
{
    this->Init(otherMatrix.getNumberOfRows(),otherMatrix.getNumberOfColumns());
    for(unsigned i = 0; i < this->mat.size(); ++i)
        for(unsigned j = 0; j < this->mat[i].size(); ++j)
            this->mat[i][j] = otherMatrix(i,j);
}

template<typename Type> template<typename OtherMatrixType>
LinAlg::Matrix<Type>::Matrix (const LinAlg::Matrix<OtherMatrixType>& otherMatrix)
{
    this->Init(otherMatrix.getNumberOfRows(),otherMatrix.getNumberOfColumns());
    for(unsigned i = 0; i < this->mat.size(); ++i)
        for(unsigned j = 0; j < this->mat[i].size(); ++j)
            this->mat[i][j] = otherMatrix(i,j);
}

template<typename Type>
LinAlg::Matrix<Type>::~Matrix ()
{
//    for(unsigned i = 0; i < this->mat.size(); ++i)
//        if(!this->mat[i].empty())
//            this->mat[i].~deque();
//    if(!this->mat.empty())
////        this->mat.clear();
//        this->mat.~deque();
}

template<typename Type>
void LinAlg::Matrix<Type>::removeRow(unsigned row)
{
    this->mat.erase(this->mat.begin()+row);
}

template<typename Type>
void LinAlg::Matrix<Type>::removeColumn(unsigned column)
{
    for(unsigned i = 0; i < this->mat.size(); ++i)
        this->mat[i].erase(this->mat[i].begin()+column);
    if(this->getNumberOfColumns() == 0)
        this->mat.clear();
}

template<typename Type>
void LinAlg::Matrix<Type>::Init (std::string Mat)
{
    unsigned commas = 1, semiColons = 1, row, column, lin = 0, col = 0;
    int posComma = 0, posSemiColon = 0;
    std::string temp;

    for(unsigned i = 0; i < Mat.length(); ++i)
    {
        if(Mat[i] == ';')
            semiColons += 1;
        else if (Mat[i] == ',')
            commas += 1;
    }

    row = semiColons;
    column = (commas + semiColons - 1)/semiColons;

    this->Init(row, column);

    while(!(Mat.empty()))
    {
        posSemiColon = Mat.find(";");
        if(posSemiColon != -1)
            temp = Mat.substr(0, posSemiColon);
        else
        {
            temp = Mat;
            posSemiColon = Mat.length();
        }

        while(!(temp.empty()))
        {
            posComma = temp.find(",");
            if (posComma == -1)
                posComma = temp.length();

            std::string temp2 = temp.substr(0, posComma);
            Type number;
            std::stringstream ss(temp2);

            if(temp2 == "")
                number = 0;
            else
                ss >> number;

            this->mat[lin][col] =  number;
            temp.erase(0, posComma + 1);
            col++;
        }

        Mat.erase(0, posSemiColon + 1);
        col = 0;
        lin++;
    }
}

template<typename Type>
void LinAlg::Matrix<Type>::Init (unsigned row, unsigned column)
{
    this->mat = std::deque<std::deque<Type>>(row,std::deque<Type>(column,Type()));
}

template<typename Type> template<typename OtherMatrixType>
bool LinAlg::Matrix<Type>::CheckDimensions (const LinAlg::Matrix<OtherMatrixType>& rhs, unsigned operation)
{
    bool checked = false;

    switch(operation)
    {
    case 0:
        if((this->getNumberOfRows() == rhs.getNumberOfRows()) && (this->getNumberOfColumns() == rhs.getNumberOfColumns()))
            checked = true;
        else
            std::cout << "As dimensoes nao batem. Impossivel realizar operacao." << std::endl;
        break;
    case 1:
        if(this->getNumberOfColumns() == rhs.getNumberOfRows())
            checked = true;
        else
            std::cout << "As dimensoes nao batem. Impossivel realizar operacao." << std::endl;
        break;
    }

    return checked;
}

template<typename Type>
unsigned LinAlg::Matrix<Type>::getNumberOfRows () const
{
    if(!this->mat.empty())
        return this->mat.size();
    else
        return 0;
}

template<typename Type>
unsigned LinAlg::Matrix<Type>::getNumberOfColumns () const
{
    if(!this->mat.empty())
        return this->mat[0].size();
    else
        return 0;
}

template<typename Type>
bool LinAlg::Matrix<Type>::isNull ()
{
    return this->mat.empty();
}

template<typename Type>
bool LinAlg::Matrix<Type>::isSquare ()
{
    bool ret = false;

    if(this->getNumberOfRows() == this->getNumberOfColumns())
        ret = true;

    return ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::getRow (const unsigned &number_of_the_row) const
{
    LinAlg::Matrix<Type> ret(1, this->getNumberOfColumns());

    for(unsigned j = 0; j < ret.getNumberOfColumns(); j++)
        ret.mat[0][j] = this->mat[number_of_the_row][j];

    return ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::getColumn (const unsigned &number_of_the_column) const
{
    LinAlg::Matrix<Type> ret(this->getNumberOfRows(), 1);

    for(unsigned i = 0; i < ret.getNumberOfRows(); i++)
        ret.mat[i][0] = this->mat[i][number_of_the_column];

    return ret;
}


template <typename Type>
unsigned LinAlg::Matrix<Type>::length () const
{
    unsigned ret;

    if(this->getNumberOfRows() >= this->getNumberOfColumns())
        ret = this->getNumberOfRows();
    else
        ret = this->getNumberOfColumns();

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::size () const
{
    LinAlg::Matrix<Type> ret(1,2);

    ret(0,0) = this->getNumberOfRows();
    ret(0,1) = this->getNumberOfColumns();

    return ret;
}

template<typename Type>
Type& LinAlg::Matrix<Type>::operator() (unsigned row, unsigned column)
{
    return this->mat[row][column];
}

template<typename Type>
Type LinAlg::Matrix<Type>::operator() (unsigned row, unsigned column) const
{
    return this->mat[row][column];
}


template<typename Type>
void LinAlg::Matrix<Type>::operator= (const char* Mat)
{
    this->Init(Mat);
}

template<typename Type>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator= (const LinAlg::Matrix<Type>& rhs) const
{
    if(rhs.getNumberORows() !=0 || rhs.getNumberOfColumns() !=0)
    {
        this->Init(rhs.getNumberOfRows(),rhs.getNumberOfColumns());
        for(unsigned i = 0; i < this->mat.size(); ++i)
            for(unsigned j = 0; j < this->mat[i].size(); ++j)
                this->mat[i][j] = rhs(i,j);
    }

    return *this;
}

template<typename Type> template<typename OtherMatrixType>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator= (const LinAlg::Matrix<OtherMatrixType>& rhs)
{
    if(rhs.getNumberOfRows() !=0 || rhs.getNumberOfColumns() !=0)
    {
        this->Init(rhs.getNumberOfRows(),rhs.getNumberOfColumns());
        for(unsigned i = 0; i < this->mat.size(); ++i)
            for(unsigned j = 0; j < this->mat[i].size(); ++j)
                this->mat[i][j] = (Type)rhs(i,j);
    }

    return *this;
}


template<typename Type>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator+= (const Type& rhs /*scalar*/)
{
    for(unsigned i = 0; i < this->getNumberOfRows(); i++)
        for(unsigned j = 0; j < this->getNumberOfColumns(); j++)
            this->mat[i][j] += rhs;

    return *this;
}

template<typename Type> template<typename RightType>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator+= (const LinAlg::Matrix<RightType>& rhs)
{
    if(CheckDimensions(rhs, 0))
    {
        for(unsigned i = 0; i < this->getNumberOfRows(); i++)
            for(unsigned j = 0; j < this->getNumberOfColumns(); j++)
                this->mat[i][j] += rhs(i, j);
    }

    return *this;
}

template<typename Type>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator-= (const Type& rhs /*scalar*/)
{
    return *this += -1*rhs;
}


template<typename Type> template<typename RightType>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator-= (const LinAlg::Matrix<RightType>& rhs)
{
    return *this += -rhs;
}

template<typename Type>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator*= (const Type& rhs /*scalar*/)
{
    for(unsigned i = 0; i < this->getNumberOfRows(); i++)
        for(unsigned j = 0; j < this->getNumberOfColumns(); j++)
            this->mat[i][j] *= rhs;

    return *this;
}

template<typename Type> template<typename RightType>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator*= (const LinAlg::Matrix<RightType>& rhs)
{

    if ((this->getNumberOfRows() == 1) && (this->getNumberOfColumns() == 1))
    {
        LinAlg::Matrix<RightType> Temp = rhs;
        for(unsigned i = 0; i < rhs.getNumberOfRows(); ++i)
            for(unsigned j = 0; j < rhs.getNumberOfColumns(); ++j)
                Temp(i,j) = rhs(i,j) * this->mat[0][0];
        *this = Temp;
//        std::cout << ' ';
    }

    else if(CheckDimensions(rhs, 1))
    {
        Type temp;
        LinAlg::Matrix<Type> tempMat(*this);
        this->Init(this->getNumberOfRows(), rhs.getNumberOfColumns());

        for(unsigned i = 0; i < tempMat.getNumberOfRows(); ++i)
            for(unsigned col = 0; col < rhs.getNumberOfColumns(); ++col)
            {
                temp = 0;
                for(unsigned j = 0; j < tempMat.getNumberOfColumns(); ++j)
                    temp += tempMat.mat[i][j] * rhs(j,col);
                this->mat[i][col] = temp;
            }
    }

    return *this;
}

template<typename Type>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator/= (const Type& rhs)
{
    return *this *= 1/rhs;
}

template <typename Type>
void LinAlg::Matrix<Type>::operator<< (const LinAlg::Matrix<Type>& mat)
{
    for(unsigned i = 0; i < mat.getNumberOfRows(); ++i)
    {
        this->mat[i].pop_front();
        this->mat[i].push_back(mat(i,0));
        for(unsigned j = 1; j < mat.getNumberOfColumns(); ++j)
            this->mat[i][j] = mat(i,j);
    }
}

template <typename Type>
void LinAlg::Matrix<Type>::operator>> (LinAlg::Matrix<Type>& mat)
{
    for(unsigned i = 0; i < mat.getNumberOfRows(); ++i)
    {
        mat.mat[i].pop_back();
        mat.mat[i].push_front(this->mat[i][0]);
        for(unsigned j = 1; j < this->getNumberOfColumns(); ++j)
            mat(i,j) = this->mat[i][j];
    }
}


template<typename Type> template<typename RightType>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator| (LinAlg::Matrix<RightType> rhs)
{
    if(!this->mat.size())
        return rhs;
    else
    {
        LinAlg::Matrix<Type> ret = *this;
        for(unsigned i = 0; i < rhs.getNumberOfRows(); ++i)
        {
            for(unsigned j = 0; j < rhs.getNumberOfColumns(); ++j)
                ret.mat[i].push_back(rhs(i,j));
        }
        return ret;
    }
}

template<typename Type> template<typename RightType>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator| (RightType rhs)
{
    return ((*this)|LinAlg::Matrix<RightType>(rhs));
}

template<typename Type> template<typename RightType>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator|| (LinAlg::Matrix<RightType> rhs)
{
    LinAlg::Matrix<Type> ret = *this;
    unsigned tam = ret.mat.size();
    for(unsigned i = 0; i < rhs.getNumberOfRows(); ++i)
    {
        ret.mat.push_back(std::deque<Type>(rhs.getNumberOfColumns(),rhs(i,0)));
        for(unsigned j = 1; j < rhs.getNumberOfColumns(); ++j)
            ret.mat[tam+i][j] = rhs(i,j);
    }

    return ret;
}

template<typename Type> template<typename RightType>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator|| (RightType rhs)
{
    return ((*this)||LinAlg::Matrix<RightType>(rhs));
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::operator- (const LinAlg::Matrix<Type>& mat)
{
    LinAlg::Matrix<Type> temp(mat);

    for(unsigned i = 0; i < temp.getNumberOfRows(); i++)
        for(unsigned j = 0; j < temp.getNumberOfColumns(); ++j)
            temp(i, j) *= -1;

    return temp;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::operator~ (LinAlg::Matrix<Type> mat)
{
    LinAlg::Matrix<Type> temp(mat.getNumberOfColumns(), mat.getNumberOfRows());

    for(unsigned i = 0; i < mat.getNumberOfRows(); i++)
        for(unsigned j = 0; j < mat.getNumberOfColumns(); j++)
            temp(j, i) = mat(i, j);

    return temp;
}

template<typename Type>
std::ostream& LinAlg::operator<< (std::ostream& output, const LinAlg::Matrix<Type> mat)
{
    if(mat.getNumberOfColumns() == 0){
        return output;
    }

    for(unsigned i = 0; i < mat.getNumberOfRows(); ++i)
    {
        for(unsigned j = 0; j < mat.getNumberOfColumns(); ++j)
            if(mat(i, j) != 0)
                output << std::setw(2*coutPrecision+1) << std::setprecision(coutPrecision) << std::fixed << mat(i, j) << ' ';
            else
                output << std::setw(2*coutPrecision+1) << std::setprecision(0) << std::fixed << mat(i, j) << ' ';

        output << std::endl;
    }

    return output;
}

template<typename Type>
std::ostream& LinAlg::operator<<= (std::ostream& output, const LinAlg::Matrix<Type> mat)
{
    if(mat.getNumberOfColumns() == 0){
        return output;
    }

    for(unsigned i = 0; i < mat.getNumberOfRows(); ++i)
    {
        for(unsigned j = 0; j < mat.getNumberOfColumns(); ++j)
        {
            if(mat(i, j) != 0)
                output << std::setw(2*coutPrecision+1) << std::setprecision(coutPrecision) << std::fixed << mat(i, j);
            else
                output << std::setw(2*coutPrecision+1) << std::setprecision(0) << std::fixed << mat(i, j);

            if(j != mat.getNumberOfColumns()-1)
                output << ',';
        }

        if(i != mat.getNumberOfRows()-1)
            output << ';';
    }

    return output;
}

template<typename Type>
std::istream& LinAlg::operator>> (std::istream& input, LinAlg::Matrix<Type>& mat)
{
    std::string temp;

    input >> temp;
    mat = temp;

    return input;
}

template<typename Type>
std::string& LinAlg::operator<< (std::string& output, const LinAlg::Matrix<Type> mat)
{
    std::stringstream ss;
    ss << mat;
    output += ss.str();
    return output;
}

template<typename Type>
std::string& LinAlg::operator<<= (std::string& output, const LinAlg::Matrix<Type> mat)
{
    std::stringstream ss;
    ss <<= mat;
    output += ss.str();
    return output;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Zeros (unsigned rows, unsigned columns)
{
    return LinAlg::Matrix<Type>(rows, columns);

}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Eye (unsigned dimension)
{
    LinAlg::Matrix<Type> Ret(dimension, dimension);

    for(unsigned i = 0; i < dimension; i++)
        for(unsigned j = 0; j < dimension; j++)
            {
                if( i == j)
                    Ret(i, j) = 1;
                else
                    Ret(i, j) = 0;
            }

    return Ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::LineVector (Type from, Type to, Type step)
{
    LinAlg::Matrix<Type> Ret(1,unsigned((to-from)/step) + 1);
    unsigned j = 0;
    if(step > 0)
        for(Type i = from; i <= to; i+= step)
        {
            Ret(0,j) = i;
            ++j;
        }
    else
        for(Type i = from; i >= to; i+= step)
        {
            Ret(0,j) = i;
            ++j;
        }
    return Ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Ones(unsigned rows, unsigned columns)
{
    LinAlg::Matrix<Type> temp(rows, columns);

    for(unsigned i = 0; i < temp.getNumberOfRows(); ++i)
        for(unsigned j = 0; j < temp.getNumberOfColumns(); ++j)
            temp(i, j) = 1;

    return temp;
}

template<typename Type,typename otherType>
bool LinAlg::isEqual(const LinAlg::Matrix<Type> &mat1, const LinAlg::Matrix<otherType> &mat2, const Type &tolerance)
{
    for(unsigned i = 0; i < mat1.getNumberOfRows(); ++i)
        for(unsigned j = 0; j < mat1.getNumberOfColumns(); ++j)
            if(fabs(mat1(i,j) - mat2(i,j)) > tolerance)
                return 0;
    return 1;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::linSolve(LinAlg::Matrix<Type> A)
{
    if(A.getNumberOfRows() == 1 && A.getNumberOfColumns() == 2)
        return LinAlg::Matrix<Type>(A(0,1)/A(0,0));

    unsigned nLin = A.getNumberOfRows();
    unsigned nCol = A.getNumberOfColumns();

    for(unsigned i = 0; i < nCol - 2; ++i)
    {
        for(unsigned j = i; j < nLin; ++j)
        {
            Type m = A(j,i)/A(i,i);
            for(unsigned k = 0; k < nCol; ++k)
                A(j,k) = A(j,k) - m*A(i,k);
        }
    }

    LinAlg::Matrix<Type> X(nLin,1);
    for(unsigned i = nLin-1; i >= 0; --i)
    {
        Type sum = Type();
        for(unsigned j = i; j < nCol-1; ++j)
            sum += A(i,j)*X(j,0);
        X(i,0) = (A(i,nCol)-sum)/A(i,i);
    }
    return X;
}