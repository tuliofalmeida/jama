#ifdef testMatrix
    #include "../../../../headers/primitiveLibs/LinAlg/matrix.h"
#else
    #ifdef testPolynom
        #include "../../../headers/primitiveLibs/LinAlg/matrix.h"
    #else
        #include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"
    #endif
#endif

template<typename Type>
LinAlg::Matrix<Type>::Matrix (Type Number)
{
    this->Init(1,1);
    this->mat[0][0] = Number;
}

template<typename Type>
LinAlg::Matrix<Type>::Matrix (const char* Mat)
{
    this->rows = 0;
    this->columns = 0;
    this->Init(Mat);
}


template<typename Type>
LinAlg::Matrix<Type>::Matrix (std::string Mat)
{
    this->rows = 0;
    this->columns = 0;
    this->Init(Mat);
}

template<typename Type>
LinAlg::Matrix<Type>::Matrix (uint32_t row, uint32_t column)
{
    if(row == 0 || column == 0)
    {
        this->rows = 0; this->columns = 0;
    }
    else
    {
        this->Init(row, column);
    }
}

template<typename Type>
LinAlg::Matrix<Type>::Matrix (const LinAlg::Matrix<Type>& otherMatrix)
{
    this->Init(otherMatrix.rows, otherMatrix.columns);

    for(uint32_t i = 0; i < otherMatrix.rows; i++)
        for(uint32_t j = 0; j < otherMatrix.columns; j++)
            this->mat[i][j] = otherMatrix.mat[i][j];
}

template<typename Type> template<typename OtherMatrixType>
LinAlg::Matrix<Type>::Matrix (const LinAlg::Matrix<OtherMatrixType>& otherMatrix)
{
    this->Init(otherMatrix.getNumberOfRows(), otherMatrix.getNumberOfColumns());

    for(uint32_t i = 0; i < otherMatrix.getNumberOfRows(); i++)
        for(uint32_t j = 0; j < otherMatrix.getNumberOfColumns(); j++)
            this->mat[i][j] = (Type)otherMatrix(i,j);
}

template<typename Type>
LinAlg::Matrix<Type>::~Matrix ()
{
    if(columns != 0 || rows != 0)
    {
        for(uint32_t i = 0; i < this->rows; i++)
            delete[] this->mat[i];
        delete this->mat;
    }

    this->rows = 0;
    this->columns = 0;

    this->mat = NULL;
}

template<typename Type>
void LinAlg::Matrix<Type>::removeRow(uint32_t row)
{
    if(this->rows == 1)
    {
        this->rows = 0;
        this->columns = 0;
    }
    else
    {
        LinAlg::Matrix<Type> Temp;
        for(uint32_t i = 0; i < this->rows; ++i)
                if(i != row)
                    Temp = Temp||this->getRow(i);
        *this = Temp;
    }
}

template<typename Type>
void LinAlg::Matrix<Type>::removeColumn(uint32_t column)
{
    if(this->columns == 1)
    {
        this->rows = 0;
        this->columns = 0;
    }
    else
    {
        LinAlg::Matrix<Type> Temp;
        for(uint32_t i = 0; i < this->columns; ++i)
                if(i != column)
                   Temp = Temp|this->getColumn(i);
        *this = Temp;
    }
}

