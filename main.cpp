#include <iostream>
#include <bitset>
using namespace std;

const int numeroDeGeracoes = 100;
const int maxIndividuos = 1000;

void gerarIndividuos(int individuos[maxIndividuos])
{
    int quantidadeIndividuos = 1000;
    while (true)
    {
        cout << "Você gostaria de gerar 10, 100 ou 1000 individuos?" << endl
             << "Digite 10, 100 ou 1000: " << endl;
        cin >> quantidadeIndividuos;

        if (quantidadeIndividuos != (10 | 100 | 1000))
            cout << "Por favor, digite um número válido." << endl;
        else
            break;
    }

    individuos[quantidadeIndividuos];
}

void crossOver(int individuos[maxIndividuos])
{
    S;
}

void geraRaiz()
{
}

bitset<32> passibilidadeDeMutacao(bitset<32> conteudoBit)
{
    srand(time(0));

    int posicao = rand() % 32;

    // Lembrar de pular a mutação do último bit da posição 31 pq ele controla o sinal do número
    if (posicao != 31)
        conteudoBit.set(posicao, (rand() % 2) == 0);

    return conteudoBit;
}

int main()
{
    int individuos[maxIndividuos]; // Perguntar pro professor se tem problema colocar esse vetor num contexto global.
    gerarIndividuos(individuos);
    for (int i = 0; i < quantidadeIndividuos; i++)
    {
        cout << bitset<32>(individuos[i]) << endl;
    }
    passibilidadeDeMutacao(individuos);

    cout << bitset<32>(individuos[0]) << endl;

    return 0;
}