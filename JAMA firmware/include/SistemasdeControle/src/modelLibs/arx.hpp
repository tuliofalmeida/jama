#ifdef testModel
    #include "../../../headers/modelLibs/arx.h"
#else
    #include "SistemasdeControle/headers/modelLibs/arx.h"
#endif

template <typename Type>
ModelHandler::ARX<Type>::ARX(unsigned nInputpar,unsigned nOutputpar,
                             unsigned delay,
                             unsigned qdtInputVar, unsigned qdtOutputVar,
                             double sampleTime)
{
    this->maxnInOut    = nInputpar;
    if( nOutputpar > nInputpar)
        this->maxnInOut    = nOutputpar;

    this->nInputpar    = nInputpar;
    this->qdtInputVar  = qdtInputVar;
    this->nOutputpar   = nOutputpar;
    this->qdtOutputVar = qdtOutputVar;
    this->delay        = delay;
    this->step         = sampleTime;

    this->ModelCoef = LinAlg::Zeros<Type>(nInputpar*qdtInputVar + nOutputpar*qdtOutputVar, qdtOutputVar);
    this->Input = LinAlg::Zeros<Type>(qdtInputVar, nInputpar);
    this->Output = LinAlg::Zeros<Type>(qdtOutputVar, nOutputpar);
    this->output = 0;
    this->EstOutput = this->Output;
    this->nSample = delay + maxnInOut + 1;
    this->OutputLinearVector = LinAlg::Zeros<Type>(this->qdtOutputVar, this->delay + this->nOutputpar);
    this->InputLinearVector  = LinAlg::Zeros<Type>(this->qdtInputVar, this->nInputpar);
//    this->InputLinearVector  = LinAlg::Zeros<Type>(this->qdtInputVar, this->nInputpar+1);
    this->LinearVectorA = LinAlg::Zeros<Type>(this->qdtOutputVar, this->nInputpar+this->delay + this->nOutputpar);
}

template <typename Type>
ModelHandler::ARX<Type>::ARX(const ModelHandler::ARX<Type>& OtherArxModel){

    this->delay                 = OtherArxModel.delay;
    this->nInputpar             = OtherArxModel.nInputpar;
    this->qdtInputVar           = OtherArxModel.qdtInputVar;
    this->nOutputpar            = OtherArxModel.nOutputpar;
    this->qdtOutputVar          = OtherArxModel.qdtOutputVar;
    this->maxnInOut             = OtherArxModel.maxnInOut;
    this->nSample               = OtherArxModel.nSample;

    this->input                 = OtherArxModel.input;
    this->output                = OtherArxModel.output;
    this->estOutput             = OtherArxModel.estOutput;
    this->lmin                  = OtherArxModel.lmin;
    this->lmax                  = OtherArxModel.lmax;
    this->step                  = OtherArxModel.step;
    this->timeSimulation        = OtherArxModel.timeSimulation;
    this->Input                 = OtherArxModel.Input;
    this->Output                = OtherArxModel.Output;
    this->EstOutput             = OtherArxModel.EstOutput;
    this->ModelCoef             = OtherArxModel.ModelCoef;
    this->LinearVectorA         = OtherArxModel.LinearVectorA;
    this->LinearEqualityVectorB = OtherArxModel.LinearEqualityVectorB;
    this->LinearMatrixA         = OtherArxModel.LinearMatrixA;
    this->LinearEqualityB       = OtherArxModel.LinearEqualityB;
    this->InputLinearVector     = OtherArxModel.InputLinearVector;
    this->OutputLinearVector    = OtherArxModel.OutputLinearVector;
}