template<typename Type>
void LinAlg::Matrix<Type>::Init (std::string Mat)
{
    uint32_t commas = 1, semiColons = 1, row, column, lin = 0, col = 0;
    uint32_t posComma = 0, posSemiColon = 0;
    std::string temp;

    for(uint32_t i = 0; i < Mat.length(); ++i)
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
void LinAlg::Matrix<Type>::Init (uint32_t row, uint32_t column)
{
    if(row == 0  && column == 0){
        this->rows = 0;
        this->columns = 0;
    }
    else{
        this->rows = row;
        this->columns = column;

        this->mat = new Type*[row]();
        for(uint32_t i = 0; i < row; i++)
            this->mat[i] = new Type[column]();
    }

//    LinAlg::Zeros(*this);
}

template<typename Type>
void LinAlg::Matrix<Type>::ReInit (uint32_t row, uint32_t column)
{
    LinAlg::Matrix<Type> temp(row, column);

    for(uint32_t i = 0; i < this->rows; i++)
        for(uint32_t j = 0; j < this->columns; j++)
            temp.mat[i][j] = this->mat[i][j];

    *this = temp;
}

template<typename Type>
void LinAlg::Matrix<Type>::Add (uint32_t row, uint32_t column, Type number)
{
    uint32_t greaterRow, greaterColumn;

    if(((row + 1) > this->rows) || ((column + 1) > this->columns))
    {
        if((row + 1) > this->rows)
            greaterRow = row + 1;
        else
            greaterRow = this->rows;

        if((column + 1) > this->columns)
            greaterColumn = column + 1;
        else
            greaterColumn = this->columns;

        this->ReInit(greaterRow, greaterColumn);
    }

    this->mat[row][column] = number;
}

template<typename Type> template<typename OtherMatrixType>
bool LinAlg::Matrix<Type>::CheckDimensions (const LinAlg::Matrix<OtherMatrixType>& rhs, uint32_t operation)
{
    bool checked = false;

    switch(operation)
    {
    case 0:
        if((this->rows == rhs.getNumberOfRows()) && (this->columns == rhs.getNumberOfColumns()))
            checked = true;
        else
            std::cout << "As dimensoes nao batem. Impossivel realizar operacao." << std::endl;
        break;
    case 1:
        if(this->columns == rhs.getNumberOfRows())
            checked = true;
        else
            std::cout << "As dimensoes nao batem. Impossivel realizar operacao." << std::endl;
        break;
    }

    return checked;
}

template<typename Type> template<typename OtherMatrixType>
void LinAlg::Matrix<Type>::swap (const LinAlg::Matrix<OtherMatrixType>& otherMatrix)
{
    using std::swap;

    LinAlg::Matrix<Type> temp(otherMatrix.getNumberOfRows(), otherMatrix.getNumberOfColumns());

    for(uint32_t i = 0; i < temp.rows; i++)
        for(uint32_t j = 0; j < temp.columns; j++)
            temp.mat[i][j] = otherMatrix(i, j);

    swap (rows, temp.rows);
    swap (columns, temp.columns);

    swap (mat, temp.mat);
}

template<typename Type>
uint32_t LinAlg::Matrix<Type>::getNumberOfRows () const
{
    return this->rows;
}

template<typename Type>
uint32_t LinAlg::Matrix<Type>::getNumberOfColumns () const
{
    return this->columns;
}

template<typename Type>
bool LinAlg::Matrix<Type>::isNull ()
{
    bool ret = false;

    if(this->mat == NULL)
        ret = true;

    return ret;
}

template<typename Type>
bool LinAlg::Matrix<Type>::isSquare ()
{
    bool ret = false;

    if(this->rows == this->columns)
        ret = true;

    return ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::getRow (const uint32_t &number_of_the_row) const
{
    LinAlg::Matrix<Type> ret(1, this->columns);

    for(uint32_t j = 0; j < ret.columns; j++)
        ret.mat[0][j] = this->mat[number_of_the_row][j];

    return ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::getColumn (const uint32_t &number_of_the_column) const
{
    LinAlg::Matrix<Type> ret(this->rows, 1);

    for(uint32_t i = 0; i < ret.rows; i++)
        ret.mat[i][0] = this->mat[i][number_of_the_column];

    return ret;
}

template <typename Type>
void LinAlg::Matrix<Type>::swapRows (uint32_t row_to_be_swapped, uint32_t row_to_take_place)
{
    LinAlg::Matrix<Type> aux1, aux2;

    aux1 = this->getRow(row_to_be_swapped);
    aux2 = this->getRow(row_to_take_place);

    for(uint32_t j = 0; j < this->columns; j++)
    {
        this->mat[row_to_be_swapped][j] = aux2.mat[0][j];
        this->mat[row_to_take_place][j] = aux1.mat[0][j];
    }
}

template <typename Type>
void LinAlg::Matrix<Type>::swapColumns (uint32_t column_to_be_swapped, uint32_t column_to_take_place)
{
    LinAlg::Matrix<Type>aux1, aux2;

    aux1 = this->getColumn(column_to_be_swapped);
    aux2 = this->getColumn(column_to_take_place);

    for(uint32_t i = 0; i < this->rows; i++)
    {
        this->mat[i][column_to_be_swapped] = aux2.mat[i][0];
        this->mat[i][column_to_take_place] = aux1.mat[i][0];
    }
}

template <typename Type>
uint32_t LinAlg::Matrix<Type>::length () const
{
    uint32_t ret;

    if(this->rows >= this->columns)
        ret = this->rows;
    else
        ret = this->columns;

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::size () const
{
    LinAlg::Matrix<Type> ret(1,2);

    ret(0,0) = this->rows;
    ret(0,1) = this->columns;

    return ret;
}

template<typename Type>
Type& LinAlg::Matrix<Type>::operator() (uint32_t row, uint32_t column)
{
    return this->mat[row][column];
}

template<typename Type>
Type LinAlg::Matrix<Type>::operator() (uint32_t row, uint32_t column) const
{
    return this->mat[row][column];
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator ()(uint32_t* row_uint32_terval, uint32_t* column_uint32_terval)const
{
    LinAlg::Matrix<Type> Ret;

    if(row_uint32_terval[0] < row_uint32_terval[1]){
        if(column_uint32_terval[0] < column_uint32_terval[1]){
            Ret.Init(row_uint32_terval[1] - row_uint32_terval[0] + 1, column_uint32_terval[1] - column_uint32_terval[0] + 1);
            for(uint32_t i = row_uint32_terval[0]; i <= row_uint32_terval[1]; ++i)
                for(uint32_t j = column_uint32_terval[0]; j <= column_uint32_terval[1]; ++j)
                    Ret.mat[i - row_uint32_terval[0]][j - column_uint32_terval[0]] = this->mat[i][j];

        }else{
            Ret.Init(row_uint32_terval[1] - row_uint32_terval[0] + 1, column_uint32_terval[0] - column_uint32_terval[1] + 1);
            for(uint32_t i = row_uint32_terval[0]; i <= row_uint32_terval[1]; ++i)
                for(uint32_t j = column_uint32_terval[0]; j >= column_uint32_terval[1]; --j)
                    Ret.mat[i - row_uint32_terval[0]][column_uint32_terval[0] - j] = this->mat[i][j];
        }

    } else{
        if(column_uint32_terval[0] < column_uint32_terval[1]){
            Ret.Init(row_uint32_terval[0] - row_uint32_terval[1] + 1, column_uint32_terval[1] - column_uint32_terval[0] + 1);
            for(uint32_t i = row_uint32_terval[0]; i >= row_uint32_terval[1]; --i)
                for(uint32_t j = column_uint32_terval[0]; j <= column_uint32_terval[1]; ++j)
                    Ret.mat[row_uint32_terval[0] - i][j - column_uint32_terval[0]] = this->mat[i][j];
        }else /*if(column_uint32_terval[1] > 0 && column_uint32_terval[0] < this->columns)*/{
            Ret.Init(row_uint32_terval[0] - row_uint32_terval[1] + 1, column_uint32_terval[0] - column_uint32_terval[1] + 1);
            for(uint32_t i = row_uint32_terval[0]; i >= row_uint32_terval[1]; --i)
                for(uint32_t j = column_uint32_terval[0]; j >= column_uint32_terval[1]; --j)
                    Ret.mat[row_uint32_terval[0] - i][column_uint32_terval[0] - j] = this->mat[i][j];
        }
    }

    return Ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator ()(uint32_t row, uint32_t* column_uint32_terval)const
{
    LinAlg::Matrix<Type> Ret;

//    std::cout << column_uint32_terval[0] << " , " << column_uint32_terval[1] << "\n\n";
    if(column_uint32_terval[0] <= column_uint32_terval[1]){
        Ret.Init(1, column_uint32_terval[1] - column_uint32_terval[0] + 1);
        for(uint32_t j = column_uint32_terval[0]; j <= column_uint32_terval[1]; ++j)
            Ret.mat[0][j - column_uint32_terval[0]] = this->mat[row][j];

    }else if(column_uint32_terval[1] > 0 && column_uint32_terval[0] < this->columns){
        Ret.Init(1, column_uint32_terval[0] - column_uint32_terval[1] + 1);
        for(uint32_t j = column_uint32_terval[0]; j >= column_uint32_terval[1]; --j)
            Ret.mat[0][column_uint32_terval[0] - j] = this->mat[row][j];
    }

    return Ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator ()(uint32_t* row_uint32_terval, uint32_t column)const
{
    LinAlg::Matrix<Type> Ret;

    if(row_uint32_terval[0] <= row_uint32_terval[1]){
        Ret.Init(row_uint32_terval[1] - row_uint32_terval[0] + 1, 1);
        for(uint32_t i = row_uint32_terval[0]; i <= row_uint32_terval[1]; ++i)
            Ret.mat[i - row_uint32_terval[0]][0] = this->mat[i][column];
    } else{
//        uint32_t aux = row_uint32_terval[0] - row_uint32_terval[1] + 1;

        Ret.Init(row_uint32_terval[0] - row_uint32_terval[1] + 1, 1);
        for(uint32_t i = row_uint32_terval[0]; i >= row_uint32_terval[1]; --i)
            Ret.mat[row_uint32_terval[0] - i][0] = this->mat[i][column];
    }

    return Ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator ()(uint32_t* row_uint32_terval, LinAlg::Matrix<Type> columns)const
{
    LinAlg::Matrix<Type> Ret;

    if(row_uint32_terval[0] <= row_uint32_terval[1]){
        Ret.Init(row_uint32_terval[1] - row_uint32_terval[0] + 1, columns.getNumberOfColumns());
        for(uint32_t i = row_uint32_terval[0]; i <= row_uint32_terval[1]; ++i)
            for(uint32_t j = 0; j < columns.getNumberOfColumns(); ++j)
                Ret.mat[i - row_uint32_terval[0]][j] = this->mat[i][uint32_t(columns(0,j))];
    } else{
//        uint32_t aux = row_uint32_terval[0] - row_uint32_terval[1] + 1;

        Ret.Init(row_uint32_terval[0] - row_uint32_terval[1] + 1, columns.getNumberOfColumns());
        for(uint32_t i = row_uint32_terval[0]; i >= row_uint32_terval[1]; --i)
            for(uint32_t j = 0; j < columns.getNumberOfColumns(); ++j)
                Ret.mat[row_uint32_terval[0] - i][j] = this->mat[i][uint32_t(columns(0,j))];
    }

    return Ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator ()(LinAlg::Matrix<Type> rows, uint32_t* column_uint32_terval)const
{
    LinAlg::Matrix<Type> Ret;

    if(column_uint32_terval[0] <= column_uint32_terval[1]){
        Ret.Init(rows.getNumberOfColumns(),column_uint32_terval[1] - column_uint32_terval[0] + 1);
        for(uint32_t i = 0; i < rows.getNumberOfColumns(); ++i)
            for(uint32_t j = column_uint32_terval[0]; j <= column_uint32_terval[1]; ++j)
                Ret.mat[i][j - column_uint32_terval[0]] = this->mat[uint32_t(rows(0,i))][j];
    } else{
        Ret.Init(rows.getNumberOfColumns(), column_uint32_terval[0] - column_uint32_terval[1] + 1);
        for(uint32_t i = 0; i < rows.getNumberOfColumns(); ++i)
            for(uint32_t j = column_uint32_terval[0]; j >= column_uint32_terval[1]; --j)
                Ret.mat[i][column_uint32_terval[0] - j] = this->mat[uint32_t(rows(0,i))][j];
    }


    return Ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator ()(uint32_t row, LinAlg::Matrix<Type> columns)const
{
    LinAlg::Matrix<Type> Ret;

    Ret.Init(1, columns.getNumberOfColumns());
    for(uint32_t j = 0; j < columns.getNumberOfColumns(); ++j)
        Ret.mat[0][j] = this->mat[row][uint32_t(columns(0,j))];

    return Ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator ()(LinAlg::Matrix<Type> rows, uint32_t column)const
{
    LinAlg::Matrix<Type> Ret;

    Ret.Init(rows.getNumberOfColumns(), 1);
     for(uint32_t j = 0; j < rows.getNumberOfColumns(); ++j)
        Ret.mat[j][0] = this->mat[uint32_t(rows(0,j))][column];

    return Ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator ()(LinAlg::Matrix<Type> rows, LinAlg::Matrix<Type> column)const
{
    LinAlg::Matrix<Type> Ret;

    Ret.Init(rows.getNumberOfColumns(), column.getNumberOfColumns());
    for(uint32_t i = 0; i < rows.getNumberOfColumns(); ++i)
         for(uint32_t j = 0; j < rows.getNumberOfColumns(); ++j)
            Ret.mat[i][j] = this->mat[uint32_t(rows(0,i))][uint32_t(column(0,j))];

    return Ret;
}

template<typename Type>
void LinAlg::Matrix<Type>::operator= (const char* Mat)
{
    this->Init(Mat);
}

template<typename Type>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator= (const LinAlg::Matrix<Type>& rhs) const
{
    if(rhs.rows !=0 || rhs.columns !=0)
        swap(rhs);

    return *this;
}

template<typename Type> template<typename MatrixLeftType>
void LinAlg::Matrix<Type>::operator= (LinAlg::Matrix< LinAlg::Matrix<MatrixLeftType>* > *rhs)
{
    for(uint32_t i = 0; i < this->getNumberOfColumns(); ++i )
        (*((*this)(0,i))) = (*((*rhs)(0,i)));
}

template<typename Type> template<typename OtherMatrixType>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator= (const LinAlg::Matrix<OtherMatrixType>& rhs)
{
    if(rhs.getNumberOfRows() !=0 || rhs.getNumberOfColumns() !=0)
        swap(rhs);

    return *this;
}

template<typename MatrixLeftType, typename MatrixRigthType>
LinAlg::Matrix< LinAlg::Matrix<MatrixLeftType>* >* LinAlg::operator, (LinAlg::Matrix<MatrixLeftType> &lhs, LinAlg::Matrix<MatrixRigthType> &rhs)
{
    LinAlg::Matrix< LinAlg::Matrix<MatrixLeftType>* > *A = new LinAlg::Matrix< LinAlg::Matrix<MatrixLeftType>* >(1,2);
    (*A)(0,0) = &lhs;
    (*A)(0,1) = &rhs;
    return A;
}

template<typename MatrixLeftType, typename MatrixRigthType>
LinAlg::Matrix< LinAlg::Matrix<MatrixLeftType>* >* LinAlg::operator, (LinAlg::Matrix< LinAlg::Matrix<MatrixLeftType>* >* lhs, LinAlg::Matrix<MatrixRigthType> &rhs)
{
    LinAlg::Matrix< LinAlg::Matrix<MatrixLeftType>* > *A = new LinAlg::Matrix< LinAlg::Matrix<MatrixLeftType>* >(1,(*lhs).getNumberOfColumns()+1);
    for(uint32_t i = 0; i < (*lhs).getNumberOfColumns(); ++i)
        (*A)(0,i) = (*lhs)(0,i);
    (*A)(0,(*lhs).getNumberOfColumns()) = &rhs;
    return A;
}

template<typename Type>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator+= (const Type& rhs /*scalar*/)
{
    for(uint32_t i = 0; i < this->rows; i++)
        for(uint32_t j = 0; j < this-> columns; j++)
            this->mat[i][j] += rhs;

    return *this;
}

template<typename Type> template<typename RightType>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator+= (const LinAlg::Matrix<RightType>& rhs)
{
    if(CheckDimensions(rhs, 0))
    {
        for(uint32_t i = 0; i < this->rows; i++)
            for(uint32_t j = 0; j < this->columns; j++)
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
    for(uint32_t i = 0; i < this->rows; i++)
        for(uint32_t j = 0; j < this->columns; j++)
            this->mat[i][j] *= rhs;

    return *this;
}

template<typename Type> template<typename RightType>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator*= (const LinAlg::Matrix<RightType>& rhs)
{

    if ((this->rows == 1) && (this->columns == 1))
    {
        LinAlg::Matrix<RightType> Temp = rhs;
        for(uint32_t i = 0; i < rhs.getNumberOfRows(); ++i)
            for(uint32_t j = 0; j < rhs.getNumberOfColumns(); ++j)
                Temp(i,j) = rhs(i,j) * this->mat[0][0];
        *this = Temp;
//        std::cout << ' ';
    }

    else if(CheckDimensions(rhs, 1))
    {
        Type temp;
        LinAlg::Matrix<Type> tempMat(*this);
        this->Init(this->rows, rhs.getNumberOfColumns());

        for(uint32_t i = 0; i < tempMat.rows; i++)
            for(uint32_t col = 0; col < rhs.getNumberOfColumns(); col++)
            {
                temp = 0;
                for(uint32_t j = 0; j < tempMat.columns; j++)
                    temp += tempMat.mat[i][j] * rhs(j, col);
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

template<typename Type> template<typename RightType>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator/= (const LinAlg::Matrix<RightType>& rhs)
{

    if(rhs.getNumberOfRows() == 1 && rhs.getNumberOfColumns() == 1)
        return  *this /= rhs((uint32_t)0, (uint32_t)0);
    else
        return *this *= LinAlg::Inverse<RightType>(rhs);
}

template<typename Type>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator^= (uint32_t exp)
{
    LinAlg::Matrix<Type> temp = LinAlg::Eye<Type>(this->rows);

    if(exp < 0)
    {
        if(this->rows == 1 && this->columns == 1)
        {
            this->mat[0][0] = 1/this->mat[0][0];
            return *this;
        }
        else{
            *this = LinAlg::Inverse(*this);
            //std::cout << *this << std::endl;
            exp *= -1;
        }
    }

    for(uint32_t i = 0; i < exp; ++i) {
        temp *= *this;
    }

    *this = temp;

    return *this;
}

template<typename Type>
LinAlg::Matrix<bool> LinAlg::Matrix<Type>::operator== (const Type& rhs)
{
    LinAlg::Matrix<bool> ret = *this;
    for(uint32_t i = 0; i < this->rows; ++i)
        for(uint32_t j = 0; j < this->columns; ++j)
            ret(i,j) = this->mat[i][j] == rhs;

    return ret;
}

template<typename Type>
LinAlg::Matrix<bool> LinAlg::Matrix<Type>::operator<= (const Type& rhs)
{
    LinAlg::Matrix<bool> ret = *this;
    for(uint32_t i = 0; i < this->rows; ++i)
        for(uint32_t j = 0; j < this->columns; ++j)
            ret(i,j) = this->mat[i][j] <= rhs;

    return ret;
}

template<typename Type>
LinAlg::Matrix<bool> LinAlg::Matrix<Type>::operator>= (const Type& rhs)
{
    LinAlg::Matrix<bool> ret = *this;
    for(uint32_t i = 0; i < this->rows; ++i)
        for(uint32_t j = 0; j < this->columns; ++j)
            ret(i,j) = this->mat[i][j] >= rhs;

    return ret;
}

template<typename Type>
LinAlg::Matrix<bool> LinAlg::Matrix<Type>::operator< (const Type& rhs)
{
    LinAlg::Matrix<bool> ret = *this;
    for(uint32_t i = 0; i < this->rows; ++i)
        for(uint32_t j = 0; j < this->columns; ++j)
            ret(i,j) = this->mat[i][j] < rhs;

    return ret;
}

template<typename Type>
LinAlg::Matrix<bool> LinAlg::Matrix<Type>::operator> (const Type& rhs)
{
    LinAlg::Matrix<bool> ret = *this;
    for(uint32_t i = 0; i < this->rows; ++i)
        for(uint32_t j = 0; j < this->columns; ++j)
            ret(i,j) = this->mat[i][j] > rhs;

    return ret;
}

template <typename Type>
void LinAlg::Matrix<Type>::operator<< (const LinAlg::Matrix<Type>& mat)
{

    for(uint32_t i = 0; i < this->rows; ++i)
        for(uint32_t j = 0; j < this->columns - mat.columns; ++j)
            this->mat[i][j] = this->mat[i][this->columns - mat.columns + j];

    for(uint32_t i = 0; i < this->rows; ++i)
        for(uint32_t j = 0; j < mat.columns; ++j)
            this->mat[i][this->columns - mat.columns + j] = mat.mat[i][j];
}

template <typename Type>
void LinAlg::Matrix<Type>::operator>> (LinAlg::Matrix<Type>& mat)
{

    for(uint32_t i = 0; i < mat.rows; ++i)
        for(uint32_t j = 0; j < mat.columns - this->columns; ++j)
            mat.mat[i][mat.columns - this->columns + j] = mat.mat[i][j];

    for(uint32_t i = 0; i < mat.rows; ++i)
        for(uint32_t j = 0; j < this->columns; ++j)
            mat.mat[i][j] = this->mat[i][j];
}


template <typename Type>
LinAlg::Matrix<Type> LinAlg::divPoint(const LinAlg::Matrix<Type> &A, const LinAlg::Matrix<Type> &B)
{
    LinAlg::Matrix<Type> ret = A;
    if(A.getNumberOfColumns() == B.getNumberOfColumns() && A.getNumberOfRows() == B.getNumberOfRows())
        for(uint32_t i = 0; i < A.getNumberOfRows(); ++i)
            for(uint32_t j = 0; j < A.getNumberOfColumns(); ++j)
                ret(i,j) = A(i,j)/B(i,j);
    else
        std::cout << "A dimensao das matrizes esta incorreta";

    return ret;
}

template <typename Type>
LinAlg::Matrix< LinAlg::Matrix<Type>* >* LinAlg::sort(const LinAlg::Matrix<Type> &vector)
{
    LinAlg::Matrix<Type> reorderedMatrix = vector;
    LinAlg::Matrix<Type> indices;
    if(vector.getNumberOfColumns() > 1 && vector.getNumberOfRows() == 1)
    {
        indices = LineVector<Type>(0, vector.getNumberOfColumns()-1);
        for(uint32_t i = 0; i < reorderedMatrix.getNumberOfColumns(); ++i)
            for(uint32_t j = i+1; j < reorderedMatrix.getNumberOfColumns(); ++j)
                if(reorderedMatrix(0,i) > reorderedMatrix(0,j)){
                    Type aux = reorderedMatrix(0,i);
                    reorderedMatrix(0,i) = reorderedMatrix(0,j);
                    reorderedMatrix(0,j) = aux;
                    aux = indices(0,i);
                    indices(0,i) = indices(0,j);
                    indices(0,j) = aux;
                }
    }
    else if(vector.getNumberOfColumns() == 1 && vector.getNumberOfRows() > 1)
    {
        indices = ~LineVector<Type>(0, vector.getNumberOfRows()-1);
        for(uint32_t i = 0; i < reorderedMatrix.getNumberOfRows(); ++i)
            for(uint32_t j = i+1; j < reorderedMatrix.getNumberOfRows(); ++j)
                if(reorderedMatrix(i,0) > reorderedMatrix(j,0)){
                    Type aux = reorderedMatrix(i,0);
                    reorderedMatrix(i,0) = reorderedMatrix(j,0);
                    reorderedMatrix(j,0) = aux;
                    aux = indices(i,0);
                    indices(i,0) = indices(j,0);
                    indices(j,0) = aux;
                }
    }
    else
    {
        std::cout << "Não foi possível organizar os índices! "
                     "Deveria ter apenas uma linha ou uma coluna!!"
                  << std::endl;
    }
    LinAlg::Matrix< LinAlg::Matrix<Type>* > *A = new LinAlg::Matrix< LinAlg::Matrix<Type>* >(1,2);
    (*A)(0,0) = new LinAlg::Matrix<Type>(vector.getNumberOfRows(),vector.getNumberOfColumns());
    (*A)(0,1) = new LinAlg::Matrix<Type>(vector.getNumberOfRows(),vector.getNumberOfColumns());
    (*((*A)(0,0))) = reorderedMatrix;
    (*((*A)(0,1))) = indices;
    return A;
}

template <typename Type>
LinAlg::Matrix< LinAlg::Matrix<Type>* >* LinAlg::min(const LinAlg::Matrix<Type> &vector)
{
    LinAlg::Matrix<Type> minMatrix, minIndiceMatrix;
    if(vector.getNumberOfRows() > 1)
    {
        minMatrix = LinAlg::Zeros<Type>(1, vector.getNumberOfColumns());
        minIndiceMatrix = LinAlg::Zeros<Type>(1, vector.getNumberOfColumns());

        for (uint32_t i = 0; i < vector.getNumberOfColumns(); ++i)
        {
            minMatrix(0,i) = vector(0,i);
            for (uint32_t j = 0; j < vector.getNumberOfRows(); ++j)
                if(minMatrix(0,i) > vector(j,i))
                {
                    minMatrix(0,i) = vector(j,i);
                    minIndiceMatrix(0,i) = j;
                }
        }
    }
    else if(vector.getNumberOfRows() == 1)
    {
        minMatrix = LinAlg::Zeros<Type>(1,1);
        minIndiceMatrix = LinAlg::Zeros<Type>(1,1);
        minMatrix(0,0) = vector(0,0);
        for (uint32_t j = 0; j < vector.getNumberOfColumns(); ++j)
            if(minMatrix(0,0) > vector(0,j))
            {
                minMatrix(0,0) = vector(0,j);
                minIndiceMatrix(0,0) = j;
            }
    }


    LinAlg::Matrix< LinAlg::Matrix<Type>* > *A = new LinAlg::Matrix< LinAlg::Matrix<Type>* >(1,2);
    (*A)(0,0) = new LinAlg::Matrix<Type>(vector.getNumberOfRows(),vector.getNumberOfColumns());
    (*A)(0,1) = new LinAlg::Matrix<Type>(vector.getNumberOfRows(),vector.getNumberOfColumns());
    (*((*A)(0,0))) = minMatrix;
    (*((*A)(0,1))) = minIndiceMatrix;
    return A;
}

template <typename Type>
LinAlg::Matrix< LinAlg::Matrix<Type>* >* LinAlg::max(const LinAlg::Matrix<Type> &vector)
{
    LinAlg::Matrix<Type> maxMatrix, maxIndiceMatrix;
    if(vector.getNumberOfRows() > 1)
    {
        maxMatrix = LinAlg::Zeros<Type>(1, vector.getNumberOfColumns());
        maxIndiceMatrix = LinAlg::Zeros<Type>(1, vector.getNumberOfColumns());

        for (uint32_t i = 0; i < vector.getNumberOfColumns(); ++i)
        {
            maxMatrix(uint32_t(0),i) = vector(uint32_t(0),i);
            for (uint32_t j = 0; j < vector.getNumberOfRows(); ++j)
                if(maxMatrix(0,i) < vector(j,i))
                {
                    maxMatrix(0,i) = vector(j,i);
                    maxIndiceMatrix(0,i) = j;
                }
        }
    }
    else if(vector.getNumberOfRows() == 1)
    {
        maxMatrix = LinAlg::Zeros<Type>(1,1);
        maxIndiceMatrix = LinAlg::Zeros<Type>(1,1);
        maxMatrix(uint32_t(0),uint32_t(0)) = vector(uint32_t(0),uint32_t(0));
        for (uint32_t j = 0; j < vector.getNumberOfColumns(); ++j)
            if(maxMatrix(0,0) < vector(uint32_t(0),j))
            {
                maxMatrix(0,0) = vector(uint32_t(0),j);
                maxIndiceMatrix(0,0) = j;
            }
    }


    LinAlg::Matrix< LinAlg::Matrix<Type>* > *A = new LinAlg::Matrix< LinAlg::Matrix<Type>* >(1,2);
    (*A)(0,0) = new LinAlg::Matrix<Type>(vector.getNumberOfRows(),vector.getNumberOfColumns());
    (*A)(0,1) = new LinAlg::Matrix<Type>(vector.getNumberOfRows(),vector.getNumberOfColumns());
    (*((*A)(0,0))) = maxMatrix;
    (*((*A)(0,1))) = maxIndiceMatrix;
    return A;
}

template <typename Type>
LinAlg::Matrix<Type> LinAlg::sum(const LinAlg::Matrix<Type> &mat, const bool &rowColResult)
{
    if(!rowColResult)
    {
        LinAlg::Matrix<Type> sum(1,mat.getNumberOfColumns());

        for (uint32_t i = 0; i < mat.getNumberOfRows(); ++i)
            for (uint32_t j = 0; j < mat.getNumberOfColumns(); ++j)
                sum(0,j) += mat(i,j);

        return sum;
    }
    else
    {
        LinAlg::Matrix<Type> sum(mat.getNumberOfRows(),1);

        for (uint32_t i = 0; i < mat.getNumberOfRows(); ++i)
            for (uint32_t j = 0; j < mat.getNumberOfColumns(); ++j)
                sum(i,0) += mat(i,j);

        return sum;
    }
}
//template <typename Type>
//uint32_t LinAlg::lineOfMinValue(const LinAlg::Matrix<Type> &mat)
//{
//    uint32_t minIndice = 1;
//    Type minValue = mat(1,1);
//    for (uint32_t i = 1; i <= mat.getNumberOfRows(); ++i)
//        for (uint32_t j = 1; j <= mat.getNumberOfColumns(); ++j)
//            if(minValue > mat(i,j))
//            {
//                minValue = mat(i,j);
//                minIndice = i;
//            }
//    return minIndice;
//}

//template <typename Type>
//uint32_t LinAlg::columnOfMinValue(const LinAlg::Matrix<Type> &mat)
//{
//    uint32_t minIndice = 1;
//    Type minValue = mat(1,1);
//    for (uint32_t i = 1; i <= mat.getNumberOfRows(); ++i)
//        for (uint32_t j = 1; j <= mat.getNumberOfColumns(); ++j)
//            if(minValue > mat(i,j))
//            {
//                minValue = mat(i,j);
//                minIndice = j;
//            }
//    return minIndice;
//}

//template <typename Type>
//Type LinAlg::MinValue(const LinAlg::Matrix<Type> &mat)
//{
//    Type minValue = mat(1,1);
//    for (uint32_t i = 1; i <= mat.getNumberOfRows(); ++i)
//        for (uint32_t j = 1; j <= mat.getNumberOfColumns(); ++j)
//            if(minValue > mat(i,j))
//                minValue = mat(i,j);

//    return minValue;
//}

//template <typename Type>
//uint32_t LinAlg::lineOfMaxValue(const LinAlg::Matrix<Type> &mat)
//{
//    uint32_t maxIndice = 1;
//    Type maxValue = mat(1,1);
//    for (uint32_t i = 1; i <= mat.getNumberOfRows(); ++i)
//        for (uint32_t j = 1; j <= mat.getNumberOfColumns(); ++j)
//            if(maxValue < mat(i,j))
//            {
//                maxValue = mat(i,j);
//                maxIndice = i;
//            }
//    return maxIndice;
//}

//template <typename Type>
//uint32_t LinAlg::columnOfMaxValue(const LinAlg::Matrix<Type> &mat)
//{
//    uint32_t maxIndice = 1;
//    Type maxValue = mat(1,1);
//    for (uint32_t i = 1; i <= mat.getNumberOfRows(); ++i)
//        for (uint32_t j = 1; j <= mat.getNumberOfColumns(); ++j)
//            if(maxValue < mat(i,j))
//            {
//                maxValue = mat(i,j);
//                maxIndice = j;
//            }
//    return maxIndice;
//}

//template <typename Type>
//Type LinAlg::MaxValue(const LinAlg::Matrix<Type> &mat)
//{
//    Type maxValue = mat(1,1);
//    for (uint32_t i = 1; i <= mat.getNumberOfRows(); ++i)
//        for (uint32_t j = 1; j <= mat.getNumberOfColumns(); ++j)
//            if(maxValue < mat(i,j))
//                maxValue = mat(i,j);

//    return maxValue;
//}

//template <typename Type>
//LinAlg::Matrix<Type> LinAlg::sumOfRowsElements(const LinAlg::Matrix<Type> &mat) // lembrar de implementar
//{
//    LinAlg::Matrix<Type> sum(mat.getNumberOfRows(),1);

//    for (uint32_t i = 1; i <= mat.getNumberOfRows(); ++i)
//        for (uint32_t j = 1; j <= mat.getNumberOfColumns(); ++j)
//            sum(i,1) += mat(i,j);

//    return sum;
//}

//template <typename Type>
//LinAlg::Matrix<Type> LinAlg::sumOfColumnsElements(const LinAlg::Matrix<Type> &mat) // lembrar de implementar
//{
//    LinAlg::Matrix<Type> sum(1,mat.getNumberOfColumns());

//    for (uint32_t i = 1; i <= mat.getNumberOfRows(); ++i)
//        for (uint32_t j = 1; j <= mat.getNumberOfColumns(); ++j)
//            sum(1,j) += mat(i,j);

//    return sum;
//}

template<typename Type> template<typename RightType>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator| (LinAlg::Matrix<RightType> rhs)
{
    LinAlg::Matrix<Type>ret;

    if(this->mat == NULL)
        ret = rhs;
    else
    {
        uint32_t aux = this->columns;

        if(this->rows < rhs.getNumberOfRows())
            ret.Init(rhs.getNumberOfRows(), this->columns + rhs.getNumberOfColumns());
        else
            ret.Init(this->rows, this->columns + rhs.getNumberOfColumns());

        for(uint32_t i = 0; i < this->rows; i++)
            for(uint32_t j = 0; j < this->columns; j++)
                ret.mat[i][j] = this->mat[i][j];

        for(uint32_t i = 0; i < rhs.getNumberOfRows(); i++)
            for(uint32_t j = 0; j < rhs.getNumberOfColumns(); j++)
                ret(i, aux + j) = rhs(i, j);
    }

    return ret;
}

template<typename Type> template<typename RightType>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator| (RightType rhs)
{
    return ((*this)|LinAlg::Matrix<RightType>(rhs));
}

template<typename Type> template<typename RightType>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator|| (LinAlg::Matrix<RightType> rhs)
{
    LinAlg::Matrix<Type>ret;

    if(this->mat == NULL)
        ret = rhs;
    else
    {
        uint32_t aux = this->rows;

        if(this->columns < rhs.getNumberOfColumns())
            ret.Init(this->rows + rhs.getNumberOfRows(), rhs.getNumberOfColumns());
        else
            ret.Init(this->rows + rhs.getNumberOfRows(), this->columns);

        for(uint32_t i = 0; i < this->rows; i++)
            for(uint32_t j = 0; j < this->columns; j++)
                ret.mat[i][j] = this->mat[i][j];

        for(uint32_t i = 0; i < rhs.getNumberOfRows(); i++)
            for(uint32_t j = 0; j < rhs.getNumberOfColumns(); j++)
                ret(i + aux, j) = rhs(i, j);
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

    for(uint32_t i = 0; i < temp.getNumberOfRows(); i++)
        for(uint32_t j = 0; j < temp.getNumberOfColumns(); j++)
            temp(i, j) *= -1;

    return temp;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::operator~ (LinAlg::Matrix<Type> mat)
{
    LinAlg::Matrix<Type> temp(mat.getNumberOfColumns(), mat.getNumberOfRows());

    for(uint32_t i = 0; i < mat.getNumberOfRows(); i++)
        for(uint32_t j = 0; j < mat.getNumberOfColumns(); j++)
            temp(j, i) = mat(i, j);

    return temp;
}

template<typename Type>
std::ostream& LinAlg::operator<< (std::ostream& output, const LinAlg::Matrix<Type> mat)
{
    if(mat.getNumberOfColumns() == 0){
        return output;
    }

    for(uint32_t i = 0; i < mat.getNumberOfRows(); i++)
    {
        for(uint32_t j = 0; j < mat.getNumberOfColumns(); j++)
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

    for(uint32_t i = 0; i < mat.getNumberOfRows(); i++)
    {
        for(uint32_t j = 0; j < mat.getNumberOfColumns(); j++)
        {
            if(mat(i, j) != 0)
                output << std::setw(2*coutPrecision+1) << std::setprecision(coutPrecision) << std::fixed << mat(i, j);
            else
                output << std::setw(2*coutPrecision+1) << std::setprecision(0) << std::fixed << mat(i, j);

            if(j != mat.getNumberOfColumns()-1)
                output << ',';
        }

        if(i != mat.getNumberOfRows())
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

//template<typename Type>
//bool LinAlg::operator== (const LinAlg::Matrix<Type>& lhs, const LinAlg::Matrix<Type>& rhs)
//{
//    bool ret = true;

//    if((lhs.getNumberOfRows() == rhs.getNumberOfRows()) && (lhs.getNumberOfColumns() && rhs.getNumberOfColumns()))
//    {
//        for(uint32_t i = 1; i <= lhs.getNumberOfRows(); i++)
//            for(uint32_t j = 1; j <= lhs.getNumberOfColumns(); j++)
//                if(!(lhs(i, j) == rhs(i, j)))
//                {
//                    ret = false;
//                    break;
//                }
//    }
//    else
//        ret = false;

//    return ret;
//}

//template<typename Type>
//void LinAlg::Zeros(Matrix<Type>& Mat)
//{
//    for(uint32_t i = 1; i <= Mat.getNumberOfRows(); i++)
//        for(uint32_t j = 1; j <= Mat.getNumberOfColumns(); j++)
//            if(typeid(Mat(i, j)) == typeid(double) || typeid(Mat(i, j)) == typeid(uint32_t) || typeid(Mat(i, j)) == typeid(float) || typeid(Mat(i, j)) == typeid(uint32_t))
//                Mat(i, j) = 0;
//}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Zeros (uint32_t rows, uint32_t columns)
{
    return LinAlg::Matrix<Type>(rows, columns);

}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Eye (uint32_t dimension)
{
    LinAlg::Matrix<Type> Ret(dimension, dimension);

    for(uint32_t i = 0; i < dimension; i++)
        for(uint32_t j = 0; j < dimension; j++)
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
    LinAlg::Matrix<Type> Ret(1,uint32_t((to-from)/step) + 1);
    uint32_t j = 0;
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
LinAlg::Matrix<Type> LinAlg::Ones(uint32_t rows, uint32_t columns)
{
    LinAlg::Matrix<Type> temp(rows, columns);

    for(uint32_t i = 0; i < temp.getNumberOfRows(); i++)
        for(uint32_t j = 0; j < temp.getNumberOfColumns(); j++)
            temp(i, j) = 1;

    return temp;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Random(uint32_t rows, uint32_t columns)
{
    LinAlg::Matrix<Type> mat(rows, columns);

    for(uint32_t i = 0; i < rows; ++i)
        for(uint32_t j = 0; j < columns; ++j)
            mat(i, j) = (Type)(((double)(rand()%100))/100.0);

    return mat;
}

template<typename Type>
LinAlg::Matrix<Type> diff(LinAlg::Matrix<Type> mat)
{
    LinAlg::Matrix<Type> ret(mat.getNumberOfRows(), mat.getNumberOfColumns()-1);
    for(uint32_t i = 0; i < mat.getNumberOfColumns()-1; ++i)
        for(uint32_t j = 0; j < mat.getNumberOfRows(); ++j)
            ret(j,i) = mat(j,i+1) - mat(j,i);
    return ret;

}

template<typename Type>
Type LinAlg::Determinant(const LinAlg::Matrix<Type>& mat)
{
    Type determinant = 0;
    uint32_t rows = mat.getNumberOfRows(), columns = mat.getNumberOfColumns(), aux1, aux2;
    LinAlg::Matrix<Type> temp(rows - 1, columns - 1);


    if(rows != columns)
    {
        determinant = 0;
        std::cout << "Operacao disponivel somente para matrizes quadradas.";
    }
    else if(rows == 1)
        determinant = mat((uint32_t)0, (uint32_t)0);
    else if(rows == 2){
        determinant = mat((uint32_t)0, (uint32_t)0)*mat((uint32_t)1, (uint32_t)1) - mat((uint32_t)0, (uint32_t)1)*mat((uint32_t)1, (uint32_t)0);
//        std::cout << mat(0,0) << std::endl;
//        std::cout << mat(1,0) << std::endl;
//        std::cout << mat(0,1) << std::endl;
//        std::cout << mat(1,1) << std::endl;
    }
    else
    {
        for(uint32_t k = 0; k < rows; k++)
        {
            aux1 = 0;
            aux2 = 0;
            for(uint32_t i = 1; i < rows; i++)
            {
                for(uint32_t j = 0; j < rows; j++)
                {
                    if(!(j == k))
                    {
                        temp(aux1, aux2) = mat(i, j);
                        aux2++;
                    }

                    if(aux2 == rows - 1)
                    {
                        aux1++;
                        aux2 = 0;
                    }
                }
            }

            determinant += pow( -1, k)*mat((uint32_t)0, k) * LinAlg::Determinant(temp);
        }
    }

    return determinant;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Cofactor(const LinAlg::Matrix<Type>& mat)
{
    uint32_t rows = mat.getNumberOfRows(), columns = mat.getNumberOfColumns(), aux1, aux2;
    LinAlg::Matrix<Type> temp(rows - 1, columns - 1), ret(rows, columns);

    if(rows != columns)
    {
        ret = LinAlg::Zeros<Type>(0,0);
        std::cout << "Operacao disponivel somente para matrizes quadradas.";
    }
    else if(rows == 2)
    {
        ret((uint32_t)0, (uint32_t)0) = mat((uint32_t)1, (uint32_t)1);
        ret((uint32_t)1, (uint32_t)1) = mat((uint32_t)0, (uint32_t)0);
        ret((uint32_t)0, (uint32_t)1) = -mat((uint32_t)1, (uint32_t)0);
        ret((uint32_t)1, (uint32_t)0) = -mat((uint32_t)0, (uint32_t)1);
    }
    else
    {
        for(uint32_t j = 0; j < rows; j++)
            for(uint32_t i = 0; i < rows; i++)
            {
                aux1 = 1;

                for(uint32_t m = 0; m < rows; m++)
                {
                    if(!(m == i))
                    {
                        aux2 = 1;

                        for(uint32_t n = 0; n < rows; n++)
                        {
                            if(!(n == j))
                            {
                                temp(aux1, aux2) = mat(m, n);
                                aux2++;
                            }
                        }
                        aux1++;
                    }
                }

                ret(i, j) = pow(-1, i + j)*LinAlg::Determinant<Type>(temp);
            }
    }

    return ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Inverse(const LinAlg::Matrix<Type>& mat)
{
    Type determinant = LinAlg::Determinant(mat);
    uint32_t rows = mat.getNumberOfRows(), columns = mat.getNumberOfColumns();
    LinAlg::Matrix<Type> ret(rows, columns);

    if(rows != columns)
        std::cout << "Operacao disponivel somente para matrizes quadradas.";
    else if(rows == 1 && columns == 1)
        ret((uint32_t)0,(uint32_t)0) = Type(1)/mat((uint32_t)0,(uint32_t)0);
    else if( determinant == Type(0.0))
        std::cout << "Impossivel inverter, determinante igual a 0.";
    else
    {
        ret = LinAlg::Cofactor(mat);
        ret = (~ret)/determinant;
    }

    return ret;
}

template<typename Type>
void LinAlg::Print(const Matrix<Type>& mat)
{
  std::cout << std::endl;

  for(uint32_t i = 0; i < mat.getNumberOfRows(); i++)
  {
    for(uint32_t j = 0; j < mat.getNumberOfColumns(); j++)
        std::cout << std::setw(10) << mat(i, j) << ' ';

    std::cout << std::endl;
  }
}

template<typename Type>
bool LinAlg::isEqual(const LinAlg::Matrix<Type>& lMat, const LinAlg::Matrix<Type>& rMat)
{
    if(lMat.getNumberOfRows() != rMat.getNumberOfRows() || lMat.getNumberOfColumns() != rMat.getNumberOfColumns())
        return false;
    else
    {
        for(uint32_t i = 0; i < lMat.getNumberOfRows(); i++)
        {
          for(uint32_t j = 0; j < lMat.getNumberOfColumns(); j++)
          {
            if(lMat(i,j) != rMat(i,j))
                return false;
          }
        }
    }
    return true;
}

template<typename Type, typename otherType>
bool LinAlg::isEqual(const LinAlg::Matrix<Type>& lMat, const LinAlg::Matrix<otherType>& rMat, Type tol)
{
    if(lMat.getNumberOfRows() != rMat.getNumberOfRows() || lMat.getNumberOfColumns() != rMat.getNumberOfColumns())
        return false;
    else
    {
        for(uint32_t i = 0; i < lMat.getNumberOfRows(); i++)
        {
          for(uint32_t j = 0; j < lMat.getNumberOfColumns(); j++)
          {
            if(fabs(lMat(i,j) - rMat(i,j)) > tol)
                return false;
          }
        }
    }
    return true;
}
