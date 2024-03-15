#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <bitset>

using namespace std;

// Função de aptidão que calcula o quão próximo um indivíduo está de ser uma raiz da equação
long double aptidao(double x, double a, double b, double c, double d, double e, double f) {
    return abs(a*pow(x, 5) + b*pow(x, 4) + c*pow(x, 3) + d*pow(x, 2) + e*x + f);
}

// Função para decodificar o gene em um valor de x
double decodificar(string gene) {
    bitset<32> bits(gene);
    unsigned long decimal = bits.to_ulong();
    double x = -10 + decimal*(20.0/(pow(2,32)-1));
    return x;
}

// Função para aplicar mutação em um indivíduo
string mutacao(string pai) {
    int indice = rand() % pai.size();
    pai[indice] = pai[indice] == '0' ? '1' : '0';
    return pai;
}

// Função para aplicar crossover entre dois indivíduos
pair<string, string> cruzamento(string indv1, string indv2) {
    int indice = rand() % indv1.size();
    string filho1 = indv1.substr(0, indice) + indv2.substr(indice, 32-indice);
    string filho2 = indv2.substr(0, indice) + indv1.substr(indice, 32-indice);
    return make_pair(filho1, filho2);
}

// Programa principal
int main(){
    srand(time(0)); // Gerar números aleatórios

    // Declaração das variáveis
    int tamanho_pop = 100; // Tamanho da população
    double taxa_mutacao = 0.01; // Taxa de mutação
    int max_geracoes = 1000; // Número máximo de gerações
    double a, b, c, d, e, f; // Coeficientes da equação

    // Inicialização das variáveis
    cout << "Digite os coeficientes a, b, c, d, e, f da equação ax^5 + bx^4 + cx^3 + dx^2 + ex + f = 0: ";
    cin >> a >> b >> c >> d >> e >> f;

    // Gerar aleatoriamente a população inicial
    string* populacao = new string[tamanho_pop];
    for (int i = 0; i < tamanho_pop; ++i) {
        for (int j = 0; j < 32; ++j) {
            populacao[i] += rand() % 2 == 0 ? '0' : '1';
        }
    }

    // Laço das gerações
    for(int geracao = 0; geracao < max_geracoes; ++geracao){
        // avaliar população e ordená-la em ordem crescente de aptidão
        for (int i = 0; i < tamanho_pop; ++i) {
            for (int j = i+1; j < tamanho_pop; ++j) {
                if (aptidao(decodificar(populacao[i]), a, b, c, d, e, f) > aptidao(decodificar(populacao[j]), a, b, c, d, e, f)) {
                    swap(populacao[i], populacao[j]);
                }
            }
        }

        // Verificar se a solução está aceitável (se sim, encerrar laço)
        if (aptidao(decodificar(populacao[0]), a, b, c, d, e, f) <= 1e-6) {
            break;
        }

        // Aplicar mutação e cruzamento
        for (int i = tamanho_pop / 2; i < tamanho_pop; ++i) {
            if ((double) rand() / RAND_MAX < taxa_mutacao) {
                populacao[i] = mutacao(populacao[i]);
            }

            int indice_pai1 = rand() % (tamanho_pop / 2);
            int indice_pai2 = rand() % (tamanho_pop / 2);
            pair<string, string> filhos = cruzamento(populacao[indice_pai1], populacao[indice_pai2]);
            populacao[indice_pai1] = filhos.first;
            populacao[indice_pai2] = filhos.second;
        }
    }

    // Imprimir a melhor solução
    cout << "Melhor solução: x = " << decodificar(populacao[0]) << endl;

    delete[] populacao;

    return 0;
}