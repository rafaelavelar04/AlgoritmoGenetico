#include <iostream>
#include <bitset>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

int numeroDeGeracoes = 0;
const int maxIndividuos = 1000;
int quantidadeIndividuos = 1000;

void gerarIndividuos(int individuos[maxIndividuos], int &a, int &b, int &c, int &d, int &e, int &f)
{
    while (true)
    {
        cout << "Seja bem vindo ao sistema de genética" << endl
             << "Por favor, digite quantas populações gostaria de gerar (10, 100 ou 1000): " << endl;
        cin >> quantidadeIndividuos;
        if (quantidadeIndividuos != (1000 || 100 || 10))
        {
            cout << "Por favor, escolha uma das opções válidas" << endl;
            continue;
        }
        cout << "Quantas gerações vc deseja?" << endl;
        cin >> numeroDeGeracoes;

        cout << "Insira o valor de a: " << endl;
        cin >> a;
        if (a == 0)
        {
            cout << "O valor de a não pode ser 0" << endl;
            continue;
        }
        cout << "Insira o valor de b: " << endl;
        cin >> b;
        cout << "Insira o valor de c: " << endl;
        cin >> c;
        cout << "Insira o valor de d: " << endl;
        cin >> d;
        cout << "Insira o valor de e: " << endl;
        cin >> e;
        cout << "Insira o valor de f: " << endl;
        cin >> f;

        switch (quantidadeIndividuos)
        {
        case 10:
            cout << "Você escolheu a população de 10" << endl;
            break;
        case 100:
            cout << "Você escolheu a população de 100" << endl;
            break;
        case 1000:
            cout << "Você escolheu a população de 1000" << endl;
            break;
        }

        // Gera os individuos aletóriamente dentro do range de -2000 a 2000
        for (int i = 0; i < quantidadeIndividuos; i++)
        {
            individuos[i] = rand() % 4001 - 2000;
        }
        break;
    }
}

void crossOver(int individuos[maxIndividuos])
{
    // S;
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
    srand(time(0));
    int a, b, c, d, e, f, x, resultado;
    int individuos[maxIndividuos]; // Perguntar pro professor se tem problema colocar esse vetor num contexto global.

    gerarIndividuos(individuos, a, b, c, d, e, f);

    for (int i = 0; i < quantidadeIndividuos; i++)
    {
        passibilidadeDeMutacao(individuos[i]);
    }

    for (int i = 0; i < numeroDeGeracoes; i++)
    {
        for (int j = 0; j < quantidadeIndividuos; j++)
        {
            x = individuos[j];
            resultado = a * pow(x, 5) + b * pow(x, 4) + c * (x, 3) + d * pow(x, 2) + e * x + f;
            if (resultado == 0)
            {
                cout << "Resultado da equação: " << x << endl
                     << "Para o indivíduo: " << j << endl
                     << "Na geração" << i << endl;
                break;
            }
        }
    }
    return 0;
}