template<typename Type> template<typename OtherType>
ModelHandler::ARX<Type>::ARX(const ModelHandler::ARX<OtherType>& otherARXFunction)
{
    this->nInputpar    = otherARXFunction.getNumberOfInputDelays();
    this->qdtInputVar  = otherARXFunction.getNumberOfInputs();
    this->nOutputpar   = otherARXFunction.getNumberOfOutputDelays();
    this->qdtOutputVar = otherARXFunction.getNumberOfOutputs();
    this->maxnInOut    = otherARXFunction.getMaxnInOut ();
    this->nSample      = otherARXFunction.getNSample ();

    this->input                 = otherARXFunction.getSingleInput();
    this->output                = otherARXFunction.getSingleOutput();
    this->estOutput             = otherARXFunction.getSingleEstOutput();
    this->lmin                  = otherARXFunction.getLmin();
    this->lmax                  = otherARXFunction.getLmax();
    this->step                  = otherARXFunction.getStep();
    this->timeSimulation        = otherARXFunction.getTimeSimulation();
    this->delay                 = otherARXFunction.getTransportDelay();
    this->Input                 = otherARXFunction.getInputMatrix();
    this->Output                = otherARXFunction.getOutputMatrix();
    this->EstOutput             = otherARXFunction.getEstOutputMatrix();
    this->ModelCoef             = otherARXFunction.getModelCoef();
    this->LinearVectorA         = otherARXFunction.getLinearVectorA();
    this->LinearEqualityVectorB = otherARXFunction.getLinearEqualityVectorB();
    this->LinearMatrixA         = otherARXFunction.getLinearMatrixA();
    this->LinearEqualityB       = otherARXFunction.getLinearEqualityB();
    this->InputLinearVector     = otherARXFunction.getInputLinearVector();
    this->OutputLinearVector    = otherARXFunction.getOutputLinearVector();
}

template <typename Type>
ModelHandler::ARX<Type>& ModelHandler::ARX<Type>::operator= (const ModelHandler::ARX<Type>& otherARXFunction)
{
    this->delay                 = otherARXFunction.delay;
    this->nInputpar             = otherARXFunction.nInputpar;
    this->qdtInputVar           = otherARXFunction.qdtInputVar;
    this->nOutputpar            = otherARXFunction.nOutputpar;
    this->qdtOutputVar          = otherARXFunction.qdtOutputVar;
    this->maxnInOut             = otherARXFunction.maxnInOut;
    this->nSample               = otherARXFunction.nSample;

    this->input                 = otherARXFunction.input;
    this->output                = otherARXFunction.output;
    this->estOutput             = otherARXFunction.estOutput;
    this->lmin                  = otherARXFunction.lmin;
    this->lmax                  = otherARXFunction.lmax;
    this->step                  = otherARXFunction.step;
    this->timeSimulation        = otherARXFunction.timeSimulation;
    this->Input                 = otherARXFunction.Input;
    this->Output                = otherARXFunction.Output;
    this->EstOutput             = otherARXFunction.EstOutput;
    this->ModelCoef             = otherARXFunction.ModelCoef;
    this->LinearVectorA         = otherARXFunction.LinearVectorA;
    this->LinearEqualityVectorB = otherARXFunction.LinearEqualityVectorB;
    this->LinearMatrixA         = otherARXFunction.LinearMatrixA;
    this->LinearEqualityB       = otherARXFunction.LinearEqualityB;
    this->InputLinearVector     = otherARXFunction.InputLinearVector;
    this->OutputLinearVector    = otherARXFunction.OutputLinearVector;

    return *this;
}

template<typename Type> template<typename OtherARXFunctionType> // não funciona
ModelHandler::ARX<Type>& ModelHandler::ARX<Type>::operator= (const ModelHandler::ARX<OtherARXFunctionType>& otherARXFunction)
{
    this->nInputpar    = otherARXFunction.getNumberOfInputDelays();
    this->qdtInputVar  = otherARXFunction.getNumberOfInputs();
    this->nOutputpar   = otherARXFunction.getNumberOfOutputDelays();
    this->qdtOutputVar = otherARXFunction.getNumberOfOutputs();
    this->maxnInOut    = otherARXFunction.getMaxnInOut ();
    this->nSample      = otherARXFunction.getNSample ();

    this->input                 = otherARXFunction.getSingleInput();
    this->output                = otherARXFunction.getSingleOutput();
    this->estOutput             = otherARXFunction.getSingleEstOutput();
    this->lmin                  = otherARXFunction.getLmin();
    this->lmax                  = otherARXFunction.getLmax();
    this->step                  = otherARXFunction.getStep();
    this->timeSimulation        = otherARXFunction.getTimeSimulation();
    this->delay                 = otherARXFunction.getTransportDelay();
    this->Input                 = otherARXFunction.getInputMatrix();
    this->Output                = otherARXFunction.getOutputMatrix();
    this->EstOutput             = otherARXFunction.getEstOutputMatrix();
    this->ModelCoef             = otherARXFunction.getModelCoef();
    this->LinearVectorA         = otherARXFunction.getLinearVectorA();
    this->LinearEqualityVectorB = otherARXFunction.getLinearEqualityVectorB();
    this->LinearMatrixA         = otherARXFunction.getLinearMatrixA();
    this->LinearEqualityB       = otherARXFunction.getLinearEqualityB();
    this->InputLinearVector     = otherARXFunction.getInputLinearVector();
    this->OutputLinearVector    = otherARXFunction.getOutputLinearVector();

    return *this;
}

