#ifdef testControl
    #include "../../../headers/controlLibs/ExplicityController.h"
#else
    #include "SistemasdeControle/headers/controlLibs/ExplicityController.h"
#endif

template<typename Type>
void ControlHandler::ExplicityController<Type>::setConstraints(const LinAlg::Matrix<Type> *Constraints, const unsigned &size)
{
    this->Constraints = new LinAlg::Matrix<Type>[size];
    for(unsigned i = 0; i < size; ++i)
        this->Constraints[i] = Constraints[i];
    this->quantityOfRegions = size;
}

template<typename Type>
void ControlHandler::ExplicityController<Type>::setControllerParameters(const LinAlg::Matrix<Type> *controllers, const unsigned &size)
{
    this->controllerParameters = new LinAlg::Matrix<Type>[size];
    for(unsigned i = 0; i < size; ++i)
        this->controllerParameters[i] = controllers[i];
    this->quantityOfRegions = size;
}// Recebe uma string com C no final de cada conjunto parâmetros do controlador afim por partes. Converte cada trecho do início até encontrar o C em uma matriz e deleta o trecho da string.


template<typename Type>
bool ControlHandler::ExplicityController<Type>::isInside(const LinAlg::Matrix<Type> &_point)
{
	this->inWitchRegion = -1; // Se o número não for alterado os estados não pertencem a nenhuma região.
	LinAlg::Matrix<Type> point(_point.getNumberOfRows()+1,1);// Representa os estados estendidos. Point = [Point -1]; Esse comentário se aplica até a linha 12

	for(uint16_t i = 0; i < _point.getNumberOfRows(); ++i)
		point(i,0) = _point(i,0);

	point(_point.getNumberOfRows(),0) = (Type)(-1);

    for (uint16_t i = 0; i < quantityOfRegions; ++i) // Percorre todas as matrizes de restrições para  verificar em qual região os estados estão localizados.
    {
        // std::cout << "A matriz de restricoes: \n"<< this->Restrictions[i] << std::endl;
        // std::cout << "A matriz de pontos: \n"<< point << std::endl;

        LinAlg::Matrix<Type> H = this->Constraints[i]*point; // se todos os elementos desse vetor forem menores que uma tolerância (podem ser negativos), os estados pertencerão ao conjunto de restrições. Isso se aplica a linha 23 também (função any)

//        std::cout << "Resultado de H: \n"<< point << std::endl;

        if(!any(H))//Verifica se algum estado esta fora das restrições.
        {
            this->inWitchRegion = i;//sinaliza qual a região a qual os estados pertencem
//            std::cout << "Controle na regiao: "<< i+1 << std::endl;
            return true; // Sinaliza que encontrou uma região.
        }
    }	
    return false; //sinaliza que não encontrou uma região.
}

template<typename Type>
bool ControlHandler::ExplicityController<Type>::any(const LinAlg::Matrix<Type> &H){
    for(uint16_t j = 0; j < H.getNumberOfRows(); ++j) 
        if(H(j,0) > (Type)(1e-8)) //Verifica se algum estado esta fora das restrições.
            return true; // retorna true se algum dos estados está fora
    return false; //retorna falso se todos os estados pertencem ao conjunto de restrições.
}

template<typename Type>
std::string ControlHandler::ExplicityController<Type>::setConstraints(std::string constraints)
{
    uint16_t quantityOfRegions = 0, posOfNConstraint;

    for(uint16_t i = 0; i < constraints.length(); ++i) // Verifica quantas regiões precisarão ser criadas na alocação dinâmica de memória.
        if(constraints[i] == 'R') // um R identifica final de restrição.
			quantityOfRegions++;

    this->Constraints = new LinAlg::Matrix<Type>[quantityOfRegions];// inicializa o vetor de matrizes de restrições com a quantidade passada na string.

	for(uint16_t i = 0; i < quantityOfRegions; ++i)// Para cada conjunto de restrições, faça.
    {
        posOfNConstraint = constraints.find("R"); // Encontre o final do conjunto (encontrando o primeiro R da string)
        this->Constraints[i] = constraints.substr(0, posOfNConstraint - 1).c_str(); //Converta o trecho do início da string até uma posição antes do primeiro R em uma matriz.
        constraints.erase(0, posOfNConstraint + 1); //Apague da string o trecho que já foi passado para a matriz.

//         std::cout << "Parametros das Restricoes, Regiao [" << i+1 << "] = \n"<< this->Restrictions[i] << std::endl;
	}

	this->quantityOfRegions = quantityOfRegions;//atualiza a quantidade de restrições

    return constraints; //retorna o resto da string (Aquilo que na string não é restrições, pode ser parâmetros do controlador ou do observador)
}

template<typename Type>
std::string ControlHandler::ExplicityController<Type>::setControllerParameters(std::string controllers)
{//Essa função funciona exatamente igual à função anterior, só que mudando o R para C e no lugar de setar as restrições, seta os parâmetros do controlador.
	uint16_t quantityOfRegions = 0, posOfNController;

	for(uint16_t i = 0; i < controllers.length(); ++i)
		if(controllers[i] == 'C')
			quantityOfRegions++;

	this->controllerParameters = new LinAlg::Matrix<Type>[quantityOfRegions];

	for(uint16_t i = 0; i < quantityOfRegions; ++i)
    {
        posOfNController = controllers.find("C");
		this->controllerParameters[i] = controllers.substr(0, posOfNController - 1).c_str();
        controllers.erase(0, posOfNController + 1);
//         std::cout << "Parametros do Controlador, Regiao [" << i+1 << "] = \n" << this->controllerParameters[i] << std::endl;
	}

	this->quantityOfRegions = quantityOfRegions;
    return controllers;
}
