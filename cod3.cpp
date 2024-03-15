#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <bitset>

using namespace std;

double aptidao(double x, double a, double b, double c, double d, double e, double f) {
    return abs(a*pow(x,5) + b*pow(x,4) + c*pow(x,3) + d*pow(x,2) + e*x + f);
}

double decodificar(string gene) {
    bitset<32> bits(gene);
    unsigned long decimal = bits.to_ulong();
    double x = -10 + decimal*(20.0/(pow(2,32)-1));
    return x;
}

string mutacao(string pai) {
    int indice = rand() % pai.size();
    pai[indice] = pai[indice] == '0' ? '1' : '0';
    return pai;
}

pair<string, string> cruzamento(string pai1, string pai2) {
    int indice = rand() % pai1.size();
    string filho1 = pai1.substr(0, indice) + pai2.substr(indice, 32-indice);
    string filho2 = pai2.substr(0, indice) + pai1.substr(indice, 32-indice);
    return make_pair(filho1, filho2);
}

int main(){
    srand(time(0)); // para gerar números aleatórios

    // Menu para escolher o tamanho da população
    int tamanho_pop;
    cout << "Escolha o tamanho da população:\n";
    cout << "1. 10\n";
    cout << "2. 100\n";
    cout << "3. 1000\n";
    cout << "4. Sair\n";
    cout << "Opção: ";
    int opcao;
    cin >> opcao;
    switch(opcao) {
        case 1: tamanho_pop = 10; break;
        case 2: tamanho_pop = 100; break;
        case 3: tamanho_pop = 1000; break;
        case 4: cout << "Saindo do programa.\n"; return 0;
        default: cout << "Opção inválida. Usando o tamanho padrão da população (100).\n"; tamanho_pop = 100;
    }

    // Taxa de crossover fixa em 50%
    double taxa_crossover = 0.5;

    // Menu para escolher a taxa de mutação
    double taxa_mutacao;
    cout << "Digite a taxa de mutação (0 a 100): ";
    cin >> taxa_mutacao;
    taxa_mutacao /= 100; // Converte a porcentagem para uma proporção

    double a, b, c, d, e, f; // Coeficientes da equação
    cout << "Digite os coeficientes a, b, c, d, e, f da equação ax^5 + bx^4 + cx^3 + dx^2 + ex + f = 0: ";
    cin >> a >> b >> c >> d >> e >> f;

    string* populacao = new string[tamanho_pop];
    for (int i = 0; i < tamanho_pop; ++i) {
        for (int j = 0; j < 32; ++j) {
            populacao[i] += rand() % 2 == 0 ? '0' : '1';
        }
    }

    int max_geracoes = 1000; // Número máximo de gerações
    int geracao;
    for(geracao = 0; geracao < max_geracoes; ++geracao){
        for (int i = 0; i < tamanho_pop; ++i) {
            for (int j = i+1; j < tamanho_pop; ++j) {
                if (aptidao(decodificar(populacao[i]), a, b, c, d, e, f) > aptidao(decodificar(populacao[j]), a, b, c, d, e, f)) {
                    swap(populacao[i], populacao[j]);
                }
            }
        }

        if (aptidao(decodificar(populacao[0]), a, b, c, d, e, f) <= 1e-6) {
            break;
        }

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

    cout << "Melhor solução: x = " << decodificar(populacao[0]) << endl;
    cout << "Taxa de mutação: " << taxa_mutacao * 100 << "%" << endl;
    cout << "Taxa de crossover: " << taxa_crossover * 100 << "%" << endl;
    cout << "Número total de gerações: " << geracao + 1 << endl;
    cout << "Programa Finalizado" << endl;

    delete[] populacao;

    return 0;
}