// Nesta função será avaliada a quantidade de saídas pelo número de linhas das matrizes
// Neste caso Input e Output se forem escalares corresponderão ao próximo valor
// a ser colocado no vetor de saídas ou entradas e sor uma matriz corresponderá
// a um conjunto de variáveis no instante de tempo pedido
template <typename Type>
void ModelHandler::ARX<Type>::setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> PastOutput)
{
    this->InputLinearVector  =  Input|this->InputLinearVector;
    this->OutputLinearVector =  PastOutput|this->OutputLinearVector;
    this->InputLinearVector.removeColumn(this->InputLinearVector.getNumberOfColumns()-1);
    this->OutputLinearVector.removeColumn(this->OutputLinearVector.getNumberOfColumns()-1);
    LinAlg::Matrix<Type> TempLinearVector;


    for(unsigned i = 0; i < this->OutputLinearVector.getNumberOfRows(); ++i)
        TempLinearVector = TempLinearVector | -this->OutputLinearVector.getRow(i);

    for(unsigned i = 0; i < this->InputLinearVector.getNumberOfRows(); ++i)
        TempLinearVector = TempLinearVector | this->InputLinearVector.getRow(i);

    this->LinearVectorA = TempLinearVector;
    this->LinearEqualityVectorB = PastOutput;
}

template <typename Type>
void ModelHandler::ARX<Type>::setLinearModel(LinAlg::Matrix<Type> Input,
                                   LinAlg::Matrix<Type> Output)
{
    this->Input = Input;
    this->Output = Output;

    for(nSample = 0; nSample < this->Output.getNumberOfColumns()-2; ++nSample)
    {
        this->setLinearVector( Input.getColumn(nSample), Output.getColumn(nSample));
        this->LinearMatrixA = this->LinearMatrixA || this->LinearVectorA;
        this->LinearEqualityB = this->LinearEqualityB || ~Output.getColumn(nSample+1);
    }
}

template <typename Type>
Type ModelHandler::ARX<Type>::sim(Type input)
{
    this->setLinearVector(input, this->output);
    this->output = (this->LinearVectorA*this->ModelCoef)(0,0);
    return this->output;
}

template <typename Type>
Type ModelHandler::ARX<Type>::sim(Type input, Type output)
{
    this->setLinearVector(input, output);
    this->output = (this->LinearVectorA*this->ModelCoef)(0,0);
    return this->output;
}

template <typename Type>
std::string ModelHandler::ARX<Type>::print()
{
    std::string str;
    for(unsigned nOutputVar = 1; nOutputVar <= this->qdtOutputVar; ++nOutputVar)
    {
        str += " y";
        std::stringstream ss2; ss2 << nOutputVar; str += ss2.str();
        str += "( k ) = ";

        unsigned nCoef = 1;
        bool isTheFirst = true;
        for(unsigned yPar = 1; yPar <= this->qdtOutputVar; ++yPar)
        {
            for(unsigned ny = 1; ny <= this->nOutputpar; ++ny)
            {
                if(fabs(this->ModelCoef(nCoef-1,nOutputVar-1)) < 1e-30)
                {
                    ++nCoef;
                    continue;
                }
                else if(this->ModelCoef(nCoef-1,nOutputVar-1) > 0)
                {
                    std::stringstream ss1;
                    ss1 << this->ModelCoef(nCoef-1,nOutputVar-1);
                    str += " - ";
                    str += ss1.str();
                }
                else
                {
                    std::stringstream ss1;
                    ss1 << -this->ModelCoef(nCoef-1,nOutputVar-1);
                    if(!isTheFirst)
                        str += " + ";
                    str += ss1.str();
                }
                str += " y";
                std::stringstream ss2; ss2 << yPar; str += ss2.str();
                str += "( k - ";
                std::stringstream ss3; ss3 << ny; str += ss3.str();
                str += " ) ";
                ++nCoef;
                isTheFirst = false;
            }
        }
        for(unsigned uPar = 1; uPar <= this->qdtInputVar; ++uPar)
        {
            for(unsigned nu = 1; nu <= this->nInputpar; ++nu)
            {
                if(fabs(this->ModelCoef(nCoef-1,nOutputVar-1)) < 1e-30)
                {
                    ++nCoef;
                    continue;
                }
                else if(this->ModelCoef(nCoef-1,nOutputVar-1) > 0)
                {
                    std::stringstream ss1;
                    ss1 << this->ModelCoef(nCoef-1,nOutputVar-1);
                    if(!isTheFirst)
                        str += " + ";
                    str += ss1.str();
                }
                else
                {
                    std::stringstream ss1;
                    ss1 << -this->ModelCoef(nCoef-1,nOutputVar-1);
                    str += " - ";
                    str += ss1.str();
                }
                str += " u";
                std::stringstream ss2; ss2 << uPar; str += ss2.str();
                str += "( k - ";
                std::stringstream ss3; ss3 << nu; str += ss3.str();
                str += " ) ";
                ++nCoef;
                isTheFirst = false;
            }
        }
        if(nCoef == 1)
            str += "0 ";
        str += "\n";
    }
    return str;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::ARX<Type>::sim(LinAlg::Matrix<Type> Input)
{
    this->Input  = Input;
    this->EstOutput = LinAlg::Zeros<Type>(this->qdtOutputVar,1);

    for(unsigned i = 0; i < Input.getNumberOfColumns(); ++i){
        this->setLinearVector(Input.getColumn(i),this->EstOutput.getColumn(i));
        this->EstOutput = this->EstOutput | ~(this->LinearVectorA*this->ModelCoef);
    }
    this->Output = this->EstOutput;
    return this->Output;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::ARX<Type>::sim(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output)
{
    this->Input  = Input;
    LinAlg::Matrix<Type> TempOutput = LinAlg::Zeros<Type>(this->qdtOutputVar,1);

    for(unsigned i = 0; i < Input.getNumberOfColumns(); ++i){
        this->setLinearVector(Input.getColumn(i),Output.getColumn(i));
        TempOutput = TempOutput | ~(this->LinearVectorA*this->ModelCoef);
    }
    this->Output = TempOutput;
    return this->Output;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::ARX<Type>::sim(Type lmin, Type lmax, Type step)
{
    return LinAlg::Matrix<Type>(lmin+lmax+step);
}

template <typename Type>
unsigned ModelHandler::ARX<Type>::getNumberOfInputDelays() const{
    return this->nInputpar;
}

template <typename Type>
unsigned ModelHandler::ARX<Type>::getNumberOfInputs()const {
    return this->qdtInputVar;
}

template <typename Type>
unsigned ModelHandler::ARX<Type>::getNumberOfOutputDelays() const {
    return this->nOutputpar;
}

template <typename Type>
unsigned ModelHandler::ARX<Type>::getNumberOfOutputs() const {
    return this->qdtOutputVar;
}


template <typename Type>
unsigned ModelHandler::ARX<Type>::getNumberOfVariables() const {
    return this->qdtInputVar*this->nInputpar + this->qdtOutputVar*this->nOutputpar;
}

template <typename Type>
void ModelHandler::ARX<Type>::setInitialOutputValue(const LinAlg::Matrix<Type> &Output)
{
    this->OutputLinearVector = LinAlg::Ones<Type>(this->qdtOutputVar, this->delay + this->nOutputpar);
    uint32_t zero = 0;
    for(uint32_t i = 0; i < this->qdtOutputVar; ++i)
    {
        this->OutputLinearVector = this->OutputLinearVector*Output(i,zero);
        if(i == zero)
        {
            this->output = Output(i,zero);
            this->estOutput = Output(i,zero);
        }
    }
}

template<typename Type>
std::ostream& ModelHandler::operator<< (std::ostream& output, ModelHandler::ARX<Type> arx)
{
    output << arx.print();
    return output;
}

template<typename Type>
std::string& ModelHandler::operator<< (std::string& output, ModelHandler::ARX<Type> arx)
{
    output += arx.print();
    return output;
